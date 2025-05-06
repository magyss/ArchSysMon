#pragma once
#include <vector>

struct CpuCoreUsage {
    double usagePercent;
};

class CpuMonitor {
public:
    CpuMonitor();
    std::vector<CpuCoreUsage> getUsage();

private:
    std::vector<std::vector<unsigned long long>> prevCpuStats;

    std::vector<unsigned long long> parseCpuLine(const std::string& line);
    void updatePrevStats(const std::vector<std::vector<unsigned long long>>& newStats);
};
