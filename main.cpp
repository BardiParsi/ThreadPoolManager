#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <sstream>
#include <cassert>
#include "lib/Logger.h"
#include "lib/HeavyTask.h"
#include "lib/ThreadPool.h"


// Minimum requirement for this program is 2 CPU thread MinGW64 G++ Compiler for C++20.
// Heavy task function can be any type of void() with no parameter.
// Type of function can be modified in HeavyTask class.

const int CPUThreadNum = std::thread::hardware_concurrency(); //total number of threads in CPU

// Function to simulate a task
void taskSimulator(int id) {
    std::ostringstream oss;
    oss << std::this_thread::get_id(); // Convert thread ID to string
    Logger::INFO("Task " + std::to_string(id) + " running on thread ID: " + oss.str()  + "\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {
    // This runs on full capacity of total thread. This can be changed simply by modifyimg the numbedroFThreads
    int numberOfThreads {CPUThreadNum};
    assert(numberOfThreads >= 2); // Assert if we have less than 2 threads to run this program

    if (numberOfThreads >= 2) {
        ThreadPool pool(numberOfThreads);
        for (int i = 0; i < numberOfThreads; i++) {
            pool.enqueueTask([i](){ taskSimulator(i);}); // The std::function of void can be any of void type
        }
    } else {
        Logger::INFO("THERE IS NOT ENOUGH CPU THREADS ON THIS DIVICE");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Threads sleep for 2 seconds before the program to ends

    std::cin.get(); //This can be eliminated. It is used just to keep the console on.

    return 0;
}
