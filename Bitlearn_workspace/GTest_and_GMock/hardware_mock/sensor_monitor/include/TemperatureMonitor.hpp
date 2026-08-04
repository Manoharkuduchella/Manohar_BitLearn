#ifndef TEMP_MONITOR_HPP
#define TEMP_MONITOR_HPP

#include "TemperatureSensor.hpp"

class TemperatureMonitor
{
    public:
    explicit TemperatureMonitor(TemperatureSensor *Sensor);
    Status checkTemperature();
    bool readTemperatureWithRetry();

    private:
    TemperatureSensor *sensor_;
};

#endif