/* Board used:  DISCOVERY-F407G- DISC1
   Application: Toggle all 4 user LED's in circular manner with a delay.

   Programming Style: Bare Metal.
*/

/* Pins:
 * USR_LED       : PD12,PD13,PD14,PD15: Green, Orange, Red, Blue.
*/

#include "stm32f4xx.h"

#define SET_BIT(REG,BIT)          (REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)          (REG &= ~(1<<BIT))
#define TOGGLE_BIT(REG,BIT)       (REG |= (1<<BIT))


void Delay(unsigned long);



int main(){

	    /*Enable clock to GPIOD by setting bit 3*/
		SET_BIT(RCC->AHB1ENR,3);
		/*Setting direction of PD12 as output*/
		SET_BIT(GPIOD->MODER,24);
		/*Setting direction of PD13 as output*/
		SET_BIT(GPIOD->MODER,26);
		/*Setting direction of PD14 as output*/
		SET_BIT(GPIOD->MODER,28);
		/*Setting direction of PD15 as output*/
		SET_BIT(GPIOD->MODER,30);


		while(1){

			SET_BIT(GPIOD->ODR,12);
			Delay(100000);
			CLR_BIT(GPIOD->ODR,12);
			Delay(100000);
			SET_BIT(GPIOD->ODR,13);
			Delay(100000);
			CLR_BIT(GPIOD->ODR,13);
			Delay(100000);
			SET_BIT(GPIOD->ODR,14);
			Delay(100000);
			CLR_BIT(GPIOD->ODR,14);
			Delay(100000);
			SET_BIT(GPIOD->ODR,15);
			Delay(100000);
			CLR_BIT(GPIOD->ODR,15);
			Delay(100000);

		}

	return 0;
}

void Delay(unsigned long ticks){

	for(unsigned long i=0;i<ticks;i++);
}

