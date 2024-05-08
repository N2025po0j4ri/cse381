// Copyright 2024 Nirupama Poojari

#include "BufferToggle.h"      // Custom header
#include "homework03Helpers.h"  // Custom header
#include <unistd.h>             // POSIX operating system API
#include <sys/types.h>         // Data types
#include <pwd.h>                // Password database operations
#include <iostream>             // Input/output stream
#include <fstream>              // File stream
#include <sstream>              // String stream
#include <vector>               // Vector container
#include <iterator>             // Iterator
#include <algorithm>            // Algorithms
#include <iomanip>              // Input/output manipulators
#include <unordered_map>        // Unordered map container
#include <thread>               // Threading support
#include <chrono>               // Time utilities
#include <condition_variable>   // Condition variable
#include <mutex>                // Mutual exclusion
#include <atomic>               // Atomic operations
#include <map>                  // Map container
#include <cstdlib>              // General utilities library
using std::cout;

// Structure to hold CPU usage information
struct CPUUsage {  // CPPUsage starts
    uint64_t total = 0;
    std::unordered_map<int, uint64_t> pidToCpu;
    std::chrono::steady_clock::time_point timestamp;
};  // CPPUsage ends

// Global variables for synchronization
std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> terminateRequested(false);

// Function prototypes
std::string formatTime(uint64_t time);
uint64_t getCPUUsage(int pid);
CPUUsage gatherProcessInfo();
void displayProcesses(const CPUUsage& cpuUsage);
void clearScreen();
void displayTopLikeOutput();
void waitForInput();

/**
 * @brief Helper function to format CPU time
 * @param time
 * @return ss.str()
 */
std::string formatTime(uint64_t time) {  // formatTime() starts
    uint64_t hours = time / 3600;
    uint64_t minutes = (time % 3600) / 60;
    uint64_t seconds = time % 60;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
    return ss.str();
}  // formatTime() ends

/**
 * @brief Tokenizes a string using whitespace as delimiter
 * @param str The string to tokenize
 * @return A vector of tokens
 */
std::vector<std::string> tokenize(const std::string& str) {  // tokeniz() starts
    std::istringstream iss(str);
    return std::vector<std::string>{std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>()};
}  // tokenize() ends

/**
 * @brief Reads the contents of a file into a string
 * @param filePath The path to the file
 * @return The file contents
 */
std::string readFileToString(const std::string& filePath) {
    // readFileToString() starts
    std::ifstream file(filePath);
    if (file) {  // if file starts
        return {std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()};
    }  // if file ends
    return "";
}  // readFileToString() end

/**
 * @brief Gets CPU Usage for the given process ID
 * @param pid The process ID
 * @return The CPU usage in clock ticks
 */
uint64_t getCPUUsage(int pid) {  // getCPPUsage() starts
    std::string statFilePath = "/proc/" + std::to_string(pid) + "/stat";
    std::string content = readFileToString(statFilePath);
    if (content.empty()) {  // if startss
        return 0;
    }   // if ends

    // Tokenize the content
    std::vector<std::string> tokens = tokenize(content);

    // Calculate total CPU time
    uint64_t totalCpuTime = 0;
    if (tokens.size() >= 15) {  // if starts
        try {  // try starts
            totalCpuTime += std::stoull(tokens[13]);  // utime
            totalCpuTime += std::stoull(tokens[14]);  // stime
            return totalCpuTime;
        } catch (const std::exception& e) {  // catch starts
            std::cerr << "Error in parsing CPU time: " << e.what() << std::endl;
        }
    }  // try-ctch ends
    return 0;
}  // getCPPUsage() ends

/**
 * @brief Gathers information about the processes
 * @return CPUUsage structure containing process information
 */
CPUUsage gatherProcessInfo() {  // gatherProcessInfo() starts
    CPUUsage cpuUsage;
    cpuUsage.total = 0;

    std::vector<std::string> procFiles;
    getProcFiles(procFiles);
    uid_t uid = getuid();
    for (const auto& pid : procFiles) {  // for-each loop starts
        std::string statFilePath = "/proc/" + pid + "/loginuid";
        std::ifstream loginuidFile(statFilePath);
        if (!loginuidFile.is_open()) continue;
        std::string loginuid;
        std::getline(loginuidFile, loginuid);
        if (loginuid.empty() || loginuid == "4294967295") continue;
        try {  // try starts
            int loginUidInt = std::stoi(loginuid);
            if (loginUidInt != static_cast<int>(uid)) continue;
            uint64_t cpuUsageValue = getCPUUsage(std::stoi(pid));
            cpuUsage.pidToCpu[std::stoi(pid)] = cpuUsageValue;
            cpuUsage.total += cpuUsageValue;
        } catch (...) {  // catch starts
            continue;
        }  // try-catch ends
    }  // for loop ends
    return cpuUsage;
}  // gatherProcessInfo() end

/**
 * @brief Displays process information
 * @param cpuUsage The CPU usage information to display
 */
void displayProcesses(const CPUUsage& cpuUsage) {  // displayProcesses() start
    // Convert unordered map to map for automatic sorting
    std::map<uint64_t, int, std::greater<uint64_t>> sortedProcesses;
    for (const auto& entry : cpuUsage.pidToCpu) {  // for-each starts
        sortedProcesses[entry.second] = entry.first;
    }  // for-each ends

    // Display header
    std::cout << "   PID      CPU     COM\n";

    // Display each process
    for (const auto& entry : sortedProcesses) {  // for-each starts
        int pid = entry.second;
        uint64_t cpuTime = entry.first;

        // Format CPU time
        std::string formattedTime = formatTime(cpuTime);

        // Get command name
        std::string command = parseStatFile(std::to_string(pid)).tcomm;

        // Display process details
        std::cout << std::setw(7) << pid << "  "
                  << std::setw(10) << formattedTime
                  << "  " << command << "\n";
    }  // for-each ends

    // Display total CPU usage
    std::string formattedTotalTime = formatTime(cpuUsage.total);
    std::cout << "\nTotal CPU Usage: " << formattedTotalTime << std::endl;
}  // displayProcesses() end

/**
 * @brief Displays the output like the top command
 */
void displayTopLikeOutput() {  // displayTopLikeOutput() start
    CPUUsage prevCPUUsage;
    while (!terminateRequested) {  // while starts
        clearScreen();
        CPUUsage cpuUsage = gatherProcessInfo();
        displayProcesses(cpuUsage);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }  // while ends
}  // displayTopLikeOutput() ends

/**
 * @brief Waits for user input asynchronously
 * @return (void)
 */
void waitForInput() {  // waitForInput() ends
    BufferToggle bt;
    bt.off();
    while (true) {  // while starts
        char ch;
        std::cin.get(ch);
        if (ch == 'q') {  // if starts
            std::cout << "\nExiting program...\n";
            terminateRequested = true;
            cv.notify_one();
            break;  // Break out of the loop when 'q' is entered
        }  // if ends
    }  // while loop ends
}  // while ends


/**
 * @brief Clears the screen
 */
void clearScreen() {  // clearScreen starts
    int result = std::system("clear");
    (void)result;
}  // clearScreen ends

int main() {  // main starts
    std::thread waiter(waitForInput);
    waiter.detach();
    displayTopLikeOutput();
    std::exit(0);
}  // main ends
