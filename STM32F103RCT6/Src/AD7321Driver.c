/*
 * AD7321Driver.c
 *
 *  Created on: 2019��9��5��
 *      Author: YSHUN
 */

/*******P4.0->CS��P4.1->SCLK��P4.2->DIN��P4.3->DOUT*****/
//#define set_spi_cs()		HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET)
//#define clr_spi_cs()		HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET)
//#define set_spi_clk()       HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET)
//#define clr_spi_clk()       HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET)
//#define set_spi_dout() 		HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET)
//#define clr_spi_dout() 		HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET)
//#define read_spi_di()		HAL_GPIO_ReadPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin)
//#define read_spi_di_HIGH		0x00000004
//
//#define set_spi_mosi()		set_spi_dout()
//#define clr_spi_mosi()		clr_spi_dout()
//#define read_spi_miso()		read_spi_di()
//#define read_spi_miso_HIGH	read_spi_di_HIGH
/*
*/


//static void delay(unsigned int second)
//{
//	HAL_Delay(second);
//}
//
//unsigned int AD7321_read_write(unsigned int spi_mosiValue)
//{
//	unsigned int   no,
//	spi_misoValue;
//
//	set_spi_cs();
//
//	clr_spi_cs();
//
//	for(no=0;no<16;no++)
//	{
//   		set_spi_clk();
//
//  		spi_misoValue = (spi_misoValue << 1);
//
//   		if((spi_mosiValue & 0x8000)==0x8000)
//     		set_spi_mosi();
//   		else
//     		clr_spi_mosi();
//
//		if(read_spi_miso() == read_spi_miso_HIGH)
//         	spi_misoValue |= 0x0001;
//     	else
//         	spi_misoValue &= ~0x0001;
//   		clr_spi_clk();
//
//   		spi_mosiValue = (spi_mosiValue << 1);
//		delay(1);
//
//	}
//
//	set_spi_clk();
//
//	set_spi_cs();
//
//	return  (spi_misoValue & 0x0000FFFF);
//
//}

