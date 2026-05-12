#include <lpc214x.h>
#include <stdio.h>

// ===== UART =====
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
    while (!(U0LSR & (1<<5)));
    U0THR = ch;
}

void UART0_TxString(char *str)
{
    while(*str)
        UART0_TxChar(*str++);
}

// ===== Delay =====
void delay(int n)
{
    int i;
    for(i=0;i<n*100000;i++);
}

// ===== I2C Defines =====
#define SI   (1<<3)
#define STA  (1<<5)
#define STO  (1<<4)
#define I2EN (1<<6)
#define AA   (1<<2)

// ===== I2C Init =====
void I2C_Init(void)
{
    PINSEL0 |= 0x00000050;   

    I2C0SCLH = 300;
    I2C0SCLL = 300;

    I2C0CONSET = I2EN;
}

// ===== START =====
void I2C_Start(void)
{
    I2C0CONSET = STA;
    I2C0CONCLR = SI;
    while(!(I2C0CONSET & SI));
}

// ===== STOP =====
void I2C_Stop(void)
{
    I2C0CONSET = STO;
    I2C0CONCLR = SI;
    delay(10);
}

// ===== WRITE =====
int I2C_Write(unsigned char data)
{
    I2C0DAT = data;
    I2C0CONCLR = SI;

    while(!(I2C0CONSET & SI));

    if(I2C0STAT == 0x18 || I2C0STAT == 0x28 || I2C0STAT == 0x40)
        return 1;
    else
        return 0;
}

// ===== READ (NACK) =====
unsigned char I2C_Read_NACK(void)
{
    I2C0CONCLR = AA;
    I2C0CONCLR = SI;

    while(!(I2C0CONSET & SI));

    return I2C0DAT;
}

// ===== LM75 READ =====
unsigned char LM75_Read(unsigned char addr)
{
    unsigned char temp;

    I2C_Start();

    // SLA + W
    if(!I2C_Write((addr<<1) | 0))
    {
        I2C_Stop();
        return 0xFF;
    }

    // Pointer = TEMP (0x00)
    I2C_Write(0x00);

    // REPEATED START
    I2C_Start();

    // SLA + R
    if(!I2C_Write((addr<<1) | 1))
    {
        I2C_Stop();
        return 0xFF;
    }

    // Read one byte
    temp = I2C_Read_NACK();

    I2C_Stop();

    return temp;
}

// ===== I2C SCAN =====
unsigned char I2C_Scan(void)
{
    unsigned char addr;

    for(addr = 0x48; addr <= 0x4F; addr++)
    {
        I2C_Start();

        if(I2C_Write(addr<<1))
        {
            I2C_Stop();
            return addr;
        }

        I2C_Stop();
    }

    return 0xFF;
}

// ===== MAIN =====
int main(void)
{
    char buffer[50];
    unsigned char addr;
    unsigned char temp;

    VPBDIV = 0x01;

    UART0_Init();
	
		UART0_TxString("Running\r\n");
	
    I2C_Init();

    addr = I2C_Scan();

    while(1)
    {
        if(addr != 0xFF)
        {
            temp = LM75_Read(addr);

            sprintf(buffer, "Temp = %d C\r\n", temp);
            UART0_TxString(buffer);
        }
        else
        {
            UART0_TxString("Sensor Not Found\r\n");
        }

        delay(20);
    }
}
