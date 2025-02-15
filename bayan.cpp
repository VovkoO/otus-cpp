#include <boost/program_options.hpp>
#include <iostream>
#include <filesystem>
#include "file_checker.h"

using namespace std;

namespace po = boost::program_options;
namespace fs = filesystem;

int main(int argc, char* argv[]) {
    po::options_description desc("Allowed options");

    desc.add_options()
            ("help,h", "Show help")
            ("include", po::value<vector<string>>(), "Include directories")
            ("exclude", po::value<vector<string>>(), "Exclude directories")
            ("scan-level", po::value<int>()->default_value(1), "Scan level")
            ("min-file-size", po::value<int>()->default_value(1), "Min file size to scan")
            ("file-mask", po::value<string>(), "File mask")
            ("block-size", po::value<int>(), "File compare block size")
            ("hash-algorithm", po::value<string>()->default_value("md5"), "Hash algorithm");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 0;
    }

    config cfg;
    if (vm.contains("include")) {
        cfg.include = vm["include"].as<vector<string>>();
    }
    if (vm.contains("exclude")) {
        cfg.exclude = vm["exclude"].as<vector<string>>();
    }
    if (vm.contains("scan-level")) {
        cfg.scan_level = vm["scan-level"].as<int>();
    }
    if (vm.contains("min-file-size")) {
        cfg.min_file_size = vm["min-file-size"].as<int>();
    }
    if (vm.contains("file-mask")) {
        cfg.mask = vm["file-mask"].as<string>();
    }
    if (vm.contains("block-size")) {
        cfg.block_size = vm["block-size"].as<int>();
    }
    if (vm.contains("hash-algorithm")) {
        cfg.hash_algo = vm["hash-algorithm"].as<string>();
    }

    file_checker fc(cfg);
}
