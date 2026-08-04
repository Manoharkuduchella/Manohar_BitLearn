#include "TemperatureMonitor.hpp"

TemperatureMonitor::TemperatureMonitor(TemperatureSensor *sensor) : sensor_(sensor)
{

}

Status TemperatureMonitor::checkTemperature()
{
    int temp = sensor_->readTemperature();

    if(temp == -1)
    {
        return Status::SENSOR_ERROR;
    }
    else if(temp >= 100)
    {
        return Status::ALARM;
    }
    else if(temp >= 85)
    {
        return Status::WARNING;
    }
    else
        return Status::NORMAL;
}

bool TemperatureMonitor::readTemperatureWithRetry()
{
    constexpr int MAX_RETRIES = 3;

    for(int i = 0; i < MAX_RETRIES; i++)
    {
        int temp = sensor_->readTemperature();

        if(temp != -1)
        {
            return true;
        }
    }

    return false;
}