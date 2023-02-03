

#include <stdint.h>
#include "stm32f4xx.h"


#define GPIOBEN                  (1U<<1)
#define I2C_100KHZ                80
#define SD_MODE_MAX_RISE_TIME     17

void I2C1_Init(void);

/*
 * ==========================================================
========  12C Init    =======
[1] Enable the clock access to PORT B-12C1.
[2] SET PB7 AND PB8 to alternate function.
[3] SET OUTPUTTYPE as OPEN DRAIN.
[4] SET Internal PULLUP FOR BOTH.
[5] SET THE ALTERNATE FUNCTION TYPE FOR 12C.
[6] ENTER TO RESET MODE.
[7] COME OUR OF THE RESET MODE.
[8] Set the Peripheral Clock Frequency(16 mhz).
[9] Set the Standard Mode (I2C_100KHZ).
* =============================================================
*/

void I2C1_Init(void)
{
//	[1] Enable the clock access to PORT B-12C1.
	RCC->AHB1ENR |=GPIOBEN;
	RCC->APB1ENR |=(1<<21);
//	[2] SET PB7 AND PB8 to alternate function.
	GPIOB->MODER &=~(1<<16);//Set 0
	GPIOB->MODER |=(1<<17);//Set 0
	GPIOB->MODER &=~(1<<18);//Set 0
	GPIOB->MODER |=(1<<19);//Set 0
//	[3] SET OUTPUTTYPE as OPEN DRAIN.
	GPIOB->OTYPER |=(1<<8);
	GPIOB->OTYPER |=(1<<9);
//	[4] SET Internal PULLUP FOR BOTH.
	GPIOB->PUPDR |=(1<<16);
	GPIOB->PUPDR &=~(1<<17);
	GPIOB->PUPDR |=(1<<18);
	GPIOB->PUPDR &=~(1<<19);
//	[5] SET THE ALTERNATE FUNCTION TYPE FOR 12C.
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &=~(1U<<3);
	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);
//	[6] ENTER TO RESET MODE.
	I2C1->CR1 |=(1U<<15);
//	[7] COME OUR OF THE RESET MODE.
	I2C1->CR1 &=~(1U<<15);
//	[8] Set the Peripheral Clock Frequency(16 mhz).
	I2C1->CR2 |=(1U<<4);
//	[9] Set the Standard Mode (I2C_100KHZ).
	I2C1->CCR =I2C_100KHZ;
	I2C1->TRISE =SD_MODE_MAX_RISE_TIME;
// Enable I2C1 Peripheral Enable
	I2C1->CR1 |=(1U<<0);

}
int main(void)
{
	I2C1_Init();

	while(1)
	{

	}

}
