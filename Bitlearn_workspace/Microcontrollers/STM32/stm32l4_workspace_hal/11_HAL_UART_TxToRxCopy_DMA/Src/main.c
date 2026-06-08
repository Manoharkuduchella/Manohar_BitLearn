#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_rcc.h"


void SysTick_Handler(void);
void uart1_init(void);

//UART1 <-> APB1
//USART_TX - PA9
//USART_RX - PA10

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

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

	HAL_UART_Transmit_DMA(&huart1, tx_buffer, 10);
	HAL_UART_Receive_DMA(&huart1, rx_buffer,10);

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

	//Enable DMA1 module clock access
	__HAL_RCC_DMA1_CLK_ENABLE();

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

	//configure USART1 RX DMA
	hdma_usart1_rx.Instance = DMA1_Channel5;
	hdma_usart1_rx.Init.Request = DMA_REQUEST_2;
	hdma_usart1_rx.Init.Mode = DMA_NORMAL;
	hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;


	HAL_DMA_Init(&hdma_usart1_rx);

	//Link usart1 rx to DMA
	__HAL_LINKDMA(&huart1,hdmarx,hdma_usart1_rx);


	//configure USART1 TX DMA
	hdma_usart1_tx.Instance = DMA1_Channel4;
	hdma_usart1_tx.Init.Request = DMA_REQUEST_2;
	hdma_usart1_tx.Init.Mode = DMA_NORMAL;
	hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;


	HAL_DMA_Init(&hdma_usart1_tx);

	//Link usart1 tx to DMA
	__HAL_LINKDMA(&huart1,hdmatx,hdma_usart1_tx);

	//DMA1_Channel4_IRQn Interrupt configuration
	HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);


	//DMA1_Channel5_IRQn Interrupt configuration
	HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

	//DMA1_CH4_IRQHandler

}

void DMA1_CH5_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_usart1_rx);
}


void DMA1_CH4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_usart1_tx);
}



void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

