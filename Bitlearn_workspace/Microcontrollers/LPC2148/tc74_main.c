#include<LPC214x.h>

#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define I2C_SPEED 100000
#define LOAD_VAL ((PCLK/I2C_SPEED)/2)

#define SI   (1<<3)
#define STA  (1<<5)
#define STO  (1<<4)
#define I2EN (1<<6)
#define AA   (1<<2)

#define THRE_BIT 5
#define RDR_BIT 0

volatile unsigned char addr;
volatile unsigned char temp;

void delay(unsigned int d)
{
    while(d--);
}

void i2c_init(void)
{
    PINSEL0 |= 0x00000050;   // P0.2=SCL0, P0.3=SDA0

    I2C0SCLL = LOAD_VAL;
    I2C0SCLH = LOAD_VAL;

    I2C0CONSET = I2EN;
}

void i2c_start(void)
{
    I2C0CONSET = STA;
    I2C0CONCLR = SI;
    while(!(I2C0CONSET & SI));
}

void i2c_stop(void)
{
    I2C0CONSET = STO;
    I2C0CONCLR = SI;
    delay(1000);
}

unsigned char i2c_write(unsigned char data)
{
    I2C0DAT = data;
    I2C0CONCLR = SI;

    while(!(I2C0CONSET & SI));

 
    if(I2C0STAT == 0x18 || I2C0STAT == 0x40)//status for w/r ack
        return 1;
    else
        return 0;
}

unsigned char i2c_read_nack(void)
{
    I2C0CONCLR = AA;   // NACK
    I2C0CONCLR = SI;

    while(!(I2C0CONSET & SI));

    return I2C0DAT;
}

unsigned char tc74_read(unsigned char addr)
{
    unsigned char temp;

    i2c_start();
    i2c_write((addr << 1) | 0); // write
    i2c_write(0x00);            // temperature register

    i2c_start();                // repeated start
    i2c_write((addr << 1) | 1); // read

    temp = i2c_read_nack();

    i2c_stop();

    return temp;
}

unsigned char i2c_scan(void)
{
    unsigned char addr;

    for(addr = 0x48; addr <= 0x4F; addr++) 
    {
        i2c_start();

        if(i2c_write(addr << 1))  //send sa+w and wait for ack 
        {
            i2c_stop();
            return addr;   
        }

        i2c_stop();
    }

    return 0xFF; 
}

void initUart0(void)
{
	PINSEL0 |= 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0x0;
	U0LCR = 0x03;
	
}

void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<200;j++);
}

void uart_tx(char ch)
{
    while(((U0LSR >> THRE_BIT) & 1) == 0);
    U0THR = ch;
}

void uart_print(char *str)
{
    while(*str)
        uart_tx(*str++);
}

void uart_print_hex(unsigned char val)
{
    char hex[] = "0123456789ABCDEF";

    uart_tx(hex[(val >> 4) & 0x0F]);
    uart_tx(hex[val & 0x0F]);
}

int main()
{
	initUart0();
  i2c_init();

	addr = i2c_scan();
	while(1)
	{
		uart_print("Running:");
		if(addr != 0xFF)
		{
			temp = tc74_read(addr);
			uart_print("Temp: ");
			uart_print_hex(temp);
		}
		else
		{
			uart_print("Notfound");
		}
		uart_print("\r\n");
		delay(500);

	}
}

