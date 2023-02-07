

#include <stdint.h>
#include "stm32f4xx.h"

/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
#define GPIOBEN                  (1U<<1)
#define I2C1EN                   (1U<<21)
#define I2C_100KHZ                80 //FAST MODE
#define SD_MODE_MAX_RISE_TIME     17

//I2C control Register 1
#define CR1_START                (1U<<8)
#define CR1_PE                   (1U<<0)  //Peripheral Enable
#define CR1_ACK                  (1U<<10)
#define CR1_STOP                 (1U<<9)

//I2C Status Register [SR1]
#define SR1_SB                   (1U<<0)
#define SR1_ADDR                 (1U<<1)  //Peripheral Enable
#define SR1_TXE                  (1U<<7)  //Data Register Empty (Transmitter)
#define SR1_RXNE                 (1U<<6)  //Data Register Not Empty (Receiver)
#define SR1_BTF                  (1U<<2)

#define SR2_BUSY                 (1U<<1) //Status Register [SR2]

//ADXL345 MACROS
#define DEVID_R                  (0X00)
#define DATA_FORMAT_R            (0X31)
#define POWER_CTL_R              (0X2D)
#define DATA_START_ADDR          (0X32)
#define DEVICE_ADDR              (0X53)

#define FOUR_G                   (0X01)
#define RESET                    (0X00)
#define SET_MEASURE_B            (0X08)

/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
uint8_t data_rec[6];
uint16_t x,y,z;
float xg,yg,zg;
char data;

/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
void I2C1_Init(void);
void I2C1_ByteRead(char SlaveAddress,char MemoryAddress,char* data);
void I2C1_BurstRead(char SlaveAddress,char MemoryAddress,int n,char* data);
void I2C1_BurstWrite(char SlaveAddress,char MemoryAddress,int n,char* data);
void adx1_read_values(uint8_t reg);
void adx1_read_address(uint8_t reg);
void adx1_write(uint8_t reg,char value);
void adx1_Init(void);

/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
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

/*###############################################################*/
/*###############################################################*/
/*###############################################################*/

