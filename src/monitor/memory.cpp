#include "memory.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

MemoryUsage MemoryMonitor::getUsage() {
    std::ifstream file("/proc/meminfo");
    std::string line, key;
    unsigned long value;
    std::unordered_map<std::string, unsigned long> meminfo;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> key >> value;
        key = key.substr(0, key.length() - 1); // убираем ':' на конце
        meminfo[key] = value;
    }

    unsigned long totalRAM = meminfo["MemTotal"];
    unsigned long freeRAM = meminfo["MemFree"] + meminfo["Buffers"] + meminfo["Cached"];
    unsigned long usedRAM = totalRAM - freeRAM;

    unsigned long totalSwap = meminfo["SwapTotal"];
    unsigned long freeSwap = meminfo["SwapFree"];
    unsigned long usedSwap = totalSwap - freeSwap;

    return MemoryUsage{
        totalRAM / 1024,  // в MB
        usedRAM / 1024,
        totalSwap / 1024,
        usedSwap / 1024
    };
}
