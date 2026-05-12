
#ifndef LED_H_
#define LED_H_

//USR_BUTTON = PC13 --> AHB2 EN bit 2

#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_5

void pa5_led_init(void);

#endif /* LED_H_ */
