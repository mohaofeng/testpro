#define FRAME_PKG_C
#include "FramePkg.h"
#include "SysConfig.h"
//#include "usart.h"	 
#include "SysConfig.h"


#define FRAME_PKG_DBG  0

#if TEST_DBG	
void CmpAckCheckBalence(uint16_t x,uint16_t y,uint16_t fsize,uint16_t Fcolor,uint16_t dtim,uint16_t Bcolor,uint8_t soundtype,uint8_t coincnt,char *pname)
{
	uint8_t i=0;
	EnQueue(&gNetDwDxQueu,0x90);
	EnQueue(&gNetDwDxQueu,Sn_ACK_CHECK_BALENCE);	
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>24));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>16));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>8));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(x>>8));
	EnQueue(&gNetDwDxQueu,(uint8_t)(x>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(y>>8));
	EnQueue(&gNetDwDxQueu,(uint8_t)(y>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Fcolor>>8));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Fcolor>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Bcolor>>8));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Bcolor>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(fsize>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(coincnt>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(soundtype>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(dtim>>0));
	EnQueue(&gNetDwDxQueu,(uint8_t)(0>>0));
	while(pname[i] != 0)
	{
		EnQueue(&gNetDwDxQueu,pname[i]);
		i++;
	}
	EnQueue(&gNetDwDxQueu,0);
	EnQueue(&gNetDwDxQueu,0xfe);
	EnQueue(&gNetDwDxQueu,0xfc);
	EnQueue(&gNetDwDxQueu,0xfe);
	EnQueue(&gNetDwDxQueu,0xfc);
#if FRAME_PKG_DBG
	printf("�ظ���ͷ�۷�����\r\n");
#endif
}

void CmpTestPrint(char *pname)
{
	uint8_t i;
	EnQueue(&gNetDwDxQueu,0x90);
	EnQueue(&gNetDwDxQueu,Sn_TEST_PRINTER);	
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>24));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>16));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>8));
	EnQueue(&gNetDwDxQueu,(uint8_t)(Config.deviceid>>0));
	while(pname[i] != 0)
	{
		EnQueue(&gNetDwDxQueu,pname[i]);
		i++;
	}
	EnQueue(&gNetDwDxQueu,0);
	EnQueue(&gNetDwDxQueu,0xfe);
	EnQueue(&gNetDwDxQueu,0xfc);
	EnQueue(&gNetDwDxQueu,0xfe);
	EnQueue(&gNetDwDxQueu,0xfc);
#if FRAME_PKG_DBG
	printf("���������Դ�ӡ������\r\n");
#endif
}

#endif



/***********************************************
Function: ֡ͷ
************************************************/
static void CMDHead(void)
{
	EnQueue(&gNetUpCmpQueu,0x90);
}
/***********************************************
Function: ֡β
************************************************/
static void CMDTail(void)
{
	EnQueue(&gNetUpCmpQueu,0xfe);
	EnQueue(&gNetUpCmpQueu,0xfc);
	EnQueue(&gNetUpCmpQueu,0xfe);
	EnQueue(&gNetUpCmpQueu,0xfc);
}




/***********************************************
Function: �ظ�����ָ��
************************************************/
void FrameRequTest(void)
{
	CMDHead();
	EnQueue(&gNetUpCmpQueu,XnREPOT_TEST_CMD);
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>24));//��½����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>16));//��½����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>8));//��½����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>0));//��½����
	CMDTail();
	#if FRAME_PKG_DBG
	printf("�ظ�����ָ��\r\n");
	#endif
}



/*
 *Function: ����۷�   ����
 *type:1/2/3  ����/ȡ��/��ѯ
 */
void RequestDecMon(uint8_t cmdid,uint8_t *vipstring,uint32_t deccnt) 
{
	uint32_t i=0;
	CMDHead();
	EnQueue(&gNetUpCmpQueu,RequestCMD_MULTFUNC);
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>24));
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>16));
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>8));
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>0));
	
	EnQueue(&gNetUpCmpQueu,cmdid);
	EnQueue(&gNetUpCmpQueu,(uint8_t)(deccnt>>24));//��½����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(deccnt>>16));//��½����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(deccnt>>8));//��½����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(deccnt>>0));//��½����

	while(vipstring[i] != 0)
	{
		EnQueue(&gNetUpCmpQueu,vipstring[i]);
		i++;
	}	
	EnQueue(&gNetUpCmpQueu,0);
	CMDTail();
	#if FRAME_PKG_DBG
	printf("����۷�-����\r\n");
	#endif
}
/***********************************************
Function: �����¼
************************************************/
void FrameLogin(void)
{
	CMDHead();
	EnQueue(&gNetUpCmpQueu,LOGIN_CMD_MULFUN_XFJ);

	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>24));//�豸id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>16));//�豸id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>8));//�豸id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>0));//�豸id
	
	EnQueue(&gNetUpCmpQueu,Config.hwver);//Ӳ���汾
	EnQueue(&gNetUpCmpQueu,Config.swver);//����汾
	EnQueue(&gNetUpCmpQueu,Config.runmod);//����汾
	CMDTail();
	#if FRAME_PKG_DBG
	printf("�����¼\r\n");
	#endif
}

