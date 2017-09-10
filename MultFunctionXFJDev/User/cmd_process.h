#ifndef _CMD_PROCESS_H
#define _CMD_PROCESS_H
#include "hmi_driver.h"
#include <stdint.h>
//#include "types.h"

#define NOTIFY_TOUCH_PRESS      0X01   //����������֪ͨ
#define NOTIFY_TOUCH_RELEASE  0X03  //�������ɿ�֪ͨ
#define NOTIFY_WRITE_FLASH_OK  0X0C  //дFLASH�ɹ�
#define NOTIFY_WRITE_FLASH_FAILD  0X0D  //дFLASHʧ��
#define NOTIFY_READ_FLASH_OK  0X0B  //��FLASH�ɹ�
#define NOTIFY_READ_FLASH_FAILD  0X0F  //��FLASHʧ��
#define NOTIFY_MENU                        0X14  //�˵��¼�֪ͨ
#define NOTIFY_TIMER                       0X43  //��ʱ����ʱ֪ͨ
#define NOTIFY_CONTROL                0XB1  //�ؼ�����֪ͨ
#define NOTIFY_READ_RTC               0XF7  //��ȡRTCʱ��
#define MSG_GET_CURRENT_SCREEN 0X01//����ID�仯֪ͨ
#define MSG_GET_DATA                            0X11//�ؼ�����֪ͨ

#define PTR2U16(PTR) ((((uint8_t *)(PTR))[0]<<8)|((uint8_t *)(PTR))[1])  //�ӻ�����ȡ16λ����
#define PTR2U32(PTR) ((((uint8_t *)(PTR))[0]<<24)|(((uint8_t *)(PTR))[1]<<16)|(((uint8_t *)(PTR))[2]<<8)|((uint8_t *)(PTR))[3])  //�ӻ�����ȡ32λ����

enum CtrlType
{
	kCtrlUnknown=0x0,
	kCtrlButton=0x10,  //��ť
	kCtrlText,  //�ı�
	kCtrlProgress,  //������
	kCtrlSlider,    //������
	kCtrlMeter,  //�Ǳ�
	kCtrlDropList, //�����б�
	kCtrlAnimation, //����
	kCtrlRTC, //ʱ����ʾ
	kCtrlGraph, //����ͼ�ؼ�
	kCtrlTable, //���ؼ�
	kCtrlMenu,//�˵��ؼ�
	kCtrlSelector,//ѡ��ؼ�
	kCtrlQRCode,//��ά��
};

#pragma pack(push)
#pragma pack(1)	//���ֽڶ���

typedef struct
{
	uint8_t    cmd_head;  //֡ͷ

	uint8_t    cmd_type;  //��������(UPDATE_CONTROL)	
	uint8_t    ctrl_msg;   //CtrlMsgType-ָʾ��Ϣ������
	uint16_t   screen_id;  //������Ϣ�Ļ���ID
	uint16_t   control_id;  //������Ϣ�Ŀؼ�ID
	uint8_t    control_type; //�ؼ�����

	uint8_t    param[256];//�ɱ䳤�Ȳ��������256���ֽ�

	uint8_t  cmd_tail[4];   //֡β
}CTRL_MSG,*PCTRL_MSG;

#pragma pack(pop)

void ProcessMessage( PCTRL_MSG msg, uint16_t size );

void NotifyScreen(uint16_t screen_id);

void NotifyTouchXY(uint8_t press,uint16_t x,uint16_t y);

void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t  state);

void NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str);

void NotifyProgress(uint16_t screen_id, uint16_t control_id, uint32_t value);

void NotifySlider(uint16_t screen_id, uint16_t control_id, uint32_t value);

void NotifyMeter(uint16_t screen_id, uint16_t control_id, uint32_t value);

void NotifyMenu(uint16_t screen_id, uint16_t control_id, uint8_t  item, uint8_t  state);

void NotifySelector(uint16_t screen_id, uint16_t control_id, uint8_t  item);

void NotifyTimer(uint16_t screen_id, uint16_t control_id);

void NotifyReadFlash(uint8_t status,uint8_t *_data,uint16_t length);

void NotifyWriteFlash(uint8_t status);

void NotifyReadRTC(uint8_t year,uint8_t month,uint8_t week,uint8_t day,uint8_t hour,uint8_t minute,uint8_t second);

#endif


