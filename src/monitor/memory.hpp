#pragma once

struct MemoryUsage {
    unsigned long totalRAM;
    unsigned long usedRAM;
    unsigned long totalSwap;
    unsigned long usedSwap;
};

class MemoryMonitor {
public:
    MemoryUsage getUsage();
};
