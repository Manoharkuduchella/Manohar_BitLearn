/*
 * bme280_i2c.c
 *
 *  Created on: May 15, 2026
 *      Author: manohar kuduchella
 */

#include "stm32l476xx.h"

#include "bme280.h"

/*
 * Use 32-bit compensation.
 */
#define SUPPORT_32BIT 1

static uint8_t TrimRead(I2C_Handle_t *pI2CHandle);
static uint8_t BMEReadRaw(I2C_Handle_t *pI2CHandle);

static int32_t BME280_compensate_T_int32(int32_t adc_T);
static uint32_t BME280_compensate_P_int32(int32_t adc_P);
static uint32_t bme280_compensate_H_int32(int32_t adc_H);

static int32_t tRaw, pRaw, hRaw;

static uint16_t dig_T1;
static int16_t  dig_T2;
static int16_t  dig_T3;

static uint16_t dig_P1;
static int16_t  dig_P2;
static int16_t  dig_P3;
static int16_t  dig_P4;
static int16_t  dig_P5;
static int16_t  dig_P6;
static int16_t  dig_P7;
static int16_t  dig_P8;
static int16_t  dig_P9;

static uint8_t  dig_H1;
static int16_t  dig_H2;
static uint8_t  dig_H3;
static int16_t  dig_H4;
static int16_t  dig_H5;
static int8_t   dig_H6;

static int32_t t_fine;
static uint8_t chipID;

volatile uint8_t g_bme_id;
volatile uint8_t g_read_ret;
volatile uint32_t g_isr_after_read;
volatile uint32_t g_cr2_after_read;

uint8_t BME280_ReadID(I2C_Handle_t *pI2CHandle)
{
    uint8_t id = 0;

    g_read_ret = I2C_MasterReadRegister(pI2CHandle,
                                        BME280_ADDR,
                                        BME280_ID_REG,
                                        &id,
                                        1);

    g_bme_id = id;

    g_isr_after_read = pI2CHandle->pI2Cx->ISR;
    g_cr2_after_read = pI2CHandle->pI2Cx->CR2;

    if (g_read_ret == 0)
    {
        return 0;
    }

    return id;
}


uint8_t BME280_Config(I2C_Handle_t *pI2CHandle,uint8_t osrs_t,uint8_t osrs_p,uint8_t osrs_h,uint8_t mode,uint8_t t_sb,uint8_t filter)
{
    uint8_t datatowrite;
    uint8_t datacheck;

    /*
     * First check chip ID
     */
    chipID = BME280_ReadID(pI2CHandle);

    if (chipID != BME280_CHIP_ID)
    {
        return 1;
    }

    /*
     * Read trimming parameters
     */
    if (TrimRead(pI2CHandle) != 0)
    {
        return 2;
    }

    /*
     * Reset device
     */
    datatowrite = 0xB6;

    if (I2C_MasterWriteRegister(pI2CHandle,
                                BME280_ADDR,
                                BME280_RESET_REG,
                                &datatowrite,
                                1) == 0)
    {
        return 3;
    }

    /*
     * Simple delay after reset
     */
    for (volatile uint32_t i = 0; i < 500000; i++);

    /*
     * Write humidity oversampling to 0xF2
     */
    datatowrite = osrs_h;

    if (I2C_MasterWriteRegister(pI2CHandle,
                                BME280_ADDR,
                                BME280_CTRL_HUM_REG,
                                &datatowrite,
                                1) == 0)
    {
        return 4;
    }

    I2C_MasterReadRegister(pI2CHandle,
                           BME280_ADDR,
                           BME280_CTRL_HUM_REG,
                           &datacheck,
                           1);

    if (datacheck != datatowrite)
    {
        return 5;
    }

    /*
     * Write standby time and IIR filter to 0xF5
     */
    datatowrite = (t_sb << 5) | (filter << 2);

    if (I2C_MasterWriteRegister(pI2CHandle,
                                BME280_ADDR,
                                BME280_CONFIG_REG,
                                &datatowrite,
                                1) == 0)
    {
        return 6;
    }

    I2C_MasterReadRegister(pI2CHandle,
                           BME280_ADDR,
                           BME280_CONFIG_REG,
                           &datacheck,
                           1);

    if (datacheck != datatowrite)
    {
        return 7;
    }

    /*
     * Write temperature oversampling, pressure oversampling and mode to 0xF4
     */
    datatowrite = (osrs_t << 5) | (osrs_p << 2) | mode;

    if (I2C_MasterWriteRegister(pI2CHandle,
                                BME280_ADDR,
                                BME280_CTRL_MEAS_REG,
                                &datatowrite,
                                1) == 0)
    {
        return 8;
    }

    I2C_MasterReadRegister(pI2CHandle,
                           BME280_ADDR,
                           BME280_CTRL_MEAS_REG,
                           &datacheck,
                           1);

    if (datacheck != datatowrite)
    {
        return 9;
    }

    return 0;
}


