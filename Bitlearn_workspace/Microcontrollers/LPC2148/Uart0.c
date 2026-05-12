#include<LPC214x.h>
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

void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<200;j++);
}

void delay(unsigned int d)
{
    while(d--);
}


void uart_tx(char ch)
{
    while(((U0LSR >> THRE_BIT) & 1) == 0);
    U0THR = ch;
}

unsigned char uart_rx()
{
	while(((U0LSR>>RDR_BIT)&1) == 0);
	return U0RBR;
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

/*{
	char ch;
	initUart0();
	while(1)
	{
		while(((U0LSR>>RDR_BIT)&1) == 0);
		ch = U0RBR;
		
		while(((U0LSR>>THRE_BIT)&1) == 0);
		U0THR = ch+1;
	}
}*/
