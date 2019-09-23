/*
 * HDC1080.c
 *
 *  Created on: 2019��9��17��
 *      Author: S
 */
#define   HDC1080_GLOBALS
#include "HDC1080.h"

#define  DELAY_TIME  10 /* ��ʱ����ͳһ���� */

/**
 * @brief  HDC1080��us��ʱ����
 * @param[in]  num:��ʱ������
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
 * @brief  IICӲ����ʼ��
 * @param  None
 * @return None
 */
static void IIC1_Init(void)
{
	/* iicӲ����ʼ�� */
}

/**
 * @brief  HDC1080��ʼ��
 * @param  None
 * @return None
 */
uint8_t HDC1080_Init(void)
{
	/* iic��ʼ�� */
	IIC1_Init();
}

/**
 * @brief  IIC START
 * @param  None
 * @return None
 */
static void IIC_Start(void)
{
	/* sda����Ϊ���ģʽ */
	IIC_SdaOut();

	/* iic START��SCL�ߵ������ ��SDA�ɸߵ��� */
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetSda();
	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_SetSda();
	IIC_Delay(DELAY_TIME);

	IIC_ResetScl();	/* Ƕסiicʱ���ߣ�Ϊ�´���׼�� */
	IIC_Delay(DELAY_TIME);
}

/**
 * @brief  IIC STOP
 * @param  None
 * @return None
 */
static void IIC_stop(void)
{
	/* sda����Ϊ���ģʽ */
	IIC_SdaOut();

	/* iic STOP:SCL�ߵ�����£�SDA�еͱ�� */
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
 * @brief  IIC����Ӧ���ź�
 * @param  ack:Ϊ0ʱ������Ӧ���źţ�Ϊ1ʱ����Ӧ���ź�
 * @return None
 */
static void IIC_Ack(uint8_t ack)
{
	IIC_ResetScl();
	IIC_SdaOut();
	IIC_Delay(DELAY_TIME);

	/* �ж�ack�����Ϊ0 sda����ߣ����Ϊ1 sda���Ϊ�� */
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
 * @brief  IIC ��ȡоƬӦ���ź�
 * @param  none
 * @return 0,����Ӧ��ɹ�	1,����Ӧ��ʧ��
 */
static uint8_t IIC_GetAck(void)
{
	/* ��ʱ�����ж��Ƿ�Ӧ�� */
	uint8_t TempBit;

	IIC_SetSda();
	IIC_Delay(DELAY_TIME);
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);

	IIC_Sda_In();
	IIC_Delay(DELAY_TIME);
	TempBit = IIC_ReadSda();
	IIC_Delay(DELAY_TIME);

	/* �ж���������״̬  */
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
 * @brief  IIC��оƬ����һ���ֽ�����
 * @param  none
 * @return 0,����Ӧ��ɹ�	1,����Ӧ��ʧ��
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

	/* ����Ӧ�� */
	return IIC_GetAck();
}

/**
 * @brief  IIC��оƬ����һ���ֽ�����
 * @param  ack:Ϊ0ʱ������Ӧ���źţ�Ϊ1ʱ����Ӧ���ź�
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
 * @brief  ��HDC1080ָ����ַд��һ������
 * @param[in]  WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ
 * @param[in]  DataToWrite:Ҫд�������
 * @return None
 */
void HDC1080_WriteOneByte(uint8_t WriteAddr,uint32_t DataToWrite)
{
  IIC_Start();

  IIC1_Send_Byte(0X80);    //����������ַ0XA0,д����
  IIC1_Wait_Ack();
  IIC1_Send_Byte(WriteAddr);   //���͵͵�ַ
  IIC1_Wait_Ack();

  IIC1_Send_Byte(DataToWrite>>8);     //�����ֽ�
  IIC1_Wait_Ack();
  IIC1_Send_Byte(DataToWrite&0xff);     //�����ֽ�
  IIC1_Wait_Ack();

  IIC1_Stop();//����һ��ֹͣ����

  SYSExitCritical();////_EINT();       //�����ж�
}

/***************************************************************************
*��������T8563_SendData
*��  ����SlvAdr �ӻ���ַ    SubAdr�ӻ��Ĵ�����ַ
*����ֵ����
*��  ������ָ��оƬ��ָ����ַ  ����ByteCnt������
*/

