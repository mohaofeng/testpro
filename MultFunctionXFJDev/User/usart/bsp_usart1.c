/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����c��printf������usart�˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_usart1.h"

 /**
  * @brief  USART1 GPIO ����,����ģʽ���á�9600 8-N-1
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	
	  // �򿪴���GPIO��ʱ��
	  SERIAL_LCD_USART_GPIO_APBxClkCmd(SERIAL_LCD_USART_GPIO_CLK, ENABLE);
	  
	  // �򿪴��������ʱ��
	  SERIAL_LCD_USART_APBxClkCmd(SERIAL_LCD_USART_CLK, ENABLE);
	
	  // ��USART Tx��GPIO����Ϊ���츴��ģʽ
	  GPIO_InitStructure.GPIO_Pin = SERIAL_LCD_USART_TX_GPIO_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(SERIAL_LCD_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	// ��USART Rx��GPIO����Ϊ��������ģʽ
	  GPIO_InitStructure.GPIO_Pin = SERIAL_LCD_USART_RX_GPIO_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(SERIAL_LCD_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	  
	  // ���ô��ڵĹ�������
	  // ���ò�����
	  USART_InitStructure.USART_BaudRate = SERIAL_LCD_USART_BAUDRATE;
	  // ���� �������ֳ�
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  // ����ֹͣλ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  // ����У��λ
	  USART_InitStructure.USART_Parity = USART_Parity_No ;
	  // ����Ӳ��������
	  USART_InitStructure.USART_HardwareFlowControl = 
	  USART_HardwareFlowControl_None;
	  // ���ù���ģʽ���շ�һ��
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  // ��ɴ��ڵĳ�ʼ������
	  USART_Init(SERIAL_LCD_USARTx, &USART_InitStructure);
	  	  
	  // ʹ�ܴ��ڽ����ж�
	  USART_ITConfig(SERIAL_LCD_USARTx, USART_IT_RXNE, ENABLE);	  
	  
	  // ʹ�ܴ���
	  USART_Cmd(SERIAL_LCD_USARTx, ENABLE);		  
}



void Uart1Sent(uint8_t ch)
{
	while((USART1->SR&0X40)==0)
	{
		;
	}//ѭ������,ֱ���������   
	USART1->DR = (u8)ch;      	
}


void Uart1SentStr(uint8_t *ch)
{
	uint16_t iNum;
	while(ch[iNum] != 0)
	{
		Uart1Sent(ch[iNum]);
	}
}



/*********************************************END OF FILE**********************/
