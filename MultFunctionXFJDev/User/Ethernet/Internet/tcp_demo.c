/**
************************************************************************************************
* @file   		tcp_demo.c
* @author  		WIZnet Software Team 
* @version 		V1.0
* @date    		2015-02-14
* @brief   		TCP ��ʾ����
* @attention  
************************************************************************************************
**/

#include <stdio.h>
#include <string.h>
#include "tcp_demo.h"
#include "W5500_conf.h"
#include "w5500.h"
#include "socket.h"
#include "SysConfig.h"
#include "SysConfig.h"
#include "queue.h"
#include <CmpDatprocess.h>
#include "FramePkg.h"




extern uint8_t gNetUpCmpCmdBuf[NET_CMD_MAXLEN];							//�����ݴ���λ������Ļ�����

static uint8 buff[2048];



#define TCP_WAIT_TO_SEND   	0x0001	/* tcp�����ݵȴ����� 				*/
#define TCP_CLOSED			0x0002			/* tcp�����Ѿ��ر�   				*/
#define TCP_INIT			0x0004				/* tcp���ڳ�ʼ��     				*/
#define TCP_CONNECTTING		0x0008    /* tcp���ڽ�������   				*/
#define TCP_CONNECTED		0x0010			/* tcp�Ѿ�������     				*/
#define TCP_CLOSEING		0x0020			/* tcp�ȴ��ر�       				*/
#define TCP_RECV_DATA		0x0040			/* tcp���յ�����     				*/



void ExpNetSta(void)
{
	
	gNetCtr.tcp_sta_old = gNetCtr.tcp_sta_new;
	gNetCtr.tcp_sta_new = gNetCtr.netsta;
	
	if(gNetCtr.tcp_sta_old != gNetCtr.tcp_sta_new)
	{
		if(TCP_WAIT_TO_SEND & gNetCtr.tcp_sta_new)
			printf("�����ݴ�����\r\n");
		if(TCP_CLOSED & gNetCtr.tcp_sta_new)
			printf("tcp���ӹر�\r\n");
		if(TCP_INIT & gNetCtr.tcp_sta_new)
			printf("tcp��ʼ��\r\n");
		if(TCP_CONNECTTING & gNetCtr.tcp_sta_new)
			printf("tcp��������\r\n");
		if(TCP_CONNECTED & gNetCtr.tcp_sta_new)
			printf("tcp�Ѿ�����\r\n");
		if(TCP_CLOSEING & gNetCtr.tcp_sta_new)
			printf("tcp�ȴ��ر�\r\n");
		if(TCP_RECV_DATA & gNetCtr.tcp_sta_new)
			printf("tcp���յ�����\r\n");
	}
}
/**
*@brief		TCP Client�ػ���ʾ������
*@param		��
*@return	��
*/
void do_tcp_client(void)
{	
   uint16 len=0;	
   uint8_t mod=1;

	switch(getSn_SR(SOCK_TCPC))								  				         /*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:											        		         /*socket���ڹر�״̬*/
			socket(SOCK_TCPC,Sn_MR_TCP,Config.local_port++,Sn_MR_ND);
			gNetCtr.netsta |= TCP_CLOSED;
			gNetCtr.netsta &= (~TCP_INIT);
			gNetCtr.netsta &= (~TCP_CONNECTED);
		  break;
		
		case SOCK_INIT:													        	         /*socket���ڳ�ʼ��״̬*/
			connect(SOCK_TCPC,Config.Rmoteip,Config.RemotePort);                /*socket���ӷ�����*/ 
			gNetCtr.netsta |= TCP_INIT;
			gNetCtr.netsta &= (~TCP_CLOSED);
			gNetCtr.netsta &= (~TCP_CLOSEING);
			gNetCtr.netsta &= (~TCP_CONNECTED);

			
			if(gNetCtr.ReConnectGas==0)
			{
				lcd_parm.distype = DIS_INIT_MOD;
				gNetCtr.ReConnectGas = CONNECT_Gas_CONST;						
				if(gNetCtr.NetConnectRetryCnt == 0)
				{
					SetFcolor(0xffff);
					SetBcolor(0x00ff);
					LCDShowSysParm();					
				//tcp_client_reconnect();
				}
				else if(gNetCtr.NetConnectRetryCnt < RECONNECT_CNT_MAX)
				{
					
					SetScreen(SHOW_SYSPARM_SCREEN_ID);
					switch(SysVar.connect_sta)
					{
						case 0:
							DisText(300, 450,mod,SYS_TMP_FONT,"������������.				          ");
							SysVar.connect_sta = 1;
						break;
						case 1:
							SysVar.connect_sta = 2;
							DisText(300, 450,mod,SYS_TMP_FONT,"������������..				        ");
						break;
						case 2:
							SysVar.connect_sta = 0;
						DisText(300, 450,mod,SYS_TMP_FONT,"������������...				          ");
						break;
					}
				}
				else
				{
						DisText(300, 450,mod,SYS_TMP_FONT,"�޷����ӵ�����������������");							
				}
				if(gNetCtr.NetConnectRetryCnt++>RECONNECT_CNT_MAX*2)
				{
					gNetCtr.NetConnectRetryCnt = 0;
				}
			}
		  break;
		
		case SOCK_ESTABLISHED: 												             /*socket�������ӽ���״̬*/
			gNetCtr.netsta |= TCP_CONNECTED;
			gNetCtr.netsta &= (~TCP_INIT);
			gNetCtr.netsta &= (~TCP_CLOSED);
			gNetCtr.netsta &= (~TCP_CLOSEING);
		
			if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC, Sn_IR_CON);								          /*��������жϱ�־λ*/
			}
			len=getSn_RX_RSR(SOCK_TCPC);									            /*����lenΪ�ѽ������ݵĳ���*/
			if(len>0)
			{
				recv(SOCK_TCPC,buff,len);								              	/*��������Client������*/
				EnQueuex(&gNetDwDxQueu,buff,len);   										//���յ���������ӣ���ת������ͷ
				gNetCtr.netsta |= TCP_RECV_DATA;		  	
			}
			if(gNetCtr.netsta & TCP_WAIT_TO_SEND)
			{
				gNetCtr.netsta &= (~TCP_WAIT_TO_SEND); 
			  send(SOCK_TCPC,gNetUpCmpCmdBuf,gNetCtr.RxFrameBufLen);											/*��Client��������*/
			}
		  break;
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket���ڵȴ��ر�״̬*/
			close(SOCK_TCPC);
			gNetCtr.netsta |= TCP_CLOSEING;
			gNetCtr.netsta &= (~TCP_INIT);
			gNetCtr.netsta &= (~TCP_CLOSED);
			gNetCtr.netsta &= (~TCP_CONNECTED);
			break;
	}
 // ExpNetSta();	
}


void NetPrintf(uint8_t *fmt, ...)
{
	va_list ap;
	
	va_start(ap,fmt);
	vsprintf((char*)TmpVar.srttmp,fmt,ap); 
	va_end(ap);
	ESP8266_SendString ( ENABLE, TmpVar.srttmp, sizeof(TmpVar.srttmp), Single_ID_0 );
	//send(SOCK_TCPC,(uint8_t*)TmpVar.srttmp,sizeof(TmpVar.srttmp));
	//FrameString(TmpVar.srttmp);  
	//gNetCtr.netsta |= TCP_WAIT_TO_SEND;
}



