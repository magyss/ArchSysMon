#pragma once
#include <string>
#include <unordered_map>

struct NetInterfaceStats {
    unsigned long rxBytes;
    unsigned long txBytes;
};

class NetworkMonitor {
public:
    NetworkMonitor();
    std::unordered_map<std::string, NetInterfaceStats> getStats();

private:
    std::unordered_map<std::string, NetInterfaceStats> prevStats;
};
