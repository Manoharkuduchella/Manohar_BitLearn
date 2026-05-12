#include <lpc214x.h>
#include <stdio.h>

void delay(void)
{
    int i;
    for(i=0;i<200000;i++);
}

void UART0_Init(void)
{
	
		PINSEL0 |= 0x00000005;

    U0LCR = 0x83;

    U0DLL = 97;  
    U0DLM = 0;

    U0LCR = 0x03;
}

void UART0_TxChar(char ch)
{
    while (!(U0LSR & 0x20));
    U0THR = ch;
}

void UART0_TxString(char *str)
{
    while(*str)
    {
        UART0_TxChar(*str++);
    }
}


void SPI_Init(void)
{
    PINSEL0 &= ~0x0000FF00;
    PINSEL0 |=  0x00001500;

    S0SPCR = 0x20;   // Master
    S0SPCCR = 32;    // slower clock
}

unsigned char SPI_Transfer(unsigned char data)
{
    S0SPDR = data;
    while(!(S0SPSR & 0x80));
    return S0SPDR;
}


void EEPROM_Write(unsigned int addr, unsigned char data)
{
    // ?? Step 1: Write Enable
    IO0CLR = (1<<7);
    SPI_Transfer(0x06);   // WREN
    IO0SET = (1<<7);

    delay();   // ?? VERY IMPORTANT

    // ?? Step 2: Actual Write
    IO0CLR = (1<<7);

    SPI_Transfer(0x02);   // WRITE
    SPI_Transfer(addr >> 8);
    SPI_Transfer(addr);
    SPI_Transfer(data);

    IO0SET = (1<<7);

    delay();   // ?? WRITE cycle time
}


unsigned char EEPROM_Read(unsigned int addr)
{
    unsigned char data;

    IO0CLR = (1<<7);

    SPI_Transfer(0x03);   // READ command
    SPI_Transfer(addr >> 8);
    SPI_Transfer(addr);

    data = SPI_Transfer(0xFF);

    IO0SET = (1<<7);

    return data;
}



int main(void)
{
    char buffer[50];
    unsigned char value;
    unsigned int i;   

    PINSEL0 |= 0x00001500;   
    IO0DIR |= (1<<7);        
    IO0SET = (1<<7);         

    UART0_Init();
    SPI_Init();

    while(1)
    {
        UART0_TxString("Writing...\r\n");

        EEPROM_Write(0x0000, 55);   
        delay();

        UART0_TxString("Reading...\r\n");

        value = EEPROM_Read(0x0000);

        sprintf(buffer, "Value = %d\r\n", value);
        UART0_TxString(buffer);

        for(i=0;i<3000000;i++);
    }
}
