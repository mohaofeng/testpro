#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H



//#include "types.h"
#include <stdint.h>
#include "./common/common.h" 
#include "utility.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_usart3.h"
#include "bsp_usart4.h"
#include "bsp_usart5.h"
#include "W5500_conf.h"
#include "Serialcd.h"
#include "rc522.h"
#include "WT588D.H"
#include "bsp_led.h"   
#include "stmflash.h"
#include <printer.h>
#include "bsp_usart2.h"
#include "exti.h"
#include "./pvd/bsp_pvd.h" 
#include "./ESP8266/bsp_esp8266.h" 



#define MAX_APNAME_LEN    				64   				/*  wifi������󳤶�  */
#define MAX_APPASSWORD_LEN  			64   				/*  wifi������󳤶�  */
#define FLASH_DAT_LEN 						250  			 	/*  ��������������    */

#define FLASH_STORE_BASE          0            /*  �ⲿ�洢������ַ  */


#define QUBI   1
#define GOUBI  2
#define CHAXUN 3
#define CUNBI  4

#define SUCCEED   1
#define FAILED  	2



#define  DEC_CNT_MAX 	5			//���λֵ
#define  RECONNECT_CNT_MAX 	10			//���λֵ







#define TCP_WAIT_TO_SEND   	0x0001			/* tcp�����ݵȴ����� 				*/
#define TCP_CLOSED			0x0002			/* tcp�����Ѿ��ر�   				*/
#define TCP_INIT			0x0004			/* tcp���ڳ�ʼ��     				*/
#define TCP_CONNECTTING		0x0008    		/* tcp���ڽ�������   				*/
#define TCP_CONNECTED		0x0010			/* tcp�Ѿ�������     				*/
#define TCP_CLOSEING		0x0020			/* tcp�ȴ��ر�       				*/
#define TCP_RECV_DATA		0x0040			/* tcp���յ�����     				*/


#define WiFi_CONNECTED		0x0080			/* wifi�Ѿ���������    				*/









/* �������io�ڶ��� */

#define GATE_CTR_SIG 	PDout(4)		//�̵������
#define COIN_SIG 		PCout(2)		//Ͷ���������







/* ����ģʽ���� */
#define RunMod_KEYINPUT 						0X01   	//������Ŀ���ѻ�ģʽ
#define RunMod_NORMAL_FIX  						0X02	 	//�̶����ɱ���ģʽ
#define RunMod_NORMAL_DANGWEI  					0X03	 	//�̶�����λ�л�ģʽ
#define RunMod_CHECK							0X04   	//��ѯģʽ
#define RunMod_SAVER_COIN      					0X05   	//��һ�ģʽ
#define RunMod_SALE_COIN  						0x06	 	//ȡ�һ�ģʽ
#define RunMod_SALE_SAVER_COIN  				0x07	 	//��ȡ�һ�ģʽ
#define RunMod_GATE_CTRL  						0x08	 	//��բ������ģʽ

/* ָ��Ŷ��� 1=�۷ѣ�2=����3=����ң�4=���Ʊ��5=ȡ���ң�6=������ң�7=ɨ��֧��*/
#define DEC_MON_CMD 												1   		//�۷�
#define CHECK_MON_CMD  											2	 			//�����
#define SAVE_COIN_DAI					  						3	 			//�����
#define SAVE_CAI_PIAO												4   		//���Ʊ
#define GET_COIN_DAI      									5   		//ȡ����
#define BUY_COIN_DAI 												6	 			//�������
#define SCAN_PAY  													7	 			//ɨ��֧��







/* �ߵ͵�ƽ���� */
#define TTL_NC 0 										//Ĭ�϶�ͷid
#define TTL_NO 1 										//Ĭ�϶�ͷid
/* �ߵ͵�ƽ���� */
#define DHCP_OFF 0 										//Ĭ�϶�ͷid
#define DHCP_ON 1 										//Ĭ�϶�ͷid
/* �ߵ͵�ƽ���� */
#define GATE_NC 0 										//Ĭ�϶�ͷid
#define GATE_NO 1 										//Ĭ�϶�ͷid

