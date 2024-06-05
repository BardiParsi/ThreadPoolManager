#include "lib/Logger.h"
//The implementation of logger.h for cout console output.

std::mutex Logger::logMtx;
void Logger::INFO(const std::string& message) {
        std::lock_guard<std::mutex> lockLog(logMtx); //Mutex Lock for multi threading access to console
        std::stringstream ss;
        ss << message;
        cout << ss.str() << endl;
    }
