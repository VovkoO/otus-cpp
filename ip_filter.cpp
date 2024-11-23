#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>

using namespace std;

vector<string> split(const string &str, char d)
{
    vector<string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void printIP(const vector<int>& v) {
    for(auto ip_part = v.cbegin(); ip_part != v.cend(); ++ip_part)
    {
        if (ip_part != v.cbegin())
        {
            cout << ".";
        }
        cout << *ip_part;
    }
}

void filter(const vector<vector<int> >& vec, int i) {
    for (auto& v : vec) {
        if (v[0] == i) {
            printIP(v);
            cout << endl;
        }
    }
}

void filter(const vector<vector<int> >& vec, int i, int j) {
    for (auto& v : vec) {
        if (v[0] == i && v[1] == j){
            printIP(v);
            cout << endl;
        }
    }
}

void filterAny(const vector<vector<int> >& vec, int i) {
    for (auto& v : vec) {
        for (auto z : v) {
            if (z == i) {
                printIP(v);
                cout << endl;
                break;
            }
        }
    }
}


int main()
{
    try
    {
        vector<vector<int> > ip_pool;

        for(string line; getline(cin, line);)
        {
            vector<string> v = split(line, '\t');
            auto splited = split(v.at(0), '.');
            vector<int> res;
            res.reserve(splited.size());
            for (auto& s : splited) {
                res.push_back(stoi(s));
            }
            ip_pool.push_back(res);
        }

        sort(ip_pool.rbegin(), ip_pool.rend());

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            printIP(*ip);
            cout << endl;
        }

//        cout << "ip 1\n";
        filter(ip_pool, 1);
//        cout << "ip 46 70\n";
        filter(ip_pool, 46, 70);
//        cout << "ip_any 46\n";
        filterAny(ip_pool, 46);
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
