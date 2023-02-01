

#include <stdint.h>
#include "stm32f4xx.h"

//PWM i a way to control analog devices with a digital output.

int main(void)
{
	//Enable The clock access for GPIOA
	RCC->AHB1ENR |=0x01;//Enale clock for GPIOA
	//Enable The clock access for TIM2
	RCC->APB1ENR |=0x01;
	//SET the GPIOA MODE Register For Alternative Function.
	GPIOA->MODER |=0x00000800;//Alternative Function MODE.
	//AFR
	GPIOA->AFR[0] |=0x00100000;
	TIM2->PSC = 10-1;//Divide TIMER CLK by 10.
	TIM2->ARR = 16667-1;
	TIM2->CNT =0;
	TIM2->CCMR1 = 0x0060; //Enable PWM MODE.
	TIM2->CCER = 1; //Enable PWM CH1.
	TIM2->CCR1 = 8889-1;
	TIM2->CR1 = 1; //Enable THE TIMER.
	while(1)
	{

	}

}
