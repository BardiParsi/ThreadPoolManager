#pragma once
#include "HeavyTask.h"
#include "Logger.h"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>
#include <memory>
#include <functional>
#include <atomic>
#include <cassert>

/*
ThreadPool class manages a pool of threads to perform heavy tasks.
It uses a queue to hold tasks and assigns them to threads for execution.
*/

class ThreadPool
{
private:
    std::vector<std::jthread> threads; // Vector of threads
    std::queue<std::shared_ptr<HeavyTask>> tasks; // Queue of tasks
    std::mutex queMtx; // Mutex for protecting access to the queue
    std::condition_variable_any condVar; // Condition variable for task synchronization
    std::atomic_bool stop; // Flag to signal stopping of threads
    void activeThread(); // Worker function for each thread in the pool

public:
    ThreadPool(size_t numThreads);
    ~ThreadPool() noexcept;
    void enqueueTask(std::function<void()> task); // Adds a new task to the tasks queue

};
