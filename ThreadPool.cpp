#include "lib/ThreadPool.h"

// Constructor: starts the given number of threads
ThreadPool::ThreadPool(size_t numThreads) : threads(), stop(false){
    threads.reserve(numThreads);
    for (size_t i = 0; i < numThreads; i++) {
        threads.emplace_back(&ThreadPool::activeThread, this);
    }
}

// Destructor: stops all threads and joins them
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queMtx);
        stop.store(true, std::memory_order_release);
        lock.unlock();
    }
    condVar.notify_all();
    for (std::jthread& thread : threads) {
        thread.join();
    }
}

// Adds a new task to the task queue
void ThreadPool::enqueueTask(std::function<void()> task) {
    assert(task != nullptr);
    {
        std::unique_lock<std::mutex> lock(queMtx);
        tasks.push(std::make_shared<HeavyTask>(std::move(task)));
        lock.unlock();
    }
    condVar.notify_one();
}

// Worker function: executed by each thread in the pool
void ThreadPool::activeThread() {
    while(true) {
        std::shared_ptr<HeavyTask> task;
        {
            std::unique_lock<std::mutex> lock(queMtx);
            condVar.wait(lock, [this](){ return stop.load(std::memory_order_acquire) || !tasks.empty(); });
            if (stop.load(std::memory_order_relaxed) && tasks.empty()) {
                return;
            }
            task = tasks.front();
            tasks.pop();
        }
        try{
            task->taskExecute();
        }
        catch(const std::exception& e){
            Logger::INFO("EXCEPTION CAUGHT IN TASK EXECUTION! " + std::string(e.what()));
        }
        catch (...) {
            Logger::INFO("UNKNOWN EXCEPTION CAUGHT IN TASK EXECUTION! \n");
        }
    }
}
