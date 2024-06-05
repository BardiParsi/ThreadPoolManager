#pragma once
#include <functional>
#include <mutex>
#include "Logger.h"
#include <exception>

/*
This class holds a simulation of a heavy funtion which returns void.
std::functional is used to make the heavy task more generic and changable.
*/
class HeavyTask
{
private:
    std::function<void()> heavyFunc; // Any fucntion that returns void can be binded into HeavyFunc
    std::mutex taskMtx; // Mutex to ensure Thread Safety

public:
    HeavyTask(std::function<void()> func);
    ~HeavyTask() noexcept;
    // Delete copy constructor and copy assignment operator
    HeavyTask(const HeavyTask&) = delete;
    HeavyTask& operator=(const HeavyTask&) = delete;
    // Default move constructors
    HeavyTask(HeavyTask&&) noexcept = default;
    HeavyTask& operator=(HeavyTask&&) noexcept = default;

    void taskExecute();
};