/***********************************************
Function: ��·֡
************************************************/
void FrameLink(void)
{
	CMDHead();
	EnQueue(&gNetUpCmpQueu,XnLINK_CMD);
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>24));//�豸id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>16));//�豸id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>8));//�豸id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>0));//�豸id
	CMDTail();
	#if FRAME_PKG_DBG
	printf("������·֡\r\n");
	#endif
}

/***********************************************
Function: �ظ�����֡
************************************************/
void FrameAckConfig(void)
{
	CMDHead();
	EnQueue(&gNetUpCmpQueu,XnREPOT_InFOR_CMD);
	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>24));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>16));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>8));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>0));	//����id
	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Rmoteip[3]));	//������ip
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Rmoteip[2]));	//������ip
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Rmoteip[1]));	//������ip
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Rmoteip[0]));	//������ip
	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.GateW[3]));	//����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.GateW[2]));	//����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.GateW[1]));	//����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.GateW[0]));	//����
	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Mass[3]));	//��������
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Mass[2]));	//��������
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Mass[1]));	//��������
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.Mass[0]));	//��������
	
	EnQueue(&gNetUpCmpQueu,Config.Localip[3]);	//����ip
	EnQueue(&gNetUpCmpQueu,Config.Localip[2]);	//����ip
	EnQueue(&gNetUpCmpQueu,Config.Localip[1]);	//����ip
	EnQueue(&gNetUpCmpQueu,Config.Localip[0]);	//����ip
	
	EnQueue(&gNetUpCmpQueu,(u8)(Config.RemotePort>>8));	//�������˿ں�
	EnQueue(&gNetUpCmpQueu,(u8)(Config.RemotePort>>0));	//�������˿ں�
	
// 	EnQueue(&gNetUpCmpQueu,(u8)(Config.DecMon>>16));	//���Ѷ��
// 	EnQueue(&gNetUpCmpQueu,(u8)(Config.DecMon>>8));	
// 	EnQueue(&gNetUpCmpQueu,(u8)(Config.DecMon>>0));	
	
	EnQueue(&gNetUpCmpQueu,(u8)(Config.NetMod>>0));	
	
	EnQueue(&gNetUpCmpQueu,(u8)(Config.PlusWith>>0));	//������
	
	EnQueue(&gNetUpCmpQueu,(u8)(Config.PromptTim>>8));	
	EnQueue(&gNetUpCmpQueu,(u8)(Config.PromptTim>>0));	
	
	EnQueue(&gNetUpCmpQueu,(u8)(Config.runmod>>0));	//���з�ʽ
	
	CMDTail();
	#if FRAME_PKG_DBG
	printf("�ظ�ϵͳ����֡\r\n");
	#endif

}


/***********************************************
Function: ��������ѯ
************************************************/
void FrameApply(u32 sn,uint32_t id)
{
	CMDHead();
	EnQueue(&gNetUpCmpQueu,XnCHK_MON_CMD);
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>24));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>16));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>8));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>0));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>24));	//??id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>16));	//??id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>8));	//??id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>0));	//??id	
	CMDTail();
	#if FRAME_PKG_DBG
	printf("??????\r\n");
	#endif
}
/***********************************************
Function: ����۷�
************************************************/
void FrameDecMon(u32 sn,u32 xf,uint32_t id)
{
	CMDHead();
	EnQueue(&gNetUpCmpQueu,XnDEC_MON_CMD);
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>24));//����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>16));//����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>8));//����
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>0));//����
	
	EnQueue(&gNetUpCmpQueu,(xf>>16));//���ѿ���
	EnQueue(&gNetUpCmpQueu,(xf>>8));
	EnQueue(&gNetUpCmpQueu,(xf>>0));
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>24));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>16));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>8));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>0));	//����id	
	CMDTail();
	#if FRAME_PKG_DBG
	printf("����۷�\r\n");
	#endif
}


