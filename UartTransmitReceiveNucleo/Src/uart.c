#include "uart.h"

void Uart2_Rxtx_Init(void){

	/* Set direction of PA2/USART2_TX to Alternate function */
	GPIOA->MODER |= (1<<5);
	GPIOA->MODER &= ~(1<<4);
	/* Set direction of PA3/USART2_RX to Alternate function */
	GPIOA->MODER |= (1<<7);
	GPIOA->MODER &= ~(1<<6);
	/* Set alternate function of PA2 to USART2 */
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] |= (1<<9);
	GPIOA->AFR[0] |= (1<<10);
	GPIOA->AFR[0] &= ~(1<<11);

	/* Set alternate function of PA3 to USART2 */
	GPIOA->AFR[0] |= (1<<12);
	GPIOA->AFR[0] |= (1<<13);
	GPIOA->AFR[0] |= (1<<14);
	GPIOA->AFR[0] &= ~(1<<15);

	/* USART2 is connected to APB1 */
	/* Enabling clock for peripherals connected to bus APB1 */
	/* Enable clock for USART2 */
	RCC->APB1ENR |= USART2EN;

	/* Set Baud Rate for USART2 */
	Set_Uart_Baudrate(USART2,APB1_CLK,USART_BAUDRATE);
	/* Configure Transfer  of USART2 PA2 and PA3 direction as Tx and Rx both */
	USART2->CR1 = (CR1_TE | CR1_RE);
	/*Enable USART2*/
	USART2->CR1 |= CR1_EN;

}

void Uart_Write(int ch){

	/*Make sure Transmit Data register is empty*/
	while(!(USART2->SR & SR_TXE)){}
	/*Transmit data*/
	USART2->DR = (ch & 0xFF);

}

int Uart_Read(void){

	/* Wait till there is nothing to receive */
	while(!(USART2->SR & SR_RXNE)){}
	/* Return the read value from console */
	return USART2->DR;
}

void Set_Uart_Baudrate(USART_TypeDef *USARTx,uint32_t periph_clk, uint32_t baudrate){

	USARTx->BRR = Compute_Uart_Baudrate(periph_clk,baudrate);
}

uint16_t Compute_Uart_Baudrate(uint32_t periph_clk, uint32_t baudrate){

	return ((periph_clk + (baudrate/2))/baudrate);
}

void Delay(unsigned long ticks){

	for(unsigned long i=0;i<ticks;i++);
}

int __io_putchar(int ch){

	Uart_Write(ch);
	return ch;
}




