

#include <stdint.h>
#include <stdio.h>

/*=============================================================
 * Initialize the ADC
[#] Enable clock access to GPIOA and ADC1.
[#] Set GPIO_A1 as Analog Input.
[#] Disable the ADC before configure the ADC.
[#] Set the PA1 as first in the sequence in SQ3 register.
[#] Enable the ADC (bit0)(Refer to ADC_CR2 register from above).
 *
 *
 * */
//Enable AHB1 Bus for GPIO
uint32_t volatile *pAHB1ENR =(uint32_t*)0xe40023830;

//Enable APB2 Bus for ADC
uint32_t volatile *pAPB2ENR =(uint32_t*)0xe40023844;

uint32_t volatile *pGIPOMODER =(uint32_t*)0xe40020000;
uint32_t volatile *pADC_SR =(uint32_t*)0xe40012000;
uint32_t volatile *pADC_CR2 =(uint32_t*)0xe40012008;
uint32_t volatile *pADC_SQR3 =(uint32_t*)0xe40012034;
uint32_t volatile *pADC_DR =(uint32_t*)0xe4001204c;
/*=====================================================*/
uint16_t analogValue;

/*=====================================================*/

void ADC_Init();
void delay();
/*=====================================================*/

void ADC_Init()
{
	*pAHB1ENR |= 1; //enable the clock access for GPIOA
	*pAPB2ENR |= 0x100; //enable the clock access for ADC1
	*pGIPOMODER|= 0xC;//configure GPIOA for Analog.
	*pADC_CR2 = 0;
	*pADC_SQR3 = 1;
	*pADC_CR2 |= 1;
}

void delay()
{
	for(uint32_t i=0;i<300000;i++);

}
/*=====================================================*/

int main(void)
{
	printf("Display ADC Value \n");
	ADC_Init();

	while(1)
	{
		//SWSTART Location in ADC_CR2
		*pADC_CR2 |= 0x40000000; //START ADC CONVERSION

		//EOC in ADC_SR
		while(!(*pADC_SR & 2)){} //Wait Till End of Conversion
		analogValue =*pADC_DR;
		printf("Display ADC Value %d\n",analogValue);
		delay();
	}
}

