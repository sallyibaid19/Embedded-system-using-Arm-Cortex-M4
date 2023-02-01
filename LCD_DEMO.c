

#include <stdint.h>
#include "stm32f4xx.h"

#define RS 0x20  //0010 0000
#define RW 0x40  //0100 0000
#define EN 0x80  //1000 0000
// PB5>>RS
// PB6 >>RW
// PB7 >>EN
// PC0 - PC7 >>D0-D7 IN LCD
unsigned char Message[]=("SALLY...");
void GPIO_Init(void);
void LCD_Command(unsigned char command);
void LCD_Data(unsigned char data);
void LCD_Init(void);
void delayMs(int delay);

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++)
		{

		}
	}
}
void GPIO_Init(void)
{
	//Set RCC AHB1ENR
	RCC->AHB1ENR |=0x06;//Enale clock for GPIOB-GPIOC.
	//set GPIOB MODE REGISTER AS O/P
	GPIOB->MODER |=0x5400;//OUTPUT MODE.
	//SET BSRR OF GPIOB AS LOW
	GPIOB->BSRR |=0x00C; //set EN and RW low.
	//set GPIOB MODE REGISTER AS O/P
	GPIOC->MODER |=0x00005555;//FROM C0 TO C7 BIT ARE OUTPUT MODE.
}
void LCD_Command(unsigned char command)
{
	//RS=0 RW=0
	GPIOB->BSRR =(RS|RW)<<16;
	GPIOC->ODR =command;
	//EN = 1
	GPIOB->BSRR =EN; //Enable EN.
	delayMs(30);
	GPIOB->BSRR =EN<<16;//CLEAR EN
}
void LCD_Data(unsigned char data)
{
	//RS=1 RW=0
	GPIOB->BSRR =RS;
	GPIOB->BSRR =RW<<16;
	GPIOC->ODR =data;
	//EN = 1
	GPIOB->BSRR =EN; //Enable EN.
	delayMs(30);
	GPIOB->BSRR =EN<<16;//CLEAR EN
	delayMs(30);
}
void LCD_Init(void)
{
	unsigned char i=0;
	GPIO_Init();
	LCD_Command(0x38); //16x2
	delayMs(20);
	LCD_Command(0x0c); //set bit data mode.
	delayMs(20);
	LCD_Command(0x06); //move the cursor right.
	delayMs(20);
	LCD_Command(0x01); //clear screen move cursor home.
	delayMs(20);
	delayMs(100);
	LCD_Command(0x80); //turn display.
	delayMs(20);
	while(Message[i]!='\0')
	{
		LCD_Data(Message[i]);
		i++;
	}
	delayMs(50);
}
int main(void)
{
	LCD_Init();
    /* Loop forever */
	for(;;);
}
