#ifndef _I2C_DEF_
#define THRE_BIT 5
#define RDR_BIT 0

void initI2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
unsigned char i2c_write(unsigned char dat);
unsigned char i2c_ack(void);
unsigned char i2c_nack(void);
unsigned char i2c_scan(void);

unsigned char tc74_read_temp(unsigned char addr);

void initUart0(void);
void uart_tx(unsigned char);
void uart_print(char *str);
void uart_print_hex(unsigned char val);
void delay_ms(unsigned int ms);
void delay(unsigned int d);

#endif
