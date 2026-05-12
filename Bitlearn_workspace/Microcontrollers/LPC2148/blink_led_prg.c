//hello
#include<LPC214x.h>

#define LED 7

void initTimer0(void)
{
	T0CTCR = 0x00;//select timer mode(by default timer mode)
	T0PR = 60000-1;//set prescaler reg value
	T0MR0 = 500-1;//set match register value
	
	T0MCR = 0x02;//configure to reset TC on MR0 matching
	
}

void delay_500ms(void)
{
	initTimer0();//initialize timer
	T0TC = 0x00;//initialize cntr value
	T0TCR = 0x01;//enable timer counter
	while((T0IR&0x01) == 1);//wait untill match interrupt occurs
	
	T0IR = 0x01;//disable the interrupt
	T0TCR = 0x00;//disable the timer counter
	
}

void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<200;j++);
}

int main()
{
	
	IO0DIR |= (1<<LED); 
	while(1)
	{
		IO0SET = (1<<LED);
		delay_ms(25000);
		//delay_500ms();
		IO0CLR = (1<<LED);
		delay_ms(25000);
		//delay_500ms();
	}

}
