#pragma once
#include <vector>
#include <string>

struct TemperatureSensor {
    std::string label;
    double temperature;
};

class TemperatureMonitor {
public:
    std::vector<TemperatureSensor> getTemperatures();
};
