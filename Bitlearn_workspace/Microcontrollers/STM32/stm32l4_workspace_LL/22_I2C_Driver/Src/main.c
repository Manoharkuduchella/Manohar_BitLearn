
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_drivers.h"
#include "stm32l476xx_i2c_drivers.h"
#include <string.h>


void  I2C2_inits(void);
void I2C2_GPIOInits(void);

I2C_Handle_t I2C2Handle;

int main()
{
    I2C2_GPIOInits();



	while (1) {

	}
}


void I2C2_GPIOInits(void)
{

		GPIO_Handle_t I2CPins;

		I2CPins.pGPIOx = GPIOB;

		I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
		I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
		I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
		I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
		I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

		/* PB10 -> SCL */
		I2CPins.GPIO_PinConfig.GPIO_PinNumber = 10;
		GPIO_Init(&I2CPins);

		/* PB11 -> SDA */
		I2CPins.GPIO_PinConfig.GPIO_PinNumber = 11;
		GPIO_Init(&I2CPins);
		I2C2_inits();

}

void  I2C2_inits(void)
{
	I2C2Handle.pI2Cx = I2C2;

		I2C2Handle.I2C_Config.SCLSpeed = 100000;
		I2C2Handle.I2C_Config.DeviceAddress = 0x61;
		I2C2Handle.I2C_Config.ACKControl = ENABLE;

		I2C_Init(&I2C2Handle);
}
