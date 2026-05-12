#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_rcc.h"

void SysTick_Handler(void);
void uart1_init(void);

//UART1 <-> APB1
//USART_TX - PA9
//USART_RX - PA10

UART_HandleTypeDef huart1;

uint8_t tx_buffer[10] = {10,20,30,40,50,60,70,80,90,100};
uint8_t rx_buffer[10];

uint32_t rx_cnt,tx_cnt;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	tx_cnt++;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rx_cnt++;
}


int main() {
	HAL_Init();
	uart1_init();

	HAL_UART_Transmit_IT(&huart1, tx_buffer, 10);
	HAL_UART_Receive_IT(&huart1, rx_buffer,10);

	while (1) {
	}
}

void SysTick_Handler(void) {
	HAL_IncTick();
}

void uart1_init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//enable UART pins clock access
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Enable UART module clock access
	__HAL_RCC_USART1_CLK_ENABLE();

	//Configure pins to act as alternate func pins(UART)
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	//GPIO_AF7_USART3
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//configure UART module
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	//HwFlowCtl and Oversampling not present

	HAL_UART_Init(&huart1);

	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

}




void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

