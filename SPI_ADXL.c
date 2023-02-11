

#include <stdint.h>
#include "stm32f4xx.h"

/*###############################################################*/
/*###############################################################*/
/*###############################################################*/
#define GPIOAEN                          (1U<<0)
#define SPI1EN                           (1U<<12)

#define MULTI_BYTE_EN                    (0x40)
#define READ_OPERATION                   (0x80)

#define SR_TXE                           (1U<<1)
#define SR_RXNE                          (1U<<0)
#define SR_BUSY                          (1U<<7)

#define DEVID_R                          (0x00)
#define DATA_FORMAT_R                    (0x31)
#define DATA_START_ADDDR                 (0x32)
#define POWER_CTRL_R                     (0x2D)
#define DEVICE_ADDR                      (0x53)
#define FOUR_G                           (0x01)
#define RESET                            (0x00)
#define SET_MEASURE_B                    (0x08)
/*###############################################################*/

uint8_t data_rec[6];
uint16_t x,y,z;
float xg,yg,zg;
char data;

/*###############################################################*/

void spi_gpio_init(void);
void spi_config(void);
void cs_enable(void);
void cs_disable(void);
void adxl_init(void);
void adxl_write(uint8_t reg,char value);
void adxl_read(uint8_t address,uint8_t *rxdata);
void spi_transmit(uint8_t *data,uint32_t size);
void spi_receive(uint8_t *data,uint32_t size);

/*###############################################################*/
void adxl_init(void)
{
	spi_gpio_init();
	spi_config();
	adxl_write(DATA_FORMAT_R,FOUR_G);
	adxl_write(POWER_CTRL_R,RESET);
	adxl_write(POWER_CTRL_R,SET_MEASURE_B);
}
void adxl_write(uint8_t reg,char value)
{
	uint8_t data[2];
	data[0]= reg |MULTI_BYTE_EN;
	data[1]= value;
	cs_enable();
	spi_transmit(data,2);
	cs_disable();


}
void adxl_read(uint8_t address,uint8_t *rxdata)
{
	address |= READ_OPERATION ;
	address |= MULTI_BYTE_EN;
	cs_enable();
	spi_transmit(&address,1);
	spi_receive(rxdata,6);
	cs_disable();
}
void cs_enable(void)
{
	GPIOA->ODR &=~(1U<<9);
}

void cs_disable(void)
{
	GPIOA->ODR |=(1U<<9);
}

void spi_config(void)
{
	//set the fpcl4ck 5
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &=~ (1U<<4);
	SPI1->CR1 &=~ (1U<<5);

    //set  CPOL TO 1 SPHA TO 1
	SPI1->CR1 |= (1U<<0);
	SPI1->CR1 |= (1U<<1);

	//configure full duplex
	SPI1->CR1 &=~ (1U<<10);

	//set as master
	SPI1->CR1 |= (1U<<2);

	//set MSB Transmitted first
	SPI1->CR1 &=~ (1U<<7);

	//configure for 8 bit data mode
	SPI1->CR1 &=~ (1U<<11);

	//select software slave
	SPI1->CR1 |= (1U<<8);
	SPI1->CR1 |= (1U<<9);

	//SPI Enable
	SPI1->CR1 |= (1U<<6);
}
void spi_gpio_init(void)
{
	//	[1] Enable the clock access to PORT A.
		RCC->AHB1ENR |=GPIOAEN;
	//	[2] Enable the clock access for SPI1.
		RCC->APB2ENR |=SPI1EN;
	// Set PA5,PA6,PA7 For ALTERNATE FUNCTION
		GPIOA->MODER &=~(1U<<10);
		GPIOA->MODER |=(1U<<11);

		GPIOA->MODER &=~(1U<<12);
		GPIOA->MODER |=(1U<<13);

		GPIOA->MODER &=~(1U<<14);
		GPIOA->MODER |=(1U<<15);
	// Set PA9 For Chip Select GPIO for Output
		GPIOA->MODER |=(1U<<18);
		GPIOA->MODER &=~(1U<<19);
	//Set AFR [Alternative function register]
		GPIOA->AFR[0] |=(1U<<20);
		GPIOA->AFR[0] &=~(1U<<21);
		GPIOA->AFR[0] |=(1U<<22);
		GPIOA->AFR[0] &=~(1U<<23);

		GPIOA->AFR[0] |=(1U<<24);
		GPIOA->AFR[0] &=~(1U<<25);
		GPIOA->AFR[0] |=(1U<<26);
		GPIOA->AFR[0] &=~(1U<<27);

		GPIOA->AFR[0] |=(1U<<28);
		GPIOA->AFR[0] &=~(1U<<29);
		GPIOA->AFR[0] |=(1U<<30);
		GPIOA->AFR[0] &=~(1U<<31);

}

void spi_transmit(uint8_t *data,uint32_t size)
{
	uint32_t i=0;
	uint8_t temp;
	while(i<size)
	{
		while(!(SPI1->SR &(SR_TXE))) {}
		SPI1->DR = data[i];
		i++;
	}
	while(!(SPI1->SR &(SR_TXE))) {}
	while(!(SPI1->SR &(SR_BUSY))) {}
	temp = SPI1->DR;
	temp = SPI1->SR;
}

void spi_receive(uint8_t *data,uint32_t size)
{
	while(size)
	{
		SPI1->DR = 0 ;
		while(!(SPI1->SR &(SR_RXNE))) {}
		*data++=(SPI1->DR);
		size--;
	}
}
/*###############################################################*/
/*###############################################################*/
/*###############################################################*/

int main(void)
{
	adxl_init();


	while(1)
	{
		adxl_read(DATA_START_ADDDR,data_rec);
		x = ( (data_rec[1]<<8) | (data_rec[0]) );
		y = ( (data_rec[3]<<8) | (data_rec[2]) );
		z = ( (data_rec[5]<<8) | (data_rec[4]) );

		xg = (x*0.0078);
		yg = (y*0.0078);
		zg = (z*0.0078);
	}

}
/*###############################################################*/

/*###############################################################*/
