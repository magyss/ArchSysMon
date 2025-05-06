#include "network.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

NetworkMonitor::NetworkMonitor() {
    getStats();
}

std::unordered_map<std::string, NetInterfaceStats> NetworkMonitor::getStats() {
    std::ifstream file("/proc/net/dev");
    std::string line;
    std::unordered_map<std::string, NetInterfaceStats> currentStats;

    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string iface;
        NetInterfaceStats stats;

        ss >> iface;
        iface = iface.substr(0, iface.length() - 1); 

        ss >> stats.rxBytes;
        for (int i = 0; i < 7; ++i) ss >> line; 
        ss >> stats.txBytes;

        currentStats[iface] = stats;
    }

    std::unordered_map<std::string, NetInterfaceStats> deltaStats;

    for (const auto& [iface, stats] : currentStats) {
        const auto& prev = prevStats[iface];
        deltaStats[iface] = {
            stats.rxBytes - prev.rxBytes,
            stats.txBytes - prev.txBytes
        };
    }

    prevStats = currentStats;
    return deltaStats;
}
