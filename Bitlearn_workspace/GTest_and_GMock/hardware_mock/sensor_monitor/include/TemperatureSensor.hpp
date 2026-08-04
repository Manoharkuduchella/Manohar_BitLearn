#ifndef TEMP_SENSOR_HPP
#define TEMP_SENSOR_HPP

enum class Status
{
    NORMAL,
    WARNING,
    ALARM,
    SENSOR_ERROR
};


class TemperatureSensor
{
    public:
    virtual ~TemperatureSensor() = default;
    virtual int readTemperature() = 0;
};

#endif