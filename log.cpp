#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <format>
#include <mutex>

using namespace std;

class Log {
private:
    atomic<bool> stop;
    vector<thread> threads;

    queue<shared_ptr<string>> displayQueue;
    queue<shared_ptr<pair<time_t, string>>> fileQueue;
    mutex displayMutex;
    mutex fileMutex;
    condition_variable displayCV;
    condition_variable fileCV;

    void displayLog() {
        unique_lock<mutex> lock(displayMutex);
        while (true) {
            if (!displayQueue.empty()) {
                cout << *displayQueue.front() << endl;
                displayQueue.pop();
                continue;
            }

            if (stop) {
                break;
            }

            displayCV.wait(lock);
        }
    }

    void fileLog(int n) {
        unique_lock<mutex> lock(fileMutex);
        while (true) {
            if (!fileQueue.empty()) {
                auto t = fileQueue.front();
                std::ofstream out(format("{}_{}.txt", to_string(t->first), n));
//                std::ofstream out(to_string(t->first) + "_" + to_string(n) + ".txt");
                out << t->second;
                out.close();
                fileQueue.pop();
                continue;
            }

            if (stop) {
                break;
            }

            fileCV.wait(lock);
        }
    }
public:
    Log(int displayThreads, int fileThreads) {
        for (int i = 0; i < displayThreads; i++) {
            threads.emplace_back(&Log::displayLog, this);
        }
        for (int i = 0; i < fileThreads; i++) {
            threads.emplace_back(&Log::fileLog, this, i);
        }
    }

    ~Log() {
        stop = true;
        displayCV.notify_all();
        fileCV.notify_all();
        for (auto& t: threads) {
            t.join();
        }
    }

    void Save(time_t& startTime, std::string& msg) {
        auto sharedMessage = make_shared<string>(msg);
        auto sharedLogEntry = make_shared<pair<time_t, string>>(startTime, msg);

        {
            scoped_lock lock(displayMutex, fileMutex);
            displayQueue.push(sharedMessage);
            fileQueue.push(sharedLogEntry);
        }

        displayCV.notify_one();
        fileCV.notify_one();
    }

};