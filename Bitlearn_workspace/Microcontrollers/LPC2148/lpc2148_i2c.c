#include<LPC214x.h>
#include"i2c_def.h"
#define I2CSPEED 100000
#define PIN_I2C0_CFG 0x00000050
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define LOAD_VAL ((PCLK/I2CSPEED)/2)

#define I2EN (1<<6)
#define STA (1<<5)
#define STO (1<<4)
#define SI (1<<3)
#define AA (1<<2)

#define STAC (1<<5)
#define SIC (1<<3)
#define I2ENC (1<<6)
#define AAC (1<<2)

void initI2c(void)
{
	//configure i2c0 scl and sda
	PINSEL0 |= PIN_I2C0_CFG;
	I2C0SCLL = LOAD_VAL;
	I2C0SCLH = LOAD_VAL;
	I2C0CONSET = I2EN;
}

void i2c_start()
{
	I2C0CONSET = STA;
	I2C0CONCLR = SI;
	while(((I2C0CONSET>>SI)&1) == 0);
}

void i2c_stop()
{
	I2C0CONSET = STO;
	I2C0CONCLR = SIC;
	delay(1000);
}

/*void i2c_restart()
{
	I2C0CONSET |= STA;
	I2C0CONCLR |= SIC;
	while(((I2C0CONSET>>SI)&1) == 0);
	I2C0CONCLR |= STAC;
}*/

unsigned char i2c_write(unsigned char dat)
{
	I2C0DAT = dat;
	I2C0CONCLR = SIC;
	while(((I2C0CONSET>>SI)&1) == 0);
	
	if(I2C0STAT == 0x18 || I2C0STAT == 0x40)//status for w/r ack
		return 1;
	else
		return 0;
	
}

unsigned char i2c_scan(void)
{
	unsigned char addr;
	for(addr=0x48;addr <= 0x4F;addr++)
	{
		i2c_start();
		if(i2c_write(addr << 1))//send sa+w and wait for ack
		{
			return addr;
		}
		i2c_stop();
	}
	return 0xFF;
}

/*unsigned char i2c_ack(void)
{
	I2C0CONSET |= AA;
	I2C0CONCLR |= SIC;
	while(((I2C0CONSET>>SI)&1) == 0);
	return I2C0DAT;
}*/

unsigned char i2c_nack(void)
{
	I2C0CONCLR = AAC;
	I2C0CONCLR = SIC;
	while(((I2C0CONSET>>SI)&1) == 0);
	
	return I2C0DAT;
}

unsigned char tc74_read_temp(unsigned char addr)
{
	unsigned char temp;
	
	i2c_start();
	i2c_write((addr<<1)|0);
	i2c_write(0x00);
	i2c_start();
	i2c_write((addr<<1)|1);
	temp = i2c_nack();
	i2c_stop();
	
	return temp;
}





