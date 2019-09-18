/*
 * HDC1080.h
 *
 *  Created on: 2019��9��17��
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
#define HDC1080_ADDR		0x80	/* HDC1080 IIC��ַ */

#define IIC_SCL_GPIO        /* sclʱ�����Ŷ˿ڶ��� */
#define IIC_SCL_PIN         /* sclʱ�����Ŷ���  */
#define IIC_SDA_GPIO        /* sda�������Ŷ˿ڶ��� */
#define IIC_SDA_PIN         /* sda�������Ŷ��� */

#define IIC_ResetScl()     /* iic sclʱ�������õ� */
#define IIC_SetScl()       /* iic sclʱ�������ø� */

#define IIC_ResetSda()     /* iic sda�����õ� */
#define IIC_SetSda()       /* iic sda�����ø� */

#define IIC_ReadSda()      1/* iic sda����״̬��ȡ���� */

#define IIC_Sda_In()  		   /* iic sda��������Ϊ����ģʽ */
#define IIC_SdaOut()		   /* iic sda��������Ϊ���ģʽ */
/* GLOBAL FUNCTIONS --------------------------------------------------------- */



#ifdef __cplusplus
}
#endif

#endif /* HDC1080_H_ */