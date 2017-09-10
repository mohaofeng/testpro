#ifndef __FRAME_PKG_H
#define __FRAME_PKG_H	 		  

#ifdef FRAME_PKG_C	
#define FRAME_PKG_EXT 
#else
#define FRAME_PKG_EXT extern
#endif
#include "queue.h"
#include "SysConfig.h"






#define CMD_TAIL_Nbyte 1 					//֡β
#define CMD_POS 1							//������λ��


/*
*
*�๦�����ѻ�ָ���
*/
#define LOGIN_CMD_MULFUN_XFJ   		 0x37					//�����¼ָ��


/***********************************************
������Э�������ֶ���    Xn -> Sn
************************************************/
   
#define XnLOGIN_CMD   		 0x00					//�����¼ָ��
#define XnLINK_CMD    		 0x01					//��·������ָ��
#define XnCHK_MON_CMD    	 0x02					//��������ѯָ��
#define XnDEC_MON_CMD    	 0x03					//����۷�
#define XnDEC_MON_CMD    	 0x03					//����۷�
#define XnEXT_CMD   			 0x04					//�ϴ�ɨ��ͷ��Ϣ
#define XnREQ_TIM_CMD      0x05					//��ȡ������ʱ��
#define XnREPOT_InFOR_CMD  0x06					//�ϴ��豸��Ϣ
#define XnREPOT_TEST_CMD   0x07					//�ظ�����������ָ��
#define XnREPOT_COIN_CMP   0x08					//�ϴ���Ʊ������������
#define XnRequestCMD   		 0x09					//����۷�ָ�������
#define RequestCMD_MULTFUNC   		 0x36					//����۷�ָ�������
/***********************************************
������Э�������ֶ���    Sn -> Xn
************************************************/
#define SnRE_TIM_CMD   		 			0xff		//����������ʱ��
#define SnRE_AMOUNT_CMD    		 	0xfe		//�������
#define SnRE_DEC_MON_CMD    	 	0xfd		//���ؿ۷�
#define SnRE_REFUND_MON_CMD    	0xfc		//�����˿�
#define Sn_REQXnIMFo_CMD   			0xfb		//��ȡ�豸��Ϣ
#define Sn_REQXnSTA_CMD      		0xfa		//��ȡ�豸����״̬
#define Sn_CONFIG_IP_CMD  			0xf9		//�������������ѻ�id��
#define Sn_Login_CMD  					0x33		//�ظ���½�ɹ�
#define Sn_SETDECMON_CMD  			0xf7		//�������������Ѷ��
#define Sn_CONFIG_ID_CMD  			0xf5		//�������������ѻ�id��
#define Sn_LINK_CMD  						0xf4		//�ظ�����ָ��
#define Sn_SET_RUMMOD_CMD  			0xf3		//�������������ѻ�����ģʽ
#define Sn_CONFIG_PLUS_CMD  		0xf2		//����������������
#define Sn_SET_AP_NAME_PASSWORD 0xf1		//�����������ȵ����ƺ�����
#define Sn_SET_RemotIP 					0xf0		//����������Զ��ip��ַ
#define Sn_SET_Netmod 					0xef		//����������������ʽ
#define Sn_PromptTIM 						0xee		//�����ʾͣ��ʱ��
#define Sn_TEST 								0xed		//����������ָ��
#define Sn_OUT_TEST 						0xec		//�����������Ϸ�ָ��
#define Sn_Config_DHCP					0xeb		//����������dhcp����
#define Sn_ACK_COIN							0xea		//�������ظ���Ʊ����
#define Sn_UPDATE_GUI						0x31		//�������ظ�����ѯָ��
//#define Sn_ACK_DEC_OK						0x32		//�������ظ��۷ѳɹ�ָ��
#define Sn_TEST_PRINTER					0x32		//�������ظ��۷ѳɹ�ָ��


void FrameLogin(void);
void FrameLink(void);


void FrameAckConfig(void);
void AckDXImfor(uint8_t dxid,uint8_t wxid,uint8_t *sn);
void FrameUpWxConfig(void);
qsize queue_find_cmdForCmp(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail);
qsize queue_find_cmdForCode(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail);
qsize queue_find_cmdForTFT(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail);
qsize queue_find_cmdForUp(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail);
void FrameDecMon(u32 sn,u32 xf,uint32_t id);
void FrameDecMonEXT(u8 imforlen,u8 *imfor,u32 xf,uint32_t id);
void FrameApply(u32 sn,uint32_t id);
void FrameRequTest(void);
void FrameUpDxCoinSum(uint32_t sn,uint32_t cnt);
void RequestDecMon(uint8_t cmdid,uint8_t *vipstring,uint32_t deccnt);
void CmpTestPrint(char *pname);
void FrameString(char *imfor);

#if TEST_DBG	
void CmpAckCheckBalence(uint16_t x,uint16_t y,uint16_t fsize,uint16_t Fcolor,uint16_t dtim,uint16_t Bcolor,uint8_t soundtype,uint8_t coincnt,char *pname);
//void CmpAckCheckBalence(uint8_t sta,uint32_t jifen,uint32_t caipiao,uint32_t daibi,uint32_t benjin,uint32_t zengjin,uint32_t sn,uint32_t snid,uint8_t *pname);
#endif



#endif






