#ifndef MOCK_TEMPERATURE_SENSOR_HPP
#define MOCK_TEMPERATURE_SENSOR_HPP

#include<gmock/gmock.h>
#include "TemperatureMonitor.hpp"

class MockTemperatureSensor : public TemperatureSensor
{
    public:
    MOCK_METHOD(int, readTemperature, (), (override));
};
#endif