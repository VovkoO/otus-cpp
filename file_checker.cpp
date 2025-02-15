//
// Created by Vladimir Razdrogin on 09.02.2025.
//

#include <filesystem>
#include <regex>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include "file_checker.h"

using namespace std;

namespace fs = std::filesystem;

regex mask_to_regex(const string& mask) {
    string regex_mask;

    for (char ch : mask) {
        switch (ch) {
            case '*':
                regex_mask += ".*";
                break;
            case '?':
                regex_mask += ".";
                break;
            case '.':
                regex_mask += "\\.";
                break;
            default:
                regex_mask += ch;
                break;
        }
    }

    return regex(regex_mask, regex_constants::icase);
}

std::string calculate_crc32(const vector<char> input) {
    boost::crc_32_type crc;
    crc.process_bytes(input.data(), input.size());

    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << crc.checksum();
    return oss.str();
}

std::string calculate_md5(const vector<char> input) {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;

    hash.process_bytes(input.data(), input.size());
    hash.get_digest(digest);

    const auto charDigest = reinterpret_cast<const char*>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(digest), std::back_inserter(result));

    return result;
}

file_checker::file_checker(config& c): cfg(c) {
    if (!c.mask.empty()) {
        mask_rg = mask_to_regex(c.mask);
    }

    if (c.hash_algo == "md5") {
        hash = calculate_md5;
    } else {
        hash = calculate_crc32;
    }

    for (const string& dir : c.include) {
        scan_fs(1, dir);
    }

    check_files_equal();
}

file_checker::~file_checker() = default;

void file_checker::scan_fs(int current_level, const string& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        const string& path = entry.path().string();

        bool exclude = false;
        for (const string& ed : cfg.exclude) {
            if (path.find(ed) != string::npos) {
                exclude = true;
                break;
            }
        }

        if (exclude) {
            continue;
        }

        if (entry.is_directory()) {
            if (current_level < cfg.scan_level) {
                scan_fs(current_level + 1, path);
            }
            continue;
        }

        if (entry.file_size() < cfg.min_file_size) {
            continue;
        }

        if (!cfg.mask.empty() && !regex_match(path, mask_rg)) {
            continue;
        }

        relevant_files.push_back(path);
    }
}

void file_checker::check_files_equal() {
    if (relevant_files.size() < 2) {
        return;
    }

    vector<char> buffer(cfg.block_size, 0);

    unordered_map<string, vector<pair<const string&, ifstream>>> groups;
    for (const string& fp : relevant_files) {
        ifstream file(fp, std::ios::binary);
        file.read(buffer.data(), cfg.block_size);

        groups[hash(buffer)].emplace_back(fp, std::move(file));
        fill(buffer.begin(), buffer.end(), 0);
    }

    bool need_continue = true;

    while (need_continue) {
        need_continue = false;

        unordered_map<string, vector<pair<const string&, ifstream>>> new_groups;

        for (auto &file_group: groups) {
            if (file_group.second.size() < 2) {
                continue;
            }

            for (auto &file : file_group.second) {
                if (file.second.gcount() < cfg.block_size) {
                    new_groups[file_group.first].push_back(std::move(file));
                    continue;
                }

                file.second.read(buffer.data(), cfg.block_size);
                new_groups[file_group.first + hash(buffer)].push_back(std::move(file));
                fill_n(buffer.begin(), cfg.block_size, 0);
                need_continue = true;
            }
        }

        groups = std::move(new_groups);
    }

    for (auto &file_group: groups) {
        if (file_group.second.size() < 2) {
            continue;
        }

        for (auto &file : file_group.second) {
            cout << file.first << endl;
        }

        cout << endl;
    }
}

