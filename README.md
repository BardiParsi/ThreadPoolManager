# ThreadPoolManager

ThreadPoolManager is a C++ project that implements an efficient multi-threading system using a thread pool for generic functions of the same type and different tasks. It includes task management, synchronization mechanisms, and thread-safe logging to demonstrate concurrent task execution.

## Features

- Efficient thread pooling
- Task queue management
- Synchronization mechanisms with mutexes and condition variables
- Thread-safe logging system
- Exception handling within tasks

## Prerequisites

- C++20 or later
- A compatible compiler (MinGW G++) or Microsoft Visual C++ (MSVC)
- CPU with more than 2 Threads

## Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/yourusername/ThreadPoolManager.git
    cd ThreadPoolManager
    ```

2. Build the project using CMake:

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```
# Contributing
   Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

# License
  This project is licensed under the GNU General Public License (GNU GPL). - see the LICENSE file for details.

# Contact
email: farsi.masoud@gmail.com
Linkedin: https://www.linkedin.com/in/bardiaparsi/
GitHub: https://github.com/BardiParsi

## Usage

1. Run the executable:

    ```sh
    ./ThreadPoolManager
    ```

2. Modify the `main.cpp` file to change the tasks or the number of threads.

## Project Structure

- **src/**: Source files
    - **main.cpp**: Entry point of the application
    - **ThreadPool.cpp**: Implementation of the ThreadPool class
    - **HeavyTask.cpp**: Implementation of the HeavyTask class
    - **Logger.cpp**: Implementation of the Logger class
- **include/**: Header files
    - **ThreadPool.h**: Header for the ThreadPool class
    - **HeavyTask.h**: Header for the HeavyTask class
    - **Logger.h**: Header for the Logger class
- **CMakeLists.txt**: CMake build configuration

## Example

Here is a simple example to demonstrate the usage:

```cpp
#include <iostream>
#include "ThreadPool.h"
#include "Logger.h"

void taskSimulator(int id) {
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    Logger::INFO("Task " + std::to_string(id) + " running on thread ID: " + oss.str() + "\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {
    const int CPUThreadNum = std::thread::hardware_concurrency();
    int numberOfThreads {CPUThreadNum};
    assert(numberOfThreads >= 2);

    if (numberOfThreads >= 2) {
        ThreadPool pool(numberOfThreads);
        for (int i = 0; i < numberOfThreads; i++) {
            pool.enqueueTask([i](){ taskSimulator(i); });
        }
    } else {
        Logger::INFO("THERE ARE NOT ENOUGH CPU THREADS ON THIS DEVICE");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cin.get();

    return 0;



}
