# ESP32 BMI160 + W25Q128JVSQ SPI Flash with Touch Interface

This project demonstrates interfacing an ESP32 microcontroller with:
- **BMI160 IMU sensor** (accelerometer + gyroscope) via I2C
- **W25Q128JVSQ SPI flash memory** for data storage
- **Touch sensor** for triggering data readout

## Hardware Requirements

### ESP32 Pin Connections

#### BMI160 Sensor (I2C)
- VCC → 3.3V
- GND → GND
- SDA → GPIO 21 (ESP32 default I2C SDA)
- SCL → GPIO 22 (ESP32 default I2C SCL)
- SDO → GND (sets I2C address to 0x69)

#### W25Q128JVSQ SPI Flash
- VCC → 3.3V
- GND → GND
- CS → GPIO 5
- DO (MISO) → GPIO 19 (ESP32 default SPI MISO)
- DI (MOSI) → GPIO 23 (ESP32 default SPI MOSI)
- CLK (SCK) → GPIO 18 (ESP32 default SPI SCK)

#### Touch Sensor
- Touch pin → GPIO 4
- Touch threshold: 500 (adjustable)

## Software Dependencies

Install the following Arduino libraries:
1. **DFRobot_BMI160** - for BMI160 sensor communication
   - GitHub: https://github.com/DFRobot/DFRobot_BMI160
2. **val_flash_spi** - for SPI flash memory operations
   - GitHub: https://github.com/Valdemir-DSW/val_flash_spi

## How It Works

1. **Data Collection**: The ESP32 continuously reads accelerometer and gyroscope data from the BMI160 sensor
2. **Data Storage**: Sensor data is written to the SPI flash memory in a circular buffer fashion
3. **Touch Trigger**: When the touch sensor is activated, the most recent data is read from flash and printed to serial
4. **Circular Buffer**: Data wraps around when reaching the end of allocated flash space

## Data Structure

```cpp
typedef struct {
  int16_t accel[3];  // X, Y, Z accelerometer values
  int16_t gyro[3];   // X, Y, Z gyroscope values
} imu_data_t;
```

## Flash Memory Layout

- **Start Address**: 0x000000
- **End Address**: 0x00100000 (1MB allocated space)
- **Sector Size**: 4096 bytes (4KB)
- **Data Size**: 12 bytes per IMU reading (6 × 2 bytes)

## Usage

1. Upload the code to ESP32
2. Open Serial Monitor at 115200 baud
3. Move the BMI160 sensor to generate data
4. Touch GPIO 4 to read the last stored data

## Serial Output

- **Normal operation**: "Write OK" messages
- **Touch detected**: "Touch detected! Reading last data from flash..." followed by accel and gyro values
- **Errors**: "Write Failed", "BMI160 read failed", etc.

## Data Conversion

- **Accelerometer**: Raw value / 16384.0 = g (gravity units)
- **Gyroscope**: Raw value × π/180 = radians/second

## Troubleshooting

1. **BMI160 not detected**: Check I2C connections and address (0x69)
2. **Flash write fails**: Check SPI connections and CS pin (GPIO 5)
3. **Touch not working**: Adjust TOUCH_THRE value (lower = more sensitive)
4. **Data corruption**: Ensure proper power supply (3.3V only)

## Memory Usage

- Each IMU reading: 12 bytes
- Flash sector: 4096 bytes
- Maximum readings per sector: ~341
- Total capacity: ~85,000 readings (1MB / 12 bytes)

## Future Improvements

- Add timestamp to data structure
- Implement data averaging/filtering
- Add error recovery mechanisms
- Create data export functionality
- Add battery monitoring