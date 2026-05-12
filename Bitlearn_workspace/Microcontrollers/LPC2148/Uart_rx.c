#include<LPC214x.h>
#define RDR_BIT 0

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
	char ch=0;
	initUart0();
	while(1)
	{
		while(((U0LSR>>RDR_BIT)&1) == 0);
		ch = U0RBR;
		
	}
}
