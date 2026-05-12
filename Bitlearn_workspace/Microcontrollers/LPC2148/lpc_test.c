#include <LPC214x.h>
#include <stdio.h>

#define THRE_BIT 5

void UART0_Init(void)
{
    PINSEL0 |= 0x00000005;   // P0.0 TXD0, P0.1 RXD0

    U0LCR = 0x83;
    U0DLL = 97;
    U0DLM = 0;
    U0LCR = 0x03;
}

void UART0_TxChar(char ch)
{
    while (!(U0LSR & (1<<THRE_BIT)));
    U0THR = ch;
}

void UART0_TxString(char *str)
{
    while(*str)
        UART0_TxChar(*str++);
}

void delay(unsigned int d)
{
    while(d--);
}

void SPI_Init(void)
{
    // P0.4=SCK0, P0.5=MISO0, P0.6=MOSI0
    PINSEL0 |= 0x00001500;

    S0SPCR = 0x20;   // Master mode
    S0SPCCR = 32;
}

unsigned char SPI_Transfer(unsigned char data)
{
    S0SPDR = data;
    while(!(S0SPSR & 0x80));
    return S0SPDR;
}

#define CS_LOW()  (IO0CLR = (1<<7))
#define CS_HIGH() (IO0SET = (1<<7))

void EEPROM_Write(unsigned int addr, unsigned char data)
{
    CS_LOW();
    SPI_Transfer(0x06);   // WREN
    CS_HIGH();

    delay(5000);

    CS_LOW();
    SPI_Transfer(0x02);
    SPI_Transfer(addr >> 8);
    SPI_Transfer(addr);
    SPI_Transfer(data);
    CS_HIGH();

    delay(50000);
}

unsigned char EEPROM_Read(unsigned int addr)
{
    unsigned char data;

    CS_LOW();
    SPI_Transfer(0x03);
    SPI_Transfer(addr >> 8);
    SPI_Transfer(addr);
    data = SPI_Transfer(0xFF);
    CS_HIGH();

    return data;
}


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

    if(I2C0STAT == 0x18 || I2C0STAT == 0x40)
        return 1;
    else
        return 0;
}

unsigned char i2c_read_nack(void)
{
    I2C0CONCLR = AA;
    I2C0CONCLR = SI;

    while(!(I2C0CONSET & SI));

    return I2C0DAT;
}

unsigned char tc74_read(unsigned char addr)
{
    unsigned char temp;

    i2c_start();
    i2c_write((addr << 1) | 0);
    i2c_write(0x00);

    i2c_start();
    i2c_write((addr << 1) | 1);

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

        if(i2c_write(addr << 1))
        {
            i2c_stop();
            return addr;
        }

        i2c_stop();
    }

    return 0xFF;
}

int main(void)
{
    char buffer[50];
    unsigned char value, temp, addr;

    IO0DIR |= (1<<7);
    CS_HIGH();

    UART0_Init();
    SPI_Init();
    i2c_init();

    addr = i2c_scan();

while(1)
{
    UART0_TxString("---- LOOP ----\r\n");

    if(addr != 0xFF)
    {
        temp = tc74_read(addr);

        sprintf(buffer, "TC74 Temp: %d C\r\n", temp);
        UART0_TxString(buffer);

        EEPROM_Write(0x0000, temp);
        UART0_TxString("Stored in EEPROM\r\n");

        value = EEPROM_Read(0x0000);

        sprintf(buffer, "EEPROM Value: %d C\r\n", value);
        UART0_TxString(buffer);
    }
    else
    {
        UART0_TxString("TC74 Not Found\r\n");
    }

    UART0_TxString("\r\n");
    delay(30000000);
}
}
