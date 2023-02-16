
#include <stdint.h>
#include "stm32f4xx.h"

/*=========================================================================================*/

void UART_Init(void);
char UART_Read(void);
void UART_Write(char data);

char UART_Read()
{
	while(!(USART1->SR & 0x0020)){}
	return USART1->DR;
}

void UART_Write(char data)
{
	while(!(USART1->SR & 0x0080)){}
	USART1->DR = (data&0xff);
}

void UART_Init()
{
	//enable the clock access for GPIOA, GPIOB
	RCC->AHB1ENR |=(1U<<0); //GPIO A
	RCC->AHB1ENR |=(1U<<1); //GPIO B
	RCC->APB2ENR |=(1U<<4); //USART1

	//Set Alternative Function For PB6->TX and PB7->RX
	GPIOB->MODER |=(1U<<13);
	GPIOB->MODER &=~(1U<<12);
	GPIOB->MODER |=(1U<<15);
	GPIOB->MODER &=~(1U<<14);

	//Set PA5 is output connected to Relay
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	GPIOB->AFR[0] |=(1U<<24);
	GPIOB->AFR[0] |=(1U<<25);
	GPIOB->AFR[0] |=(1U<<26);
	GPIOB->AFR[0] &=~(1U<<27);

	GPIOB->AFR[0] |=(1U<<28);
	GPIOB->AFR[0] |=(1U<<29);
	GPIOB->AFR[0] |=(1U<<30);
	GPIOB->AFR[0] &=~(1U<<31);

	USART1->CR1 |=(1U<<13);
	USART1->CR1 |=(1U<<2);
	USART1->CR1 |=(1U<<3);

	USART1->BRR =0x0683; //9600 Baud Rate
}


int main(void)
{
	char Data;
	UART_Init();
//	UART_Write('A');
	while(1)
	{
		Data = UART_Read();
		if(Data == 'A')
		{
			GPIOA->ODR |=(1U<<5);
			UART_Write(Data);

		}
		else
		{
			GPIOA->ODR &=~(1U<<5);
			UART_Write(Data);

		}

	}

}
