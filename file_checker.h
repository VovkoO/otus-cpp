//
// Created by Vladimir Razdrogin on 09.02.2025.
//

#ifndef BAYAN_FILE_CHECKER_H
#define BAYAN_FILE_CHECKER_H

#include <vector>
#include <regex>

using namespace std;

struct config {
    vector<string> include;
    vector<string> exclude;
    int scan_level;
    size_t min_file_size;
    string mask;
    int block_size;
    string hash_algo;
};

class file_checker {
public:
    file_checker(config&);
    ~file_checker();

private:
    void scan_fs(int current_level, const string& path);
    void check_files_equal();

    config cfg;
    regex mask_rg;
    vector<string> relevant_files;
    function<string(const vector<char>)> hash;
};


#endif //BAYAN_FILE_CHECKER_H
