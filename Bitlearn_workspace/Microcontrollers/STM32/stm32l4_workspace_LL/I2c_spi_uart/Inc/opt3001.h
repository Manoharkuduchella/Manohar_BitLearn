/*
 * opt3001.h
 *
 *  Created on: May 20, 2026
 *      Author: manohar kuduchella
 */

#ifndef OPT3001_H_
#define OPT3001_H_

/*
 * opt3001.c
 *
 *  Created on: May 20, 2026
 *      Author: manohar kuduchella
 */
#include "stm32l476xx.h"
#include "stm32l476xx_i2c_drivers.h"
#include "stm32l476xx_gpio_drivers.h"



#define OPT3001_ADDR               0x47

/* ================= REGISTER MAP ================= */

#define OPT3001_REG_RESULT         0x00
#define OPT3001_REG_CONFIG         0x01
#define OPT3001_REG_LOWLIMIT       0x02
#define OPT3001_REG_HIGHLIMIT      0x03
#define OPT3001_REG_MANFID         0x7E
#define OPT3001_REG_DEVICEID       0x7F


//WRITE REGISTER
void OPT3001_WriteReg(I2C_Handle_t *pI2CHandle, uint8_t reg, uint16_t value);

//READ REGISTER
uint16_t OPT3001_ReadReg(I2C_Handle_t *pI2CHandle, uint8_t reg);

//SENSOR INIT
void OPT3001_Init(I2C_Handle_t *pI2CHandle);

//READ LUX
int OPT3001_ReadLux(I2C_Handle_t *pI2CHandle);


#endif /* OPT3001_H_ */
