#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <assert.h>
#include <stdint.h>

using namespace std;

struct addr_t
{
    addr_t() = default;
    addr_t(const addr_t& arg) = default;
    ~addr_t() = default;

    addr_t(uint32_t arg) noexcept : value(arg) {};

    uint8_t& operator[] (unsigned index) noexcept
    {
        assert(index < 4);
        return (reinterpret_cast<uint8_t*>(&value))[index];
    };

    uint8_t operator[] (unsigned index) const noexcept
    {
        assert(index < 4);
        return (reinterpret_cast<const uint8_t*>(&value))[index];
    };

    void print(ostream& out = cout) const {
        out << int((*this)[3]) << "." << int((*this)[2]) << "."
            << int((*this)[1]) << "." << int((*this)[0]) << endl;
    };

    operator uint32_t () const noexcept {return value;};

private:
    uint32_t value;
};

int main()
{
    static vector<addr_t> addr;
    static vector<addr_t> cache46;

    try {
        smatch match;
        string line;
        size_t linenum = 0;
        //- argument index:   1              2              3              4
        regex  search("^([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\t.*\\t.*$");

        while (getline(cin, line))
        {
            regex_match(line, match, search);
            if (match.size() != 5)
                throw runtime_error("Wrong syntax at line " + to_string(linenum));

            addr.push_back(0);

            for (auto i = 1; i <= 4; ++i)
            {
                auto octet = stoi(match[i]);
                if (octet > 255)
                    throw out_of_range("Octet should be in range: [0..255] Error at line " + to_string(linenum));

                addr.back()[4 - i] = octet;
            }

            linenum++;
        }

        if (addr.empty())
            throw runtime_error("No values given.");

    } catch(const exception& err)
    {
        cerr << err.what() << endl;
        return 1;
    } catch(...)
    {
        cerr << "Error unknown." << endl;
        return 2;
    }

    sort(addr.begin(), addr.end(), [](uint32_t a, uint32_t b){return a > b;});

//- Print whole list, cache elements for whitch any octet is 46
    for (auto &val: addr)
    {
        val.print();

        if ((val[0] == 46)||(val[1] == 46)||(val[2] == 46)||(val[3] == 46))
            cache46.push_back(val);
    }

//- Print elements like 1.*.*.* but find a better starting position first
    auto index = addr.size() / 2;
    for (auto range = index / 2; range; range /= 2)
        index += (addr[index][3] > 1) ? range : -range;

    while (index < addr.size() && addr[index][3] > 1)
        index++;

    if (index < addr.size())
        find_if(addr.begin() + index, addr.end(),
            [](const addr_t& val)
            {
                if (val[3] != 1)
                    return true;

                val.print();

                return false;
            }
        );

//- Print elements like 46.70.*.*
    find_if(cache46.begin(), cache46.end(),
        [](const addr_t& val)
        {
            if (val[3] < 46)
                return true;

            if ((val[3] == 46) && (val[2] == 70))
                val.print();

            return false;
        }
    );

//- Print elements for whitch any octet is 46
    for (auto &val: cache46)
        val.print();

    return 0;
}
