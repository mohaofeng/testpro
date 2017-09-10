#include "exti.h"
//#include "delay.h"
//#include "usart.h"
#include "SysConfig.h"



#define PLUS_WITH_DLY_T  							(4)				//�ߵ�ƽ
#define PLUS_WITH_H_T  								(4)				//�ߵ�ƽ
#define PLUS_WITH_L_T  								(4)				//�ߵ�ƽ����ʱ��
#define PLUS_WITH_OVER_T  						(2000)				//���������ʱʱ��

//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
 		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_SetBits(GPIOC, GPIO_Pin_1);		
			
  //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;	//ssr1
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn ;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
		
}

//ssr1�����ж�
void EXTI9_5_IRQHandler(void)         		 //����Ϊ��EXTI15_10 (�ⲿ�жϺŵ�10~15��������ʵ�֣�   
{   
	if(EXTI_GetITStatus(EXTI_Line8) != RESET) 
	{  			
		if(DlyVar.PlusCntDly == 0)
		{
			DlyVar.PlusCntDly = PLUS_WITH_DLY_T;
			DlyVar.PlusCntOverTim = PLUS_WITH_OVER_T;
			SysVar.PlusCntSum ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line8);		 	//���ж�	
	} 
}  


