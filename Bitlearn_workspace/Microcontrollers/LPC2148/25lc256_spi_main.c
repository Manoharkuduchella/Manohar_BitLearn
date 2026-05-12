#include<LPC214x.h>

#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)

#define SPCCR_VAL 60 //500khz <--- PCLk/30 
#define SPI_MODE0 0x00
#define SPI_MODE1 (1<<3)
#define SPI_MODE2 (1<<4)
#define SPI_MODE3 (3<<3)

#define _8BITS (0x8<<8)
#define _9BITS (0x9<<8)

#define READ 0x03
#define WRITE 0x02
#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01

#define MSTR_MODE (1<<5)

#define CS (1<<7)
#define SPIF 7


#define THRE_BIT 5
#define RDR_BIT 0

void initUart0(void)
{
	PINSEL0 |= 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0x0;
	U0LCR = 0x03;
	
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

void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<200;j++);
}

void init_spi()
{
	PINSEL0 |= 0x00001500;//SCK|MISO|MOSI
	S0SPCCR = SPCCR_VAL;
	S0SPCR = MSTR_MODE;
	IO0DIR |= CS;
	IO0SET |= CS;//set default value as 1 to cs line
	
	
}

unsigned char spi0(unsigned char dat)
{
	S0SPDR = dat;
	while(((S0SPSR>>SPIF)&1) == 0);
	return S0SPDR;
}

unsigned char read_status()
{
    unsigned char status;

    IO0CLR = CS;
    spi0(RDSR);
    status = spi0(0xFF);
    IO0SET = CS;

    return status;
}

void LC256_cmd(unsigned char cmd)
{
	IO0CLR = CS;
	spi0(cmd);
	IO0SET = CS;
}

void spi_byte_write(unsigned short int addr,unsigned char byte)
{
	LC256_cmd(WREN);
	
	delay_ms(1);
	
	IO0CLR = CS;
	spi0(WRITE);
	spi0(addr>>8);
	spi0(addr);
	spi0(byte);
	IO0SET = CS;
	delay_ms(10);
	
	LC256_cmd(WRDI);
}

unsigned char spi_byte_read(unsigned short int addr)
{
	unsigned char dat;
	IO0CLR = CS;
	
	spi0(READ);
	spi0(addr>>8);
	spi0(addr);
	dat = spi0(0xFF);
	
	IO0SET = CS;
	return dat;
}

unsigned char ch;

int main()
{
	initUart0();
	init_spi();
	
	uart_print("Status before WREN: ");
	uart_print_hex(read_status());
	uart_print("\r\n");

	LC256_cmd(WREN);

	uart_print("Status after WREN: ");
	uart_print_hex(read_status());
	uart_print("\r\n");
	
	uart_print("Writing...\r\n");
	spi_byte_write(0x0000,'a');
	delay_ms(100);
	ch = spi_byte_read(0x0000);
	delay_ms(100);
	if(ch == 'a')
	{
		uart_print_hex(ch);
		uart_print("\r\n");
		uart_print("Write and read done...");
	}
	else
	{
		uart_print_hex(ch);
		uart_print("\r\n");
		uart_print("Write and read failed...");
	}
	
	while(1);
	
}