static uint8_t TrimRead(I2C_Handle_t *pI2CHandle)
{
    uint8_t trimdata[32];

    /*
     * Read NVM from 0x88 to 0xA0, 25 bytes
     */
    if (I2C_MasterReadRegister(pI2CHandle,
                               BME280_ADDR,
                               0x88,
                               trimdata,
                               25) == 0)
    {
        return 1;
    }

    /*
     * Read NVM from 0xE1 to 0xE7, 7 bytes
     */
    if (I2C_MasterReadRegister(pI2CHandle,
                               BME280_ADDR,
                               0xE1,
                               trimdata + 25,
                               7) == 0)
    {
        return 2;
    }

    /*
     * Temperature coefficients
     */
    dig_T1 = (uint16_t)((trimdata[1] << 8) | trimdata[0]);
    dig_T2 = (int16_t)((trimdata[3] << 8) | trimdata[2]);
    dig_T3 = (int16_t)((trimdata[5] << 8) | trimdata[4]);

    /*
     * Pressure coefficients
     */
    dig_P1 = (uint16_t)((trimdata[7] << 8) | trimdata[6]);
    dig_P2 = (int16_t)((trimdata[9] << 8) | trimdata[8]);
    dig_P3 = (int16_t)((trimdata[11] << 8) | trimdata[10]);
    dig_P4 = (int16_t)((trimdata[13] << 8) | trimdata[12]);
    dig_P5 = (int16_t)((trimdata[15] << 8) | trimdata[14]);
    dig_P6 = (int16_t)((trimdata[17] << 8) | trimdata[16]);
    dig_P7 = (int16_t)((trimdata[19] << 8) | trimdata[18]);
    dig_P8 = (int16_t)((trimdata[21] << 8) | trimdata[20]);
    dig_P9 = (int16_t)((trimdata[23] << 8) | trimdata[22]);

    /*
     * Humidity coefficients
     */
    dig_H1 = trimdata[24];
    dig_H2 = (int16_t)((trimdata[26] << 8) | trimdata[25]);
    dig_H3 = trimdata[27];
    dig_H4 = (int16_t)((trimdata[28] << 4) | (trimdata[29] & 0x0F));
    dig_H5 = (int16_t)((trimdata[30] << 4) | (trimdata[29] >> 4));
    dig_H6 = (int8_t)trimdata[31];

    return 0;
}

volatile uint8_t g_raw_status;
volatile int32_t g_tRaw;
volatile int32_t g_pRaw;
volatile int32_t g_hRaw;

volatile uint8_t g_raw_data[8];

static uint8_t BMEReadRaw(I2C_Handle_t *pI2CHandle)
{
    uint8_t RawData[8];

    chipID = BME280_ReadID(pI2CHandle);

    if (chipID != BME280_CHIP_ID)
    {
        return 1;
    }

    /*
     * Read registers 0xF7 to 0xFE
     */
    if (I2C_MasterReadRegister(pI2CHandle,
                               BME280_ADDR,
                               BME280_PRESS_MSB_REG,
                               RawData,
                               8) == 0)
    {
        return 2;
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        g_raw_data[i] = RawData[i];
    }

    /*
     * Pressure and temperature are 20-bit.
     * Humidity is 16-bit.
     */
    pRaw = ((int32_t)RawData[0] << 12) |
           ((int32_t)RawData[1] << 4)  |
           ((int32_t)RawData[2] >> 4);

    tRaw = ((int32_t)RawData[3] << 12) |
           ((int32_t)RawData[4] << 4)  |
           ((int32_t)RawData[5] >> 4);

    hRaw = ((int32_t)RawData[6] << 8) |
           ((int32_t)RawData[7]);

    g_pRaw = pRaw;
    g_tRaw = tRaw;
    g_hRaw = hRaw;

    return 0;
}



