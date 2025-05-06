#include "cpu.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

CpuMonitor::CpuMonitor() {
    getUsage();
}

std::vector<unsigned long long> CpuMonitor::parseCpuLine(const std::string& line) {
    std::istringstream ss(line);
    std::string cpu;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;

    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    return { user, nice, system, idle, iowait, irq, softirq, steal };
}

void CpuMonitor::updatePrevStats(const std::vector<std::vector<unsigned long long>>& newStats) {
    prevCpuStats = newStats;
}

std::vector<CpuCoreUsage> CpuMonitor::getUsage() {
    std::ifstream file("/proc/stat");
    std::string line;
    std::vector<CpuCoreUsage> usageList;
    std::vector<std::vector<unsigned long long>> currentStats;

    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.substr(0, 3) != "cpu") break;
        currentStats.push_back(parseCpuLine(line));
    }

    if (prevCpuStats.empty()) {
        updatePrevStats(currentStats);
        return std::vector<CpuCoreUsage>(currentStats.size(), {0.0});
    }

    for (size_t i = 0; i < currentStats.size(); ++i) {
        const auto& prev = prevCpuStats[i];
        const auto& curr = currentStats[i];

        unsigned long long prevIdle = prev[3] + prev[4];
        unsigned long long currIdle = curr[3] + curr[4];

        unsigned long long prevTotal = 0, currTotal = 0;
        for (auto v : prev) prevTotal += v;
        for (auto v : curr) currTotal += v;

        double totalDiff = static_cast<double>(currTotal - prevTotal);
        double idleDiff = static_cast<double>(currIdle - prevIdle);
        double usage = (totalDiff - idleDiff) / totalDiff * 100.0;

        usageList.push_back({usage});
    }

    updatePrevStats(currentStats);
    return usageList;
}
