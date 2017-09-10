/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_led.h"   
#include "SysConfig.h"

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED������ʱ��*/
	RCC_APB2PeriphClockCmd( LED1_GPIO_CLK|LED2_GPIO_CLK|LED3_GPIO_CLK, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOB0*/
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�����*/															   
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;

	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED3_PIN;

	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	
	  

	/* �ر�����led��	*/
	GPIO_SetBits(LED1_GPIO_PORT, LED1_PIN);
	GPIO_SetBits(LED2_GPIO_PORT, LED2_PIN);	
	GPIO_SetBits(LED3_GPIO_PORT, LED3_PIN);	
}
void LED_RGB111(uint8_t rgb111)
{
	assert_param(IS_RGB111_ALL_PERIPH(rgb111));
	if(rgb111&0x1)
		GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN);
	else
		GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);
	if(rgb111&0x2)
		GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN);
	else
		GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);
	if(rgb111&0x4)
		GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN);
	else
		GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);
}




void GateIoInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}
/////////////////////////////////////////////////////////////////////
//?    ?:??????
//????: Dly_Var.gPlusGas????x*10ms ????????Config.CoinSigHod???????
//					
//					SysVar.PlusNum????         
void GateSig(void)
{
	static uint8_t st=0;
	if((g_tFlg.GateSigNum > 0) &&(0 == DlyVar.gGateSigDly))
	{
		switch(st)
		{
				case 0:
					DlyVar.gGateSigDly = Config.PlusWith;
					st = 1;
					COIN_SIG = !COIN_SIG;
					break;
				case 1:
					COIN_SIG = !COIN_SIG;
					DlyVar.gGateSigDly = Config.PlusGas;
					st = 0;
					g_tFlg.GateSigNum--;
					break;
				default:
					break;
		}
	}
}
void CoinSig(void)
{
	static uint8_t st=0;
	if((g_tFlg.CoinSigNum > 0) &&(0 == DlyVar.gCoinSigDly))
	{
		switch(st)
		{
				case 0:
					DlyVar.gCoinSigDly = Config.GateWith;
					st = 1;
					COIN_SIG = !COIN_SIG;
					break;
				case 1:
					COIN_SIG = !COIN_SIG;
					DlyVar.gCoinSigDly = Config.GateGas;
					st = 0;
					g_tFlg.CoinSigNum--;
					break;
				default:
					break;
		}
	}
}

/*********************************************END OF FILE**********************/