uint8_t BME280_Measure(I2C_Handle_t *pI2CHandle,
                       float *temperature,
                       float *pressure,
                       float *humidity)
{
    g_raw_status = BMEReadRaw(pI2CHandle);

    if (g_raw_status == 0)
    {
        if (tRaw == 0x80000)
        {
            *temperature = 0;
        }
        else
        {
            *temperature = BME280_compensate_T_int32(tRaw) / 100.0f;
        }

        if (pRaw == 0x80000)
        {
            *pressure = 0;
        }
        else
        {
            *pressure = BME280_compensate_P_int32(pRaw);
        }

        if (hRaw == 0x8000)
        {
            *humidity = 0;
        }
        else
        {
            *humidity = bme280_compensate_H_int32(hRaw) / 1024.0f;
        }

        return 0;
    }

    *temperature = 0;
    *pressure = 0;
    *humidity = 0;

    return g_raw_status;
}


static int32_t BME280_compensate_T_int32(int32_t adc_T)
{
    int32_t var1, var2, T;

    var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) *
            ((int32_t)dig_T2)) >> 11;

    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) *
              ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) *
            ((int32_t)dig_T3)) >> 14;

    t_fine = var1 + var2;

    T = (t_fine * 5 + 128) >> 8;

    return T;
}

static uint32_t BME280_compensate_P_int32(int32_t adc_P)
{
    int32_t var1, var2;
    uint32_t p;

    var1 = (((int32_t)t_fine) >> 1) - (int32_t)64000;

    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) *
           ((int32_t)dig_P6);

    var2 = var2 + ((var1 * ((int32_t)dig_P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t)dig_P4) << 16);

    var1 = (((dig_P3 *
             (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) +
            ((((int32_t)dig_P2) * var1) >> 1)) >> 18;

    var1 = ((((32768 + var1)) * ((int32_t)dig_P1)) >> 15);

    if (var1 == 0)
    {
        return 0;
    }

    p = (((uint32_t)(((int32_t)1048576) - adc_P) -
         (var2 >> 12))) * 3125;

    if (p < 0x80000000)
    {
        p = (p << 1) / ((uint32_t)var1);
    }
    else
    {
        p = (p / (uint32_t)var1) * 2;
    }

    var1 = (((int32_t)dig_P9) *
            ((int32_t)(((p >> 3) * (p >> 3)) >> 13))) >> 12;

    var2 = (((int32_t)(p >> 2)) *
            ((int32_t)dig_P8)) >> 13;

    p = (uint32_t)((int32_t)p + ((var1 + var2 + dig_P7) >> 4));

    return p;
}


static uint32_t bme280_compensate_H_int32(int32_t adc_H)
{
    int32_t v_x1_u32r;

    v_x1_u32r = t_fine - ((int32_t)76800);

    v_x1_u32r =
        (((((adc_H << 14) -
            (((int32_t)dig_H4) << 20) -
            (((int32_t)dig_H5) * v_x1_u32r)) +
           ((int32_t)16384)) >> 15) *
         (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) *
              (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) +
               ((int32_t)32768))) >> 10) +
            ((int32_t)2097152)) *
           ((int32_t)dig_H2) + 8192) >> 14));

    v_x1_u32r =
        v_x1_u32r -
        (((((v_x1_u32r >> 15) *
            (v_x1_u32r >> 15)) >> 7) *
          ((int32_t)dig_H1)) >> 4);

    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

    return (uint32_t)(v_x1_u32r >> 12);
}
