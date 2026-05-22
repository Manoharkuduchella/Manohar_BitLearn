/*
 * bme280.h
 *
 *  Created on: May 15, 2026
 *      Author: manohar kuduchella
 */

#ifndef BME280_H_
#define BME280_H_

#include <stdint.h>
#include "stm32l476xx_i2c_driver.h"

#define BME280_ADDR        0x77   /* 7-bit address for your board */

/*
 * BME280 register definitions
 */
#define BME280_ID_REG          0xD0
#define BME280_RESET_REG       0xE0
#define BME280_CTRL_HUM_REG    0xF2
#define BME280_STATUS_REG      0xF3
#define BME280_CTRL_MEAS_REG   0xF4
#define BME280_CONFIG_REG      0xF5
#define BME280_PRESS_MSB_REG   0xF7

/*
 * Expected chip ID
 */
#define BME280_CHIP_ID         0x60

/*
 * Oversampling definitions
 */
#define OSRS_OFF              0x00
#define OSRS_1                0x01
#define OSRS_2                0x02
#define OSRS_4                0x03
#define OSRS_8                0x04
#define OSRS_16               0x05

/*
 * Mode definitions
 */
#define MODE_SLEEP            0x00
#define MODE_FORCED           0x01
#define MODE_NORMAL           0x03

/*
 * Standby time
 */
#define T_SB_0p5              0x00
#define T_SB_62p5             0x01
#define T_SB_125              0x02
#define T_SB_250              0x03
#define T_SB_500              0x04
#define T_SB_1000             0x05
#define T_SB_10               0x06
#define T_SB_20               0x07

/*
 * IIR filter coefficients
 */
#define IIR_OFF               0x00
#define IIR_2                 0x01
#define IIR_4                 0x02
#define IIR_8                 0x03
#define IIR_16                0x04

uint8_t BME280_ReadID(I2C_Handle_t *pI2CHandle);
uint8_t BME280_Config(I2C_Handle_t *pI2CHandle,
                      uint8_t osrs_t,
                      uint8_t osrs_p,
                      uint8_t osrs_h,
                      uint8_t mode,
                      uint8_t t_sb,
                      uint8_t filter);

uint8_t BME280_Measure(I2C_Handle_t *pI2CHandle,
                    float *temperature,
                    float *pressure,
                    float *humidity);

#endif /* BME280_H_ */
