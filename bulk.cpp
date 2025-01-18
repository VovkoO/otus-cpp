#include <iostream>
#include <string>
#include <queue>
#include "log.cpp"

using namespace std;

class Bulk {
private:
    Log lg;
    size_t maxSize;
    queue<string> commands;
    queue<string> brackets;

    void handleOpenBracket() {
        if (brackets.empty()) {
            logCommands();
        }

        brackets.emplace("{");
    }

    void handleCloseBracket() {
        brackets.pop();
        if (brackets.empty()) {
            logCommands();
        }
    }

    void handleCommand(string& s) {
        if (commands.empty()) {
            lg = Log();
        }

        if (s != "EOF") {
            commands.emplace(s);
        }

        if (brackets.empty() && (commands.size() == maxSize || s == "EOF")) {
            logCommands();
        }
    }

    void logCommands() {
        if (commands.empty()) {
            return;
        }

        string res = "bulk: ";

        while (!commands.empty()) {
            res += commands.front() + " ";
            commands.pop();
        }

        lg.Save(res);
    }

public:
    Bulk(size_t maxSize): maxSize(maxSize) {
        cout << "Bulk " << this->maxSize << endl;
    };

    void Handle(string& s) {
       if (s == "{") {
           handleOpenBracket();
       } else if (s == "}") {
           handleCloseBracket();
       } else {
           handleCommand(s);
       }
    };
};

istream& operator >> (istream& in, Bulk& b) {
    string s;
    in >> s;
    b.Handle(s);
    return in;
}

int main(int argc, char* argv[]) {
    size_t maxSize = strtoul(argv[argc - 1], nullptr, 10);

    cout << maxSize << endl;

    queue<string> commands;
    queue<string> blocks;

    string command;
    Bulk b{maxSize};

    while (cin >> b);
}