/* ��ʾ��λ���� */
#define BI 1 										//Ĭ�϶�ͷid
#define YUAN 2 									//Ĭ�϶�ͷid
/* ͨ�ŷ�ʽ�� */
#define NET_RJ45  			1   					//��������
#define NET_WIFI  			2   					//WIFI����
#define NET_GPRS  			4   					//GPRS����
#define NET_2_4G  			8   					//2.4G����

/* �豸���Ͷ��� */
#define XN     		    0X01						//���ѻ�
#define ZN     		    0X02						//����
#define CCGN     			0X03						//�洢��

/* ������� */
#define CHUZHI     		0X01						//��ֵ��
#define SHIJIAN     	0X02						//ʱ�俨
#define JICI     			0X03						//�Ǵο�
#define GUANLI     		0X04						//����
#define FEIFA     		0X05						//���ѳɹ�


#define BIT_SET0  	0X0001
#define BIT_SET1  	0X0002
#define BIT_SET2  	0X0004
#define BIT_SET3  	0X0008
#define BIT_SET4  	0X0010
#define BIT_SET5  	0X0020
#define BIT_SET6  	0X0040
#define BIT_SET7  	0X0080
#define BIT_SET8  	0X0100
#define BIT_SET9 	0X0200
#define BIT_SET10  	0X0400
#define BIT_SET11  	0X0800
#define BIT_SET12 	0X1000
#define BIT_SET13  	0X2000
#define BIT_SET14  	0X4000
#define BIT_SET15  	0X8000



/*------------------���Ժ궨��------------------------*/
#define MAIN_DBG	0
#define TEST_DBG	0
#define NetDatExp_DBG	0
#define TcpClientTaskDBG 0
#define ESP07_DBG  0
#define LCDDisplayTaskDBG 0
#define a6_moduleDBG 0
#define esp8266_moduleDBG 0
#define AT_CMD_DBG 0





/*---------------------------��������----------------------*/



#define LED_GAS_CONST   500//��ͷ״̬��Ϣ�ϴ���� 100x10ms
#define LinkGas_CONST 3000  //�����������
#define CONNECT_Gas_CONST 500  //�����������
#define ToolBarDlyCONST 200  //

#define RC522FLASH_CONST					200       	//rc522ָʾ�Ƶ�������ʱ��
#define ICScanGas_CONST 					100        //ͬһ�û�ˢ������ʱ����
#define KEY_SCAN_CONST 						400        //ͬһ�û�ˢ������ʱ����

#define LINK_MAX_NUM 3				 		//��·����ط�����
#define CONNECT_MAX_NUM 3				 //��·����ط�����
#define QLEN_MAX 2048				 			//���л�������󳤶�






/* ������ʾģʽ���� */


#define SERIAL_LCD          1         			//������������
#define DIS_NULL_MOD 				0x00
#define DIS_IDE_MOD 				0x01
#define DIS_Cmp_MOD 				0x02
#define DIS_LOGIN_MOD 			0x03
#define DIS_INIT_MOD 				0xff


#define CHECK_MON_FLG 				0x0001     //����ѯ�ɹ���־


#define MAX_APNAME_LEN    	64
#define MAX_APPASSWORD_LEN  64








#define SYS_LED PBout(2)// PB5 








/*  ϵͳĬ�����ò��� */
#define DEFAULT_TAG_FLG    		2
#define DEFAULT_ID      	 	1
#define DEFAULT_COIN_TIM    	30
#define DEFAULT_COIN_GAS    	100
#define DEFAULT_GATE_TIM    	1000
#define DEFAULT_GATE_GAS    	1000
#define DEFAULT_DecMon_10   	100
#define DEFAULT_DecMon_20   	200
#define DEFAULT_DecMon_30   	300
#define DEFAULT_DecMon_40   	400
#define DEFAULT_DecMon_50   	500
#define DEFAULT_PromptTim   	1000
#define DEFAULT_KEY      		123456
#define DEFAULT_Hwver      		27
#define DEFAULT_Swver      		27
#define DEFAULT_DecMon_10   	100
#define DEFAULT_DecMon_20   	200
#define DEFAULT_DecMon_30   	300
#define DEFAULT_DecMon_40   	400
#define DEFAULT_DecMon_50   	500
#define DEFAULT_DHCP_STA   		DHCP_ON

//#define IP_FROM_DEFINE	        0       			              /*ʹ�ó�ʼ�����IP��Ϣ*/
//#define IP_FROM_DHCP	        1       			              /*ʹ��DHCP��ȡIP��Ϣ*/

#pragma pack(1)

//ϵͳ������Ϣ
typedef struct
{
	uint8_t  NetMod;													//������ʽ
	uint32_t deviceid;
	uint32_t LoginKey;
	
	uint32_t PlusWith;
	uint32_t PlusGas;												//�Ϸּ��ʱ��
	uint32_t GateWith;
	uint32_t GateGas;
	uint32_t GateSta;
	uint32_t PromptTim;    									//�����ʾͣ��ʱ��
	
	uint8_t  Rmoteip[4];											//������ip
	uint8_t  Localip[4];											//����ip
	uint8_t  GateW[4];												//Ĭ������
	uint8_t  Mass[4];												//��������
	uint16_t RemotePort;													//�˿ں�
	uint16_t tagflg;												//��־
	uint16_t DeviceType;
	uint8_t  hwver;
	uint8_t  swver;
	uint16_t DecMon[5];											//��λ��Ϣ
	uint8_t  ICKey[6];											//��Ƭ��֤����
	uint8_t  runmod;
	uint8_t  ttlLe;													//��̬��ƽ
	uint8_t  dhcpsw;													//dhcp����
	uint8_t  Mac[6];
	uint32_t SysSn[3];
	uint8_t  APName[MAX_APNAME_LEN+2];//ap����
	uint8_t  APPassword[MAX_APPASSWORD_LEN+2];//ap����
	uint8_t  dns[4];
	uint16_t local_port;
}__ConfigVar;
#pragma pack()

extern __ConfigVar Config;								//ϵͳ���ò���



typedef struct
{
	uint8_t 	ucisOk;				//
	uint8_t 	cmdid;				//
	
	
	uint16_t 	wxpos;				//��ʾx����
	uint16_t 	wypos;				//��ʾy����
	uint16_t 	ucFcolor; 		//��ʾǰ��ɫ
	uint16_t	ucBcolor; 		//��ʾ����ɫ
	uint8_t 	ucFontsize;		//��ʾ�����С

	uint16_t 	ucIdeFcolor; 		//��ʾǰ��ɫ
	uint16_t	ucIdeBcolor; 		//��ʾ����ɫ
	uint16_t 	wIdexpos;				//��ʾx����
	uint16_t 	wIdeypos;				//��ʾy����
	uint8_t 	ucIdeFontsize;		//��ʾ�����С
	
	uint32_t 	wCoinCnt;  		//Ͷ�Ҵ���
	uint32_t 	wGateCnt;  		//���Ŵ���
	uint32_t 	wDecNum;  		//��������
	uint16_t 	wSountType;		//�������
	uint8_t 	ScreenWaitTim;//����ָ�ʱ��
	uint8_t 	SerParm;			//Ԥ����
	char name[400];					//��ʾ����
	char IdeShowStr[800];					//��ʾ����
}__VipImfor;
extern __VipImfor VipImfor;


//���������
typedef struct
{
	uint8_t  WiFiRmoteip[4];											//������ip
	uint8_t  WiFiLocalip[4];											//����ip
	uint8_t  WiFiGateW[4];												//Ĭ������
	uint8_t  WiFiMass[4];												//��������
	uint16_t WiFiRemotePort;											//�˿ں�

	uint8_t  LanRmoteip[4];											//������ip
	uint8_t  LanLocalip[4];											//����ip
	uint8_t  LanGateW[4];												//Ĭ������
	uint8_t  LanMass[4];												//��������
	uint16_t LanRemotePort;											//�˿ں�

	uint16_t TxFrameBufLen;						//���ͻ���������
	uint16_t RxFrameBufLen;						//���ջ���������

	uint16_t tcp_sta_old;						//nrf24l01���ͱ�־z
	uint16_t tcp_sta_new;						//nrf24l01���ͱ�־z
	
	
	uint16_t netsta;									//�����ݴ����ͱ�־
	uint8_t NetConnectRetryCnt;					//������������
	uint16_t NetChkGas;								//����״̬�����
	uint16_t ReConnectGas;						//�����������
	uint16_t LinkGas;									//�����������
	uint16_t LinkRetryCnt;						//���������ط�������
	uint8_t  WiFiStpSta;									//���������ط�������
	
	uint8_t csp;
	uint8_t flg;
}__net_ctr;
extern __net_ctr gNetCtr;

//ϵͳ��ʱ��Ϣ
typedef struct{
	uint32_t tst_gas1;			//������
	uint32_t LCDIdeT;				//��������ָ�ʱ��
	uint32_t LCDIdeTUpdatGas;				//��������ˢ�����
	uint32_t gGateSigDly;			//�ϱ�������
	uint32_t gCoinSigDly;			//�ϱ�������
	uint32_t gKeyScanGas;			//����ɨ����
	uint32_t SysStartDly;
//	uint16_t ToolBarDly;    //���������¼��ʱ��
	uint32_t tst_gas;
	uint32_t gLED_Gas;
	uint32_t wifi_mod_key_Dly;
	uint32_t lan_mod_key_Dly;
	uint32_t LcdDisTaskDly;
	uint32_t PlusCntOverTim;
	uint32_t PlusCntLT;
	uint32_t PlusCntHT;
	uint32_t PlusCntDly;
	uint32_t UpdateCoinCntDly;
	uint32_t NetScanGas;
	
}__SysDlyT;
extern __SysDlyT DlyVar;

//ϵͳ��־
typedef struct{
	char *pc[10];
	char srttmp[1024];
}__TmpVar;
extern __TmpVar TmpVar;	 




//ϵͳȫ�ֱ���
volatile typedef struct
{
	uint8_t PlusNum; 		//��������
	uint8_t DisType; 	//��ʾģʽ
	uint8_t UpDatCnt; 	//�ϴ��������
	uint32_t PlusCntSum;//���������ʱ��
	uint32_t WaitUpPlusCntSum;//���������ʱ��
	uint32_t icsn;
	uint32_t icsn_old;
	uint32_t icsn_new;
	uint8_t CntFlg;
	uint8_t CmdID;
	uint16_t ALLFlg;
	uint16_t connect_sta;	
	uint32_t GetVipIdFlg;
	uint8_t ucTcpClosedFlag;
}__Sys_Var;
extern __Sys_Var SysVar;


//��Ա��Ϣ����
typedef struct
{
	uint8_t *name;		//����
	uint8_t *call;		//�绰
	uint32_t kajin;		//����
	uint32_t zengjin;	//�������
	uint32_t jifen;		//�������
	uint32_t daibi;		//�������
	uint32_t caipiao;	//��Ʊ���
	uint32_t cardsn;	//�����
	uint32_t cardid;	//�����
	
}__VIPImfor;
extern __VIPImfor VIPImfor;

//ϵͳ��־
typedef struct{
	uint16_t KeyVal;				//�ϱ���������
	uint16_t PlusSt;				//�ϱ���������
	uint16_t KeySta;				//�ϱ���������
	uint32_t gDecMon;				//��ǰ���ѽ��
	uint16_t gDecMonCnt;				//��ǰ��λ״̬
	uint32_t GateSigNum;
	uint32_t CoinSigNum;				//�ϱ���������
	uint8_t  dhcp_ok;
	uint32_t ChipUniqueID[3];
	uint8_t VipIDString[400];					//��ʾ����
	uint8_t pString[200];
}__SysFlg;
extern __SysFlg g_tFlg;	


void SysParmSet(void);
void SysParmWrite(void);
void SysParmExplain(void);
void SysParmRestorDefault(void);
void SysParmPrint(void);
void SysInit(void);
void SysReset(void);
void NetInit(void);

void showdbg32hex(u32 *bf,u8 len);
void showdbg32dec(u32 *bf,u8 len);
void showdbg8hex(u8 *bf,u8 len);
void showdbg16hex(u16 *bf,u8 len);
void showdbg8dec(u8 *bf,u8 len);


#endif




