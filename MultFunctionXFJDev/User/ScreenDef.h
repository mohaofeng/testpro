#ifndef ScreenDef_H
#define ScreenDef_H


// typedef unsigned          char uint8_t;
// typedef unsigned          char uchar;
// typedef unsigned short     int uint16_t;
// typedef unsigned           int uint32_t;
// typedef unsigned       __int64 uint64;
#include <stdint.h>

/*   ��ʾϵͳ��������   */
#define SHOW_SYSPARM_SCREEN_ID    											0 	 
#define SHOW_SYSPARM_SCREEN_REMOTE_IP_TEXT_ID 					18  		//������ip�ı���
#define SHOW_SYSPARM_SCREEN_SUB_NET_TEXT_ID 						1  			//���������ı���
#define SHOW_SYSPARM_SCREEN_GATE_WAY_TEXT_ID 						2  			//Ĭ�������ı���
#define SHOW_SYSPARM_SCREEN_LOCAL_IP_TEXT_ID 						19  		//����ip�ı���
#define SHOW_SYSPARM_SCREEN_MAC_ADDR_TEXT_ID 						20  		//����mac�ı���
#define SHOW_SYSPARM_SCREEN_WIFI_NAME_TEXT_ID 					21  		//WIFI�����ı���
#define SHOW_SYSPARM_SCREEN_WIFI_PWD_TEXT_ID 						22  		//WIFI�����ı���
#define SHOW_SYSPARM_SCREEN_REMOTE_PORT_TEXT_ID 				23  		//�������˿ں��ı���

#define SHOW_SYSPARM_SCREEN_GATE_TIM_TEXT_ID 						27  		//����ʱ��
#define SHOW_SYSPARM_SCREEN_PULS_TIM_TEXT_ID 						28  		//�ϱ�ʱ��
#define SHOW_SYSPARM_SCREEN_GATE_GAS_TEXT_ID 						29  		//���ż��
#define SHOW_SYSPARM_SCREEN_PULS_GAS_TEXT_ID 						30  		//�ϱҼ��

#define SHOW_SYSPARM_SCREEN_GATE_STA_BUTTON_ID 					25  		//�����ź�nc/no����
#define SHOW_SYSPARM_SCREEN_COIN_STA_BUTTON_ID 					26  		//Ͷ�ҿ��ź�nc/no����
#define SHOW_SYSPARM_SCREEN_DHCP_SW_BUTTON_ID 					41  		//DHCP����
#define SHOW_SYSPARM_SCREEN_NET_MOD_BUTTON_ID 					24  		//������ʽ����
#define SHOW_SYSPARM_SCREEN_RUN_MOD_BUTTON_ID 					32  		//����ģʽ����
#define SHOW_SYSPARM_SCREEN_QUIT_BUTTON_ID 							34  		//�˳�����
#define SHOW_SYSPARM_SCREEN_SET_BUTTON_ID 							44  		//���ÿ���

/*   ����ϵͳ�����������    */
#define SET_SYSPARM_FOR_NET_SCREEN_ID    									1 	

/*   �̶�������ѻ�����*/
#define FIXED_MON_SCREEN_ID    														2  		

/*   �ɱ䵵λ���ѻ����� */
#define STALL_MON_SCREEN_ID    														3  		
#define BT_STALL_MON_SCREEN_ID 														2  		//��λ�л���ť

/*  �����������ѻ����� */
#define KEY_INPUT_MON_SCREEN_ID    												4  	
#define KEY_INPUT_MON_SCREEN_TEXT_ID     									1    //�ı������ID  	





/*  ��Աȡ�ҽ���  */
#define VIP_QUBI_SCREEN_ID    						5 

/*  ��Ա��ҽ���  */
#define VIP_CUN_SCREEN_ID    						6  

/*  ϵͳ������Ϣ����  */
#define SERVER_ACK_IMFOR_SCREEN_ID    				7 

/*  ��Ա���ҽ���  */
#define VIP_GOUBI_SCREEN_ID    						8 

/*  ��Ա��ȡһ�������  */
#define VIP_SAVE_SALE_SCREEN_ID    						9



/* VIP�̶�����ģʽ��������  */
#define IDE_FIXED_MON_SCREEN_ID						10

/* ���л���λ��������  */
#define IDE_STALL_MON_SCREEN_ID						11

/* VIP����ģʽ��������  */
#define IDE_KEY_INPUT_MON_SCREEN_ID					12


/* VIPȡ�һ���������  */
#define IDE_VIP_QUBI_SCREEN_ID						13

/* VIP��һ���������  */
#define IDE_VIP_CUN_SCREEN_ID						14

/*  ��Ա���Ҵ������� */
#define IDE_GOUBI_SCREEN_ID    						15 

/* VIP��ȡһ�����������  */
#define IDE_SAVE_SALE_SCREEN_ID						16

/* VIP��բ��������������  */
#define IDE_GATE_CTRL_SCREEN_ID						17

/* VIP��ѯ����������  */
#define IDE_CHECK_SCREEN_ID							18

/* ��բ���ƽ��� */
#define GATE_CTRL_SCREEN_ID    						19 

/* ��ѯ��������  */
#define CHECK_SCREEN_ID    							20 

/* VIPδ�����������  */
#define LOGIN_SCREEN_ID						21


/* VIPδ�����������  */
#define IDE_RESERVER_SCREEN_ID						22



/* Ԥ������  */
#define RESERVER_SCREEN_ID    						50 




#define CMD_MAX_SIZE 100        /*!<����ָ���С��������Ҫ�������������ô�һЩ*/
//#define QUEUE_MAX_SIZE 1000   /*!< ָ����ջ�������С��������Ҫ�������������ô�һЩ*/


#define TIME_100MS 10  //100����(10����λ)


//void UpdateUI(void);



#endif