int main(void)
{
	adx1_Init();

	while(1)
	{
		adx1_read_values(DATA_START_ADDR);
		x = ( (data_rec[1]<<8) | (data_rec[0]) );
		y = ( (data_rec[3]<<8) | (data_rec[2]) );
		z = ( (data_rec[5]<<8) | (data_rec[4]) );

		xg = (x*0.0078);
		yg = (y*0.0078);
		zg = (z*0.0078);
		//printf("%f \n",xg);
		//printf("%f \n",yg);
		//printf("%f \n",zg);


	}

}
/*###############################################################*/
void adx1_Init(void)
{
	I2C1_Init();
	adx1_read_address(DEVID_R);
	adx1_write(DATA_FORMAT_R,FOUR_G);
	//Reset All The Bits
	adx1_write(POWER_CTL_R,RESET);
	adx1_write(POWER_CTL_R,SET_MEASURE_B);

}
/*###############################################################*/
void adx1_read_values(uint8_t reg)
{
	I2C1_BurstRead(DEVICE_ADDR,reg,6,(char*)data_rec);
}
/*###############################################################*/
void adx1_write(uint8_t reg,char value)
{
	char data[1];
	data[0] = value;
	I2C1_BurstWrite(DEVICE_ADDR,reg,1, &data);

}
/*###############################################################*/
void adx1_read_address(uint8_t reg)
{
	I2C1_ByteRead(DEVICE_ADDR,reg, &data);
}
/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
void I2C1_Init(void)
{
//	[1] Enable the clock access to PORT B-12C1.
	RCC->AHB1ENR |=GPIOBEN;
//	RCC->APB1ENR |=(1<<21);
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

	RCC->APB1ENR |=I2C1EN;
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
	I2C1->CR1 |=CR1_PE ;//(1U<<0)

}
/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
void I2C1_ByteRead(char SlaveAddress,char MemoryAddress,char* data)
{
	volatile int tmp;
	//[1] Wait Until Bus is not Busy.
	while(I2C1->SR2 & (SR2_BUSY)) {}

	//	[2] Generate Start Condition.
	I2C1->CR1|=CR1_START;

	//	[3] Wait Until The Start Flag is Set.
	while(!(I2C1->SR1 & (SR1_SB))) {}

	//	[4] Transmit Slave Address + Write.
	I2C1->DR= SlaveAddress<<1;

	//	[5] Wait Until The Address Flag is Set.
	while(!(I2C1->SR1 & (SR1_ADDR))) {}

	//	[6] Clear The Address Flag.
	tmp = I2C1->SR2;

	//	[7] Send Memory Address.
	I2C1->DR= MemoryAddress;

	//	[8] Wait Until The Transmitter is Empty.
	while(!(I2C1->SR1 & (SR1_TXE))) {}

	//	[9] Generate Restart.
	I2C1->CR1 |= CR1_START ;

	//	[10] Wait Until The Start Flag is Set.
	while(!(I2C1->SR1 & (SR1_SB))) {}

	//	[11] Transmit Slave Address + Write.
	I2C1->DR= SlaveAddress<<1;

	//	[12] Wait Until The Address Flag is Set.
	while(!(I2C1->SR1 & (SR1_ADDR))) {}

	//	[13] Disable Acknowledgment.
	I2C1->CR1 &= ~CR1_ACK ;

	//	[14] Clear The Address Flag.
	tmp = I2C1->SR2;

	//	[15] Generate Stop.
	I2C1->CR1 |= CR1_STOP ;

	//	[16] Wait Until RXNE Flag is Set.
	while(!(I2C1->SR1 & (SR1_RXNE))) {}

	//	[17] Read Data from Data Register.
	*data++=I2C1->DR;
}
/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
void I2C1_BurstRead(char SlaveAddress,char MemoryAddress,int n,char* data)
{
	volatile int tmp;
	//[1] Wait Until Bus is not Busy.
	while(I2C1->SR2 & (SR2_BUSY)) {}

	//[2] Generate Start Condition.
	I2C1->CR1|=CR1_START;

	//[3] Wait Until The Start Flag is Set.
	while(!(I2C1->SR1 & (SR1_SB))) {}

	//[4] Transmit Slave Address + Write.
	I2C1->DR= SlaveAddress<<1;

	//[5] Wait Until The Address Flag is Set.
	while(!(I2C1->SR1 & (SR1_ADDR))) {}

	//[6] Clear The Address Flag.
	tmp = I2C1->SR2;

	//[7] Wait Until The Transmitter is Empty.
	while(!(I2C1->SR1 & (SR1_TXE))) {}

	//[8] Send Memory Address.
	I2C1->DR= MemoryAddress;

	//[7] Wait Until The Transmitter is Empty.
	while(!(I2C1->SR1 & (SR1_TXE))) {}

	//[2] Generate Start Condition.
	I2C1->CR1|=CR1_START;

	//[3] Wait Until The Start Flag is Set.
	while(!(I2C1->SR1 & (SR1_SB))) {}

	//	[11] Transmit Slave Address + Read (1).
	I2C1->DR= SlaveAddress<<1 |1;

	//[5] Wait Until The Address Flag is Set.
	while(!(I2C1->SR1 & (SR1_ADDR))) {}

	//	[14] Clear The Address Flag.
	tmp = I2C1->SR2;

//	[14] Enable Acknowledgment.
	I2C1->CR1 |= CR1_ACK ;
	while(n> 0U)
	{
		if(n == 1U)
		{

			//Generate Stop.
			I2C1->CR1 |= CR1_STOP ;

			//Wait Until RXNE Flag is Set.
			while(!(I2C1->SR1 & (SR1_RXNE))) {}

			//Read Data from Data Register.
			(*data++)=I2C1->DR;
			break;
		}
		else
		{
			//Wait Until RXNE Flag is Set.
			while(!(I2C1->SR1 & (SR1_RXNE))) {}

			//Read Data from Data Register.
			(*data++)=I2C1->DR;
			n--;
		}
	}
}
/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
void I2C1_BurstWrite(char SlaveAddress,char MemoryAddress,int n,char* data)
{
	volatile int tmp;
	//[1] Wait Until Bus is not Busy.
	while(I2C1->SR2 & (SR2_BUSY)) {}

	//[2] Generate Start Condition.
	I2C1->CR1|=CR1_START;

	//[3] Wait Until The Start Flag is Set.
	while(!(I2C1->SR1 & (SR1_SB))) {}

	//[4] Transmit Slave Address + Write.
	I2C1->DR= SlaveAddress<<1;

	//[5] Wait Until The Address Flag is Set.
	while(!(I2C1->SR1 & (SR1_ADDR))) {}

	//[6] Clear The Address Flag.
	tmp = I2C1->SR2;

	//[7] Wait Until The Transmitter is Empty.
	while(!(I2C1->SR1 & (SR1_TXE))) {}

	//[8] Send Memory Address.
	I2C1->DR= MemoryAddress;

	for(int i=0;i<n;i++)
	{
		//[10] Wait Until The Transmitter is Empty.
		while(!(I2C1->SR1 & (SR1_TXE))) {}
		I2C1->DR= *data++;
	}
	//[11] Generate Stop after Data Received.
	while(!(I2C1->SR1 & (SR1_BTF))) {}
	//Generate Stop.
	I2C1->CR1 |= CR1_STOP ;

}
/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
