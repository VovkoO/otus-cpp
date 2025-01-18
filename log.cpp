#include <chrono>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Log {
private:
    time_t startTime;

public:
    Log() {
        time(&startTime);
    }

    void Save(std::string& s) {
        std::ofstream out(to_string(startTime) + ".txt");
        out << s;
        out.close();

        cout << s << endl;
    }
};