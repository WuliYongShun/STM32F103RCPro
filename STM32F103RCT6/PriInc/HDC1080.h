/*
 * HDC1080.h
 *
 *  Created on: 2019年9月17日
 *      Author: S
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HDC1080_H_
#define HDC1080_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef   HDC1080_GLOBALS
#define  HDC1080_EXT
#else
#define  HDC1080_EXT  extern
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/


/* GLOBAL VARIABLES --------------------------------------------------------- */


/* Private defines -----------------------------------------------------------*/
#define HDC1080_ADDR		0x80	/* HDC1080 IIC地址 */

#define IIC_SCL_GPIO        /* scl时钟引脚端口定义 */
#define IIC_SCL_PIN         /* scl时钟引脚定义  */
#define IIC_SDA_GPIO        /* sda数据引脚端口定义 */
#define IIC_SDA_PIN         /* sda数据引脚定义 */

#define IIC_ResetScl()     /* iic scl时钟引脚置低 */
#define IIC_SetScl()       /* iic scl时钟引脚置高 */

#define IIC_ResetSda()     /* iic sda引脚置低 */
#define IIC_SetSda()       /* iic sda引脚置高 */

#define IIC_ReadSda()      1/* iic sda输入状态读取数据 */

#define IIC_Sda_In()  		   /* iic sda引脚设置为输入模式 */
#define IIC_SdaOut()		   /* iic sda引脚设置为输出模式 */
/* GLOBAL FUNCTIONS --------------------------------------------------------- */



#ifdef __cplusplus
}
#endif

#endif /* HDC1080_H_ */