/***********************************************
Function: ����۷� ɨ��ͷ
************************************************/
void FrameDecMonEXT(u8 imforlen,u8 *imfor,u32 xf,uint32_t id)
{
	uint8_t i=0;
	CMDHead();
	EnQueue(&gNetUpCmpQueu,XnEXT_CMD);	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>24));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>16));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>8));	//����id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(id>>0));	//����id	
	EnQueue(&gNetUpCmpQueu,(xf>>16));//���ѿ���
	EnQueue(&gNetUpCmpQueu,(xf>>8));
	EnQueue(&gNetUpCmpQueu,(xf>>0));
	EnQueue(&gNetUpCmpQueu,(imforlen>>0));
	
	for(i=0;i<imforlen;i++)//
		EnQueue(&gNetUpCmpQueu,imfor[i]);
	
	CMDTail();
	#if FRAME_PKG_DBG
	printf("����۷�\r\n");
	#endif
}
/***********************************************
Function: ���͸�ʽ���ַ���
************************************************/
void FrameString(char *imfor) 
{
	uint16_t i=0;
//	CMDHead();	
	while(imfor[i] != 0)
	{
		EnQueue(&gNetUpCmpQueu,imfor[i]);
		i++;
	}	
	EnQueue(&gNetUpCmpQueu,0);	
//	CMDTail();
}


/***********************************************
Function: ��ȡ������ʱ��
************************************************/
void FrameResTim(void)
{
	CMDHead();
	EnQueue(&gNetUpCmpQueu,XnREQ_TIM_CMD);
	CMDTail();
	#if FRAME_PKG_DBG
	printf("��ȡ������ʱ��\r\n");
	#endif
}

/***********************************************
Function: ��ͷ�ϴ��û�ˢ����Ϣ��������
************************************************/
void FrameUpDxCoinSum(uint32_t sn,uint32_t cnt)
{
	EnQueue(&gNetUpCmpQueu,0x90);
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>24));	//??id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>16));	//??id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>8));	//??id
	EnQueue(&gNetUpCmpQueu,(uint8_t)(Config.deviceid>>0));	//??id	
	EnQueue(&gNetUpCmpQueu,XnREPOT_COIN_CMP);	//????????
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>24));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>16));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>8));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(sn>>0));//??
	EnQueue(&gNetUpCmpQueu,(uint8_t)(cnt>>24));	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(cnt>>16));	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(cnt>>8));	
	EnQueue(&gNetUpCmpQueu,(uint8_t)(cnt>>0));	
	
	EnQueue(&gNetUpCmpQueu,0xfe);
	EnQueue(&gNetUpCmpQueu,0xfc);
	EnQueue(&gNetUpCmpQueu,0xfe);
	EnQueue(&gNetUpCmpQueu,0xfc);
#if FRAME_PKG_DBG
	printf("????????\r\n");
#endif
}





static u32 Cmpcmd_state=0;  //����֡β���״̬
static qsize Cmpcmd_pos=0;  //��ǰָ��ָ��λ��

///***********************************************
//Function: ֡������λ���´�����
//head��֡ͷ
//֡β
//************************************************/
qsize queue_find_cmdForCmp(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail)
{
	qsize cmd_size = 0;
	elementType _data = 0;
	
//	cmd_size = ;
	while(QueueDatLen(Q)>0)
	{
		DeQueue(Q,&_data);
		//showdbg8hex(&_data,1);
		//printf("0x%x,",_data);
		if(Cmpcmd_pos==0&&_data!= head)//ָ���һ���ֽڱ�����֡ͷ����������
		{
#if FRAME_PKG_DBG	
				printf("��Ч֡!��������  ---%d---- byte���ݡ�\r\n",cmd_size);				
#endif
		    return 0;
		}
		if(Cmpcmd_pos<buf_len)//��ֹ���������
		{
			buffer[Cmpcmd_pos++] = _data;
		}
		else
		{
			Cmpcmd_pos = 0;
//			cmd_size = 0;
			Cmpcmd_state = 0;
			ClearQ(Q);
			printf("֡���");
			return 0;
		}
		Cmpcmd_state = ((Cmpcmd_state<<8)|_data);//ƴ�����4���ֽڣ����һ��32λ����
		if(Cmpcmd_state == tail)//���4���ֽ���֡βƥ�䣬�õ�����֡
		{
			cmd_size = Cmpcmd_pos; //ָ���ֽڳ���
			Cmpcmd_state = 0;  //���¼��֡β
			Cmpcmd_pos = 0; //��λָ��ָ��
			return cmd_size;
		}
	}
	return 0;//û���γ�������һ֡
}
static u32 Upcmd_state=0;  //����֡β���״̬
static qsize Upcmd_pos=0;  //��ǰָ��ָ��λ��

