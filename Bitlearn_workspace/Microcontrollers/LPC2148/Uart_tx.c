#include<LPC214x.h>
#define THRE_BIT 5

void initUart0(void)
{
	PINSEL0 |= 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0x0;
	U0LCR = 0x03;
	
}

int main()
{
	initUart0();
	while(1)
	{
		while(((U0LSR>>THRE_BIT)&1) == 0);
		U0THR = 'b';
		
	}
}
