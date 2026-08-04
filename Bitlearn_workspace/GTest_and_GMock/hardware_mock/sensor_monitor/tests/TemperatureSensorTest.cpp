#include "MockTemperatureSensor.hpp"

using ::testing::Return;

TEST(TemperatureMonitorTest, NormalTemperature)
{
    MockTemperatureSensor sensor;

    EXPECT_CALL(sensor, readTemperature())
        .WillOnce(Return(25));

    TemperatureMonitor monitor(&sensor);

    EXPECT_EQ(monitor.checkTemperature(),Status::NORMAL);
}

TEST(TemperatureMonitorTest, WarningTemperature)
{
    MockTemperatureSensor sensor;

    EXPECT_CALL(sensor, readTemperature())
        .WillOnce(Return(85));

    TemperatureMonitor monitor(&sensor);

    EXPECT_EQ(monitor.checkTemperature(),
              Status::WARNING);
}

TEST(TemperatureMonitorTest, AlarmTemperature)
{
    MockTemperatureSensor sensor;

    EXPECT_CALL(sensor, readTemperature())
        .WillOnce(Return(100));

    TemperatureMonitor monitor(&sensor);

    EXPECT_EQ(monitor.checkTemperature(),
              Status::ALARM);
}

TEST(TemperatureMonitorTest, SensorFailure)
{
    MockTemperatureSensor sensor;

    EXPECT_CALL(sensor, readTemperature())
        .WillOnce(Return(-1));

    TemperatureMonitor monitor(&sensor);

    EXPECT_EQ(monitor.checkTemperature(),
              Status::SENSOR_ERROR);
}

TEST(TemperatureMonitorTest, RetryUnitSuccess)
{
    MockTemperatureSensor sensor;

    EXPECT_CALL(sensor, readTemperature())
        .Times(3)
        .WillOnce(Return(-1))
        .WillOnce(Return(-1))
        .WillOnce(Return(25));

    TemperatureMonitor monitor(&sensor);

    EXPECT_TRUE(monitor.readTemperatureWithRetry());
}

TEST(TemperatureMonitorTest, RetryFailsAfterThreeAttempts)
{
    MockTemperatureSensor sensor;

    EXPECT_CALL(sensor, readTemperature())
        .Times(3)
        .WillOnce(Return(-1))
        .WillOnce(Return(-1))
        .WillOnce(Return(-1));

    TemperatureMonitor monitor(&sensor);

    EXPECT_FALSE(monitor.readTemperatureWithRetry());
}