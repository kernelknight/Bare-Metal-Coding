#include "uart.h"


/* Board used: NUCLEO-F401RE
   Application: If user presses '1', USART should go in transmit mode.
                In Transmit mode:
                while '1' is pressed toggle User LED on while User push button is pressed.
                Number of toggles should be transmitted to COM(RealTerm)
                via UART2(can be used directly without a converter).
                If user presses '0', USART should go in receive mode.
                In Receiver mode:
                While '0' is pressed, toggle the green light.

   Programming Style: Bare Metal.
*/

/* Pins:
 * USART2_TX     : PA2/D1
 * USART2_RX     : PA3/D0
 * USR_LED       : PA5/D13
 * USR_PUSH_BTN  : PC13
*/


/* Global variables */
uint8_t counter = 0;
uint8_t key = 254;

int main(void){

	/* All GPIOS connected to AHB1 */
	/* Enabling clock for peripherals connected to bus AHB1 */
	/* Enable clock for GPIOA */
	RCC->AHB1ENR |= GPIOAEN;
	/* Enable clock for GPIOA */
	RCC->AHB1ENR |= GPIOCEN;

	/* Set direction of PA5/Green User Led to out */
	GPIOA->MODER |= (1<<10);
	GPIOA->MODER &= ~(1<<11);
	/* Set direction of PC13/User Push Button to In */
	GPIOC->MODER &= ~(1<<26);
	GPIOC->MODER &= ~(1<<27);

	/* Initialize USART2 */
	Uart2_Rxtx_Init();

	while(1){

        key = Uart_Read();
        /* Transmit mode on only once '1' is pressed from terminal */
		if(key == '1'){
			/*Check if PC13 is pressed*/
			if(!(GPIOC->IDR & USR_PUSH_BUTTON)){
			  GPIOA->ODR ^= GREEN_LED;
			  Delay(10000);
			  counter++;
			  printf("\n Current count : %d",counter);

		    }
			else{
			  GPIOA->ODR &= ~GREEN_LED;
			}
		}
		/* Receiver mode is on once user presses '0' from terminal */
		else if(key == '0'){
			 /* Toggle Grren LED */
			 GPIOA->ODR ^= GREEN_LED;
			 Delay(1000000);
		}
		else{
			/* Led turns off once user enters any other key from terminal */
			GPIOA->ODR &= ~GREEN_LED;
		}

	}

	return 0;
}



