#ifndef __CMPDATAPROCESS_H
#define	__CMPDATAPROCESS_H
#include "SysConfig.h"
#include "cmd_process.h"





/* ��������֡֡ͷ֡β����*/
#define NET_CMD_MAXLEN  		1024   				//TCPָ����󳤶�
#define NET_CMD_HEAD 			0x90				//֡ͷ
#define NET_CMD_TAIL 			0xfefcfefc 			//֡β

//7�紮�ڲ�������֡ͷ֡β
#define TFT_CMD_MAXLEN  		500   				//TCPָ����󳤶�
#define TFT_CMD_HEAD 			0xee				//֡ͷ
#define TFT_CMD_TAIL 			0xfffcffff 			//֡β

//��ά���ͷ֡ͷ֡β
#define CODE_CMD_MAXLEN  		200   				//��ά��ָ�����󳤶�
#define CODE_CMD_HEAD 			0x61				//֡ͷ
#define CODE_CMD_TAIL 			0x7778797A 			//֡β






void CodeDatExp(void);
void ScomTftCmdExp(void);
void NetDatExp(void);
void ProcessMessage( PCTRL_MSG msg, uint16_t size );
int CheckStr(uint8_t min,uint8_t max,char c,uint8_t cnt,uint8_t *tmpbuf,char *mstrpc);
void TestSrintInput(uint8_t min,uint8_t max,char c,uint8_t cnt,char *mstrpc);
#endif /* __CMPDATAPROCESS_H */

