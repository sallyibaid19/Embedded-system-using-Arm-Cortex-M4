

#include <stdint.h>
#include <stdio.h>

//Enable AHB1 Bus for GPIO
uint32_t volatile *pAHBIENR =(uint32_t*)0xe40023830;

//Enable APB2 Bus for EXIT
uint32_t volatile *pAPB2ENR =(uint32_t*)0xe40023844;

//Enable PORT C
uint32_t volatile *pGPIOC =(uint32_t*)0xe40020800;

uint32_t volatile *pEXTIPR =(uint32_t*)0x40013c14; //pending reg.
uint32_t volatile *pEXTIMR =(uint32_t*)0x40013c00; //mask reg.
uint32_t volatile *pEXTIFTSR =(uint32_t*)0x40013c0c; //falling edge
uint32_t volatile *pSYSCFG_EXTICR4  =(uint32_t*)0x40013814;

uint32_t volatile *pNVIC_ISER1  =(uint32_t*)0xe000e104;

void Button_Init(void)
{
	*pAHBIENR |=(1U<<2); //enable gpio c
	*pAPB2ENR |=(1U<<14); //enable sysconfig
	*pSYSCFG_EXTICR4 |=(1U<<5); //assist confige exit_13
	*pEXTIFTSR |=(1U<<13);//falling edge
	*pEXTIMR |=(1U<<13);//
	*pNVIC_ISER1 |=(1U<<8);

}

int main(void)
{
	Button_Init();

	while(1)
	{

	}
}

//copied from startup code
void EXTI15_10_IRQHandler(void)
{
	printf("Button is pressed \n");
	*pEXTIPR |=(1U<<13);

}
