#define WT588D_C



#include "WT588D.H"
//#include "usart.h"	 
//#include "KeyInput.H"


__SoundCtr SoundCtr;

#define CLK_DLY_CONST 300



void Wt588dInit(void){
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);						 //PB.5 �����
}
void Line_3A(uint8_t addr)
{
	uint8_t i = 0x00;
	uint8_t addrTmp;
	SoundCtr.Sta = 1;
	addrTmp = addr;
	WT588D_CLK_H();					
	WT588D_CS_L();
	delay_ms(10);
	for(i=0;i<8;i++)
	{
		if(addrTmp&0x01)
		{
			WT588D_DAT_H();
		}
		else
		{
			WT588D_DAT_L();
		}			
		delay_us(CLK_DLY_CONST);
		WT588D_CLK_L();	
		delay_us(CLK_DLY_CONST);
		WT588D_CLK_H();					
		delay_us(CLK_DLY_CONST);
		addrTmp >>= 1;	
	}	
	WT588D_CS_H();
	WT588D_DAT_H();
	SoundCtr.Sta = 0;
}






#define  SoundTaskDBG 0
void SoundTask(void)
{
	switch(SoundCtr.Type)
	{
			case SOUND_0:
				Line_3A(WT588D_0);
				break;
			case SOUND_1:
				Line_3A(WT588D_1);
				break;
			case SOUND_2:
				Line_3A(WT588D_2);
				break;
			case SOUND_3:
				Line_3A(WT588D_3);
				break;
			case SOUND_4:
				Line_3A(WT588D_4);
				break;
			case SOUND_5:
				Line_3A(WT588D_5);
				break;
			case SOUND_6:
				Line_3A(WT588D_6);
				break;
			case SOUND_7:
				Line_3A(WT588D_7);
				break;
			case SOUND_8:
				Line_3A(WT588D_8);
				break;
			case SOUND_9:
				Line_3A(WT588D_9);
				break;
			case SOUND_SHI:
				Line_3A(WT588D_SHI);
				break;
			case SOUND_BAI:
				Line_3A(WT588D_BAI);
				break;
			case SOUND_QIAN:
				Line_3A(WT588D_QIAN);
				break;
			case SOUND_WAN:
				Line_3A(WT588D_WAN);
				break;
			
			case SOUND_DIAN:
				Line_3A(WT588D_DIAN);
				break;
			case SOUND_F1:
				Line_3A(WT588D_f1);
				break;
			case SOUND_F2:
				Line_3A(WT588D_f2);
				break;
			case SOUND_F3:
				Line_3A(WT588D_f3);
				break;
			case SOUND_F4:
				Line_3A(WT588D_f4);
				break;
			case SOUND_QUEREN:
				Line_3A(WT588D_queren);
				break;
			/* ȡ�� */
			case SOUND_QUXIAO:
				Line_3A(WT588D_quxiao);
				break;
			/* ��ѯ��� */
			case SOUND_CHAXUN:
				Line_3A(WT588D_yu_e_ck);
				break;
			/* ��Ƭ���� */
			case SOUND_ERR_OVER:
				Line_3A(WT588D_OverTimIC);
				break;
			/* ��Ƭ��ʧ */
			case SOUND_ERR_LOSS:
				Line_3A(WT588D_LOST_IC);
				break;
				/* ��¼�ɹ� */
			case SOUND_LOGINOK_MOD:	
				Line_3A(WT588D_LOGO_IN);
				break;
				/* ���� */
			case SOUND_ERR_MOD:				;
				break;
				/* ��ѯģʽ */
			case SOUND_CHECK_MOD:			
				break;
				/* ���� */
			case SOUND_GUANLI_CARD:
				Line_3A(WT588D_adminic);
				break;
				/* ʱ�俨 */
			case SOUND_SHIJIAN:
				Line_3A(WT588D_DateCard);				
				break;
				/* ��ֵ�� */
			case SOUND_CHUZHI_CARD:
				Line_3A(WT588D_CHUZHI_IC);
				break;
				/* �ƴο� */
			case SOUND_JICI:
				Line_3A(WT588D_CountIc);								
				break;
				/*  �Ƿ� */
			case SOUND_FEIFA:
				Line_3A(WT588D_FEIFA);
			break;
				/* �޸����Ѷ�� */
			case SOUND_CHANGE_XF:
				Line_3A(WT588D_xiaofeiedu);
				break;
				/* ���� */
			case SOUND_NOMON_MOD:
				Line_3A(WT588D_NO_MONEY);
				break;
				/* ������֤ʧ�� */
			case SOUND_IC_CARD_KEY_ERR:
				Line_3A(WT588D_IC_KEY_ERR);
				break;
				/* ��Ʊ��ѯ */
			case SOUND_YU_E_CHECK:
				Line_3A(WT588D_YU_E_CHECK);
				break;
				/* ��Ʊʧ�� */
			case SOUND_SAVED_FAILED:
				Line_3A(WT588D_SAVED_FAILED);
				break;
				/* ��Ʊ�ɹ� */
			case SOUND_SAVED_OK:
				Line_3A(WT588D_SAVED_OK);
				break;
//			case SOUND_IDE_MOD:
				//Line_3A(WT588D_SAVED_OK);
//				break;
			
		//	case SOUND_IDE_MOD:
		//		break;
			
			default:
				break;
		}		
		SoundCtr.Type = SOUND_NULL_MOD;
}
