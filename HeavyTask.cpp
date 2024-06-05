#include "lib/HeavyTask.h"

HeavyTask::HeavyTask(std::function<void()> func) : heavyFunc(func) {}
HeavyTask::~HeavyTask() = default;

void HeavyTask::taskExecute() {
    std::lock_guard<std::mutex> lock(taskMtx);
    try{
        heavyFunc();
    }
    catch(const std::exception& e) {
        Logger::INFO("EXCEPTION CAUGHT IN HEAVY TASK OBJECT! " + std::string(e.what()));
    }
    catch(...) {
        Logger::INFO("UNKNOWN ERROR FROM HEAVY TASK OBJECT!\n");
    }
}
