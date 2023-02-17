
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include <string.h>


/*========================================================================================*/

unsigned char command_basic_1[5]="AT\r\n"; // BASIC
unsigned char command_basic_2[9]="AT+RST\r\n"; //BASIC

unsigned char command_ESP_1[14]="AT+CWMODE=1\r\n"; //WIFI
unsigned char command_ESP_2[14]="AT+CWQAP\r\n"; //WIFI
unsigned char command_ESP_4[25]="AT+CWDHCP=1,1\r\n"; //THINGS SPEAK

unsigned char command_ESP_3[50]="AT+CWJAP=\"warriorsway\",\"12345678\"\r\n";//WIFI ACC [PASSWORD]

unsigned char command_ESP_5[50]="AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n";
unsigned char command_ESP_6[20]="AT+CIPSEND=64\r\n";
unsigned char command_ESP_7[64]="GET /update?api_key=J4467UDKM1YL0EXH&field1=" ;
unsigned char command_ESP_8[9]="&field2=";
unsigned char command_ESP_9[9]="\r\n\r\n";
unsigned char command_ESP_10[20]="AT+CIPCLOSE \r\n";
unsigned char data_string[8];

/*========================================================================================*/

void UART_Init(void);
char UART_Read(void);
void UART_Write(char data);
int __io__putchar(char ch);
void Basic_Commands (void);
void Wifi_Conn_Commands (void);
void Delay_ms(int delay);
void integer_to_ascii (unsigned int Val, unsigned char *str);

void Init_ESP8266 (void);
void Wifi_acc(void);
void Data_Commands();
void Thing_Speak_Command_Start(void);

/*========================================================================================*/
void Basic_Commands (void)
{
	//UARTO Print (command_basic_1); >> "AT\r\n"; // BASIC
	printf("%s", command_basic_1);

	Delay_ms(500);
	printf("%s", command_basic_2);

	//UARTO Print (command_basic_2); >> "AT+RST\r\n"; //BASIC
	Delay_ms(1000);
}

void Wifi_Conn_Commands (void)
{
	//UARTO Print (command_ESP_1); >> "AT+CWMODE=1\r\n"; //WIFI
	 printf("%s", command_ESP_1);
	 Delay_ms(500);
	 //UARTO Print (command_ESP_2); >>"AT+CWQAP\r\n"; //WIFI
	 printf("%s", command_ESP_2);
	 Delay_ms(500);
}

void Wifi_acc(void)
 {
//UARTO_Print (command_ESP_3);>>
//"AT+CWJAP=\"warriorsway\",\"12345678\"\r\n";//WIFI ACC [PASSWORD]
	 printf("%s", command_ESP_3);
	 Delay_ms(8000);
}

void Thing_Speak_Command_Start(void)
{
	//UARTO Print (command_ESP_4); >>"AT+CWDHCP=1,1\r\n"; //THINGS SPEAK
	 printf("%s", command_ESP_4);
	 Delay_ms(5000);
}

void Data_Commands()
{
	//"AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n";
	printf("%s", command_ESP_5);
	 Delay_ms(5000);

	 //"AT+CIPSEND=64\r\n";
	 printf("%s", command_ESP_6);
	 Delay_ms(5000);
	// "GET /update?api_key=J4467UDKM1YL0EXH&field1=" ;
	 printf("%s", command_ESP_7);
	 printf("%s", data_string);
	 //"\r\n\r\n";
	 printf("%s", command_ESP_9);
	 Delay_ms(1000);
	 //"AT+CIPCLOSE \r\n";
	 printf("%s", command_ESP_10);
	 Delay_ms(5000);
}
void Init_ESP8266 (void)
{
	Delay_ms(5000);
	Basic_Commands();
	Wifi_Conn_Commands();
}


void integer_to_ascii (unsigned int Val, unsigned char *str)
{
 str[0] = Val/1000 + 0x30;
 Val    = Val%1000;
 str[1] = Val/100+ 0x30;
 Val    = Val%100;
 str[2] = Val/10 + 0x30;
 str[3] = Val%10 + 0x30;
 str[4] = '\0';
}

void Delay_ms(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++)
		{

		}
	}


}
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
//	RCC->AHB1ENR |=(1U<<0); //GPIO A
	RCC->AHB1ENR |=(1U<<1); //GPIO B
	RCC->APB2ENR |=(1U<<4); //USART1

	//Set Alternative Function For PB6->TX and PB7->RX
	GPIOB->MODER |=(1U<<13);
	GPIOB->MODER &=~(1U<<12);
	GPIOB->MODER |=(1U<<15);
	GPIOB->MODER &=~(1U<<14);

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

	USART1->BRR =0x008B; //115200 Baud Rate
}

int __io__putchar(char ch)
{
	UART_Write(ch);
	return ch;
}



int main(void)
{
	char Data;
	unsigned int Data_Adc;

	UART_Init();
	Init_ESP8266();
	//WIFI Account & Password
	Wifi_acc();
    //Thing Speak Command
	Thing_Speak_Command_Start();
	 Delay_ms(500);
	 Data_Adc = 30;
	 //integer to ASCII
	 integer_to_ascii(Data_Adc,data_string);
	 //Data Command
	 Data_Commands();
	 Delay_ms(500);
	 Thing_Speak_Command_Start();
	 Delay_ms(500);
	 Data_Adc = 60;
	 //integer to ASCII
	 integer_to_ascii(Data_Adc,data_string);
	 //Data Command
	 Data_Commands();
	 Delay_ms(500);
	 printf("\n END \n");
	 for(;;);

}