///***********************************************
//Function: ֡������λ���´�����
//head��֡ͷ
//֡β
//************************************************/
qsize queue_find_cmdForUp(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail)
{
	qsize cmd_size = 0;
	elementType _data = 0;
	
//	cmd_size = ;
	while(QueueDatLen(Q)>0)
	{
		DeQueue(Q,&_data);
		//showdbg8hex(&_data,1);
		//printf("0x%x,",_data);
		if(Upcmd_pos==0&&_data!= head)//ָ���һ���ֽڱ�����֡ͷ����������
		{
#if FRAME_PKG_DBG	
				printf("��Ч֡!��������  ---%d---- byte���ݡ�\r\n",cmd_size);				
#endif
		    return 0;
		}
		if(Upcmd_pos<buf_len)//��ֹ���������
		{
			buffer[Upcmd_pos++] = _data;
		}
		else
		{
			Upcmd_pos = 0;
//			cmd_size = 0;
			Upcmd_state = 0;
			ClearQ(Q);
			printf("֡���");
			return 0;
		}
		Upcmd_state = ((Upcmd_state<<8)|_data);//ƴ�����4���ֽڣ����һ��32λ����
		if(Upcmd_state == tail)//���4���ֽ���֡βƥ�䣬�õ�����֡
		{
			cmd_size = Upcmd_pos; //ָ���ֽڳ���
			Upcmd_state = 0;  //���¼��֡β
			Upcmd_pos = 0; //��λָ��ָ��
			return cmd_size;
		}
	}
	return 0;//û���γ�������һ֡
}




static u32 Codecmd_state=0;  //����֡β���״̬
static qsize Codecmd_pos=0;  //��ǰָ��ָ��λ��

///***********************************************
//Function: ֡����
//head��֡ͷ
//֡β
//************************************************/
qsize queue_find_cmdForCode(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail)
{
	qsize cmd_size = 0;
	elementType _data = 0;
	
//	cmd_size = ;
	while(QueueDatLen(Q)>0)
	{
		DeQueue(Q,&_data);
		//showdbg8hex(&_data,1);
		//printf("0x%x,",_data);
		if(Codecmd_pos==0&&_data!= head)//ָ���һ���ֽڱ�����֡ͷ����������
		{
#if FRAME_PKG_DBG	
				printf("��Ч֡!��������  ---%d---- byte���ݡ�\r\n",cmd_size);				
#endif
		    return 0;
		}
		if(Codecmd_pos<buf_len)//��ֹ���������
		{
			buffer[Codecmd_pos++] = _data;
		}
		else
		{
			Codecmd_pos = 0;
//			cmd_size = 0;
			Codecmd_state = 0;
			ClearQ(Q);
			printf("֡���");
			return 0;
		}
		Codecmd_state = ((Codecmd_state<<8)|_data);//ƴ�����4���ֽڣ����һ��32λ����
		if(Codecmd_state == tail)//���4���ֽ���֡βƥ�䣬�õ�����֡
		{
			cmd_size = Codecmd_pos; //ָ���ֽڳ���
			Codecmd_state = 0;  //���¼��֡β
			Codecmd_pos = 0; //��λָ��ָ��
			return cmd_size;
		}
	}
	return 0;//û���γ�������һ֡
}

static u32 TFTcmd_state=0;  //����֡β���״̬
static qsize TFTcmd_pos=0;  //��ǰָ��ָ��λ��

///***********************************************
//Function: ֡����
//head��֡ͷ
//֡β
//************************************************/
qsize queue_find_cmdForTFT(PQUEUE Q,elementType *buffer,qsize buf_len,uint8_t head,uint32_t tail)
{
	qsize cmd_size = 0;
	elementType _data = 0;
	
//	cmd_size = ;
	while(QueueDatLen(Q)>0)
	{
		DeQueue(Q,&_data);
		//showdbg8hex(&_data,1);
		//printf("0x%x,",_data);
		if(TFTcmd_pos==0&&_data!= head)//ָ���һ���ֽڱ�����֡ͷ����������
		{
#if FRAME_PKG_DBG	
				printf("��Ч֡!��������  ---%d---- byte���ݡ�\r\n",cmd_size);				
#endif
		    return 0;
		}
		if(TFTcmd_pos<buf_len)//��ֹ���������
		{
			buffer[TFTcmd_pos++] = _data;
		}
		else
		{
			TFTcmd_pos = 0;
//			cmd_size = 0;
			TFTcmd_state = 0;
			ClearQ(Q);
			printf("֡���");
			return 0;
		}
		TFTcmd_state = ((TFTcmd_state<<8)|_data);//ƴ�����4���ֽڣ����һ��32λ����
		if(TFTcmd_state == tail)//���4���ֽ���֡βƥ�䣬�õ�����֡
		{
			cmd_size = TFTcmd_pos; //ָ���ֽڳ���
			TFTcmd_state = 0;  //���¼��֡β
			TFTcmd_pos = 0; //��λָ��ָ��
			return cmd_size;
		}
	}
	return 0;//û���γ�������һ֡
}
