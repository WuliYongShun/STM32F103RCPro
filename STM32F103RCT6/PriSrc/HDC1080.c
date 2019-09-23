/*
 * HDC1080.c
 *
 *  Created on: 2019年9月17日
 *      Author: S
 */
#define   HDC1080_GLOBALS
#include "HDC1080.h"

#define  DELAY_TIME  10 /* 延时周期统一控制 */

/**
 * @brief  HDC1080简单us延时函数
 * @param[in]  num:延时周期数
 * @return None
 */
static void IIC_Delay(uint16_t time)
{
	uint16_t i = 0;

	while(time--)
	{
		i = 10;
		while(i--);
	}
}

/**
 * @brief  IIC硬件初始化
 * @param  None
 * @return None
 */
static void IIC1_Init(void)
{
	/* iic硬件初始化 */
}

/**
 * @brief  HDC1080初始化
 * @param  None
 * @return None
 */
uint8_t HDC1080_Init(void)
{
	/* iic初始化 */
	IIC1_Init();
}

/**
 * @brief  IIC START
 * @param  None
 * @return None
 */
static void IIC_Start(void)
{
	/* sda设置为输出模式 */
	IIC_SdaOut();

	/* iic START：SCL高的情况下 ，SDA由高到低 */
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetSda();
	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_SetSda();
	IIC_Delay(DELAY_TIME);

	IIC_ResetScl();	/* 嵌住iic时钟线，为下次做准备 */
	IIC_Delay(DELAY_TIME);
}

/**
 * @brief  IIC STOP
 * @param  None
 * @return None
 */
static void IIC_stop(void)
{
	/* sda设置为输出模式 */
	IIC_SdaOut();

	/* iic STOP:SCL高的情况下，SDA有低变高 */
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetSda();
	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_SetSda();
	IIC_Delay(DELAY_TIME);

	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
}

/**
 * @brief  IIC产生应答信号
 * @param  ack:为0时产生非应答信号，为1时产生应答信号
 * @return None
 */
static void IIC_Ack(uint8_t ack)
{
	IIC_ResetScl();
	IIC_SdaOut();
	IIC_Delay(DELAY_TIME);

	/* 判断ack：如果为0 sda输出高，如果为1 sda输出为低 */
	if(ack)
	{
		IIC_ResetSda();
	}
	else
	{
		IIC_SetSda();
	}

	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetScl();
}

/**
 * @brief  IIC 获取芯片应答信号
 * @param  none
 * @return 0,接收应答成功	1,接收应答失败
 */
static uint8_t IIC_GetAck(void)
{
	/* 临时变量判断是否应答 */
	uint8_t TempBit;

	IIC_SetSda();
	IIC_Delay(DELAY_TIME);
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);

	IIC_Sda_In();
	IIC_Delay(DELAY_TIME);
	TempBit = IIC_ReadSda();
	IIC_Delay(DELAY_TIME);

	/* 判断引脚输入状态  */
	if(TempBit)
	{
		TempBit = 1;	//no Ack
	}
	else
	{
		TempBit = 0;	//Ack
	}

	IIC_SdaOut();

	return TempBit;
}

/**
 * @brief  IIC向芯片发送一个字节数据
 * @param  none
 * @return 0,接收应答成功	1,接收应答失败
 */
uint8_t IIC_SendByte(uint8_t Data)
{
	uint8_t i;
	IIC_SdaOut();
	for(i = 0; i < 8; i++)
	{
		IIC_ResetScl();
		IIC_Delay(DELAY_TIME);

		if(Data & 0x80)
		{
			IIC_SetSda();
		}
		else
		{
			IIC_ResetSda();
		}
		Data << 1;

		IIC_Delay(DELAY_TIME);
		IIC_SetScl();
		IIC_Delay(DELAY_TIME);
		IIC_Delay(DELAY_TIME);
	}
	IIC_ResetScl();

	/* 返回应答 */
	return IIC_GetAck();
}

/**
 * @brief  IIC从芯片接收一个字节数据
 * @param  ack:为0时产生非应答信号，为1时产生应答信号
 * @return none
 */
uint8_t IIC_RecByte(uint8_t ack)
{
	uint8_t i;
	uint8_t receive = 0x00;
	uint8_t tempsda = 0;

	IIC_SetSda();
	IIC_Delay(DELAY_TIME);
	IIC_Sda_In();
	for(i =0; i < 8; i++)
	{
		receive <<= 1;
		IIC_ResetScl();
		IIC_Delay(DELAY_TIME);

		tempsda = IIC_ReadSda();
		if(tempsda )
		{
			receive |= 0x01;
		}
		IIC_Delay(DELAY_TIME);

		IIC_SetScl();
		IIC_Delay(DELAY_TIME);
	}
	IIC_ResetScl();
	IIC_SdaOut();

	IIC_Ack(ack);
	return receive;
}

/**
 * @brief  在HDC1080指定地址写入一个数据
 * @param[in]  WriteAddr  :写入数据的目的地址
 * @param[in]  DataToWrite:要写入的数据
 * @return None
 */
void HDC1080_WriteOneByte(uint8_t WriteAddr,uint32_t DataToWrite)
{
  IIC_Start();

  IIC1_Send_Byte(0X80);    //发送器件地址0XA0,写数据
  IIC1_Wait_Ack();
  IIC1_Send_Byte(WriteAddr);   //发送低地址
  IIC1_Wait_Ack();

  IIC1_Send_Byte(DataToWrite>>8);     //发送字节
  IIC1_Wait_Ack();
  IIC1_Send_Byte(DataToWrite&0xff);     //发送字节
  IIC1_Wait_Ack();

  IIC1_Stop();//产生一个停止条件

  SYSExitCritical();////_EINT();       //开总中断
}

/***************************************************************************
*函数名：T8563_SendData
*参  数：SlvAdr 从机地址    SubAdr从机寄存器地址
*返回值：无
*描  述：向指定芯片的指定地址  发送ByteCnt个数据
*/

