#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

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

void filter(const vector<vector<int> >& ips, const std::function<bool(const vector<int> &)> f) {
    for (auto &v: ips) {
        if (f(v)) {
            printIP(v);
            cout << endl;
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
        filter(ip_pool, [](const vector<int>& vec){return vec[0] == 1;});
//        cout << "ip 46 70\n";
        filter(ip_pool, [](const vector<int>& vec){return vec[0] == 46 && vec[1] == 70;});
//        cout << "ip_any 46\n";
        filter(ip_pool, [](const vector<int>& vec){return vec[0] == 46 || vec[1] == 70 || vec[2] == 46 || vec[3] == 46;});
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
