#include "async.h"

#include <fstream>
#include <iostream>
#include <iostream>

using namespace std;

namespace async {
    Logger::Logger(size_t s): maxSize(s) {
        threads.emplace_back(&Logger::logFiles, this);
        threads.emplace_back(&Logger::logDisplay, this);
    };

    Logger::~Logger() {
        unique_lock<mutex> lock(m);
        needStop = true;
        lock.unlock();
        filesCV.notify_all();
        displayCV.notify_all();

        for (auto& v:  threads) {
            v.join();
        }
    }

    void Logger::receive(const char *data, size_t size) {
        lock_guard lock(m);

        std::string strData(data, size);

        std::istringstream stream(strData);
        std::string substring;
        std::vector<std::string> substrings;

        while (getline(stream, substring, '\n')) {
            if (currentSize == 0) {
                time(&startTime);
                commands << "Bulk: ";
            }
            bool endBrackets = false;

            if (substring == "{") {
                brackets.push(substring);
                continue;
            } else if (substring == "}") {
                brackets.pop();
                endBrackets = true;
            } else {
                commands << format("{} ", substring);
                currentSize++;
            }

            if ((currentSize == maxSize && brackets.empty()) || endBrackets) {
                filesQueue.push(commands.str());
                displayQueue.push(commands.str());
                filesCV.notify_one();
                displayCV.notify_one();
                currentSize = 0;
                commands.str("");
            }
        }

    }

    void Logger::disconnect() {
        unique_lock<mutex> lock(m);
        if (currentSize > 0) {
            filesQueue.push(commands.str());
            displayQueue.push(commands.str());
            commands.str("");
            currentSize = 0;

            filesCV.notify_one();
            displayCV.notify_one();
        }
    }

    void Logger::logFiles() {
        while (true) {
            unique_lock<mutex> lock(m);
            if (filesQueue.empty() && !needStop) {
                filesCV.wait(lock);
            }

            if (filesQueue.empty() && needStop) {
                return;
            }

            if (filesQueue.empty()) {
                continue;
            }

            auto st = startTime;
            auto& cmd = filesQueue.front();
            filesQueue.pop();

            lock.unlock();

            std::ofstream out(format("{}.txt", st));
            out << cmd;
            out.close();
        }
    }

    void Logger::logDisplay() {
        while (true) {
            unique_lock<mutex> lock(m);
            if (displayQueue.empty() && !needStop) {
                displayCV.wait(lock);
            }

            if (displayQueue.empty() && needStop) {
                return;
            }

            if (displayQueue.empty()) {
                continue;
            }

            auto& cmd = displayQueue.front();
            displayQueue.pop();

            lock.unlock();

            std::cout << format("{}\n", cmd);
        }
    }


    handle_t connect(std::size_t s) {
        return make_shared<Logger>(s);
    }

    void receive(handle_t handle, const char *data, std::size_t size) {
        handle->receive(data, size);
    }

    void disconnect(handle_t handle) {
        handle->disconnect();
    }

}
