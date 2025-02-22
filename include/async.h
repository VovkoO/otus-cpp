#pragma once

#include <cstddef>
#include <chrono>
#include <sstream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>

using namespace std;

namespace async {
    class Logger {
    public:
        Logger(size_t s);
        ~Logger();

        void receive(const char* data, size_t size);
        void disconnect();
    private:
        size_t maxSize;
        size_t currentSize = 0;
        time_t startTime;
        bool needStop = false;
        stringstream commands;
        mutex m;
        queue<string> brackets;
        queue<string> filesQueue;
        queue<string> displayQueue;
        condition_variable filesCV;
        condition_variable displayCV;
        vector<thread> threads;

        void logFiles();
        void logDisplay();
    };

    using handle_t = shared_ptr<Logger>;

    handle_t connect(size_t bulk);
    void receive(handle_t, const char* data, size_t size);
    void disconnect(handle_t);
}