/**
  ******************************************************************************
  * @file    bsp_usart5.c
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
  
#include "bsp_usart5.h"

 /********************************************************************************
	* @file    bsp_usart.c
	* @author  fire
	* @version V1.0
	* @date    2013-xx-xx
	* @brief   �ض���c��printf������usart�˿�
	******************************************************************************	  
  * @brief  USART GPIO ����,������������
	* @param  ��
	* @retval ��
	*/
  void USART5_Config(void)
  {
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
  
	  // �򿪴���GPIO��ʱ��
	  PRINTER_USART_GPIO_APBxClkCmd(PRINTER_USART_GPIO_CLK, ENABLE);
	  
	  // �򿪴��������ʱ��
	  PRINTER_USART_APBxClkCmd(PRINTER_USART_CLK, ENABLE);
  
	  // ��USART Tx��GPIO����Ϊ���츴��ģʽ
	  GPIO_InitStructure.GPIO_Pin = PRINTER_USART_TX_GPIO_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(PRINTER_USART_TX_GPIO_PORT, &GPIO_InitStructure);
  
	// ��USART Rx��GPIO����Ϊ��������ģʽ
	  GPIO_InitStructure.GPIO_Pin = PRINTER_USART_RX_GPIO_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(PRINTER_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	  
	  // ���ô��ڵĹ�������
	  // ���ò�����
	  USART_InitStructure.USART_BaudRate = PRINTER_USART_BAUDRATE;
	  // ���� �������ֳ�
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  // ����ֹͣλ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  // ����У��λ
	  USART_InitStructure.USART_Parity = USART_Parity_No ;
	  // ����Ӳ��������
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  // ���ù���ģʽ���շ�һ��
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  // ��ɴ��ڵĳ�ʼ������
	  USART_Init(PRINTER_USARTx, &USART_InitStructure);
	  	  
	  // ʹ�ܴ��ڽ����ж�
	  USART_ITConfig(PRINTER_USARTx, USART_IT_RXNE, ENABLE);	  
	  
	  // ʹ�ܴ���
	  USART_Cmd(PRINTER_USARTx, ENABLE);		  
  
	// ���������ɱ�־
	  //USART_ClearFlag(USART1, USART_FLAG_TC); 	
  }
        
void USART5_Sent(uint8_t c)
{
	while((UART5->SR&0X40)==0)
	{
		;
	}//ѭ������,ֱ���������   
	UART5->DR = c;      	
}
void UART5SentStr(uint8_t *ptc)
{
	uint16_t iNum=0;
	uint8_t *pc;
	pc = ptc;
	while(pc[iNum] != 0)
	{
		USART5_Sent(pc[iNum]);
		iNum++;
	}
}





/*********************************************END OF FILE**********************/
