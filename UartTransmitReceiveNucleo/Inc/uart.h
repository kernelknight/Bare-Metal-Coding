#ifndef __UART_H
#define __UART_H

#include <stdio.h>
#include "stm32f4xx.h"

#define SYS_FREQ            16000000
#define APB1_CLK            SYS_FREQ

/* Generic Pins Macro */
#define PIN13               (1<<13)
#define PIN5                (1<<5)

/* GPIO Macros */
#define GPIOAEN             (1<<0)
#define GPIOCEN             (1<<2)

/* Push Button Macros */
#define USR_PUSH_BUTTON     PIN13

/* LED's Macros */
#define GREEN_LED           PIN5


/* USART2 Macros */
#define USART_BAUDRATE      115200
#define USART2EN            (1<<17)
#define CR1_TE              (1<<3)
#define CR1_RE              (1<<2)
#define CR1_EN              (1<<13)
#define SR_TXE              (1<<7)
#define SR_RXNE             (1<<5)

/* Functions Prototypes */
void Uart2_Rxtx_Init(void);
void Uart_Write(int);
int Uart_Read(void);
uint16_t Compute_Uart_Baudrate(uint32_t , uint32_t );
void Set_Uart_Baudrate(USART_TypeDef *,uint32_t , uint32_t );
void Delay(unsigned long);

extern uint8_t counter;


#endif
