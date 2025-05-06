#include "temperature.hpp"
#include <sensors/sensors.h>
#include <vector>
#include <string>
#include <cstring>

std::vector<TemperatureSensor> TemperatureMonitor::getTemperatures() {
    std::vector<TemperatureSensor> temps;

    sensors_init(nullptr);

    const sensors_chip_name* chip;
    int chip_nr = 0;

    while ((chip = sensors_get_detected_chips(nullptr, &chip_nr)) != nullptr) {
        const sensors_feature* feature;
        int feature_nr = 0;

        while ((feature = sensors_get_features(chip, &feature_nr)) != nullptr) {
            if (feature->type != SENSORS_FEATURE_TEMP) continue;

            const sensors_subfeature* sub = sensors_get_subfeature(chip, feature, SENSORS_SUBFEATURE_TEMP_INPUT);
            if (!sub) continue;

            double val;
            if (sensors_get_value(chip, sub->number, &val) == 0) {
                std::string label = sensors_get_label(chip, feature);
                temps.push_back({ label, val });
            }
        }
    }

    sensors_cleanup();
    return temps;
}
