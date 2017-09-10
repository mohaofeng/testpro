
#include <CmpDatprocess.h>
#include "tcp_demo.h"
#include "FramePkg.h"
#include <string.h>
#include "WT588D.H"
#include "SysConfig.h"
#include <printer.h>




uint8_t gNetDwCmdBuff[NET_CMD_MAXLEN];								//�����ݴ���λ������Ļ�����
uint8_t gNetUpCmpCmdBuf[NET_CMD_MAXLEN];							//�����ݴ���λ������Ļ�����
uint8_t gExtTFTLCDCmdBuff[TFT_CMD_MAXLEN];							//���ڲ����������
uint8_t gExtCodeBuff[NET_CMD_MAXLEN];								//��ά���ͷ������ջ�����




QUEUE 	gNetDwDxQueu;										//��λ���´���������
QUEUE 	gNetUpCmpQueu;										//�豸�ϴ���������
QUEUE 	gExtCodeQueu;										//��Ӷ�ά���ͷ��������
QUEUE 	gExtTFTLCDQueu;										//��Ӵ��ڲ�����������


//static uint32_t test_value = 0;//����ֵ
//static uint8_t update_en = 1;//���±��
//static uint32_t timer_tick_last_update = 0; //��һ�θ��µ�ʱ��
//volatile uint32_t  timer_tick_count = 0; //��ʱ������
//static uint16_t current_screen_id = 0;//��ǰ����ID

__VipImfor VipImfor;
__TmpVar TmpVar;	

/*
 *��ά���ͷ���ݽ������봦��
 *
 *
 **/
void CodeDatExp(void)
{
	uint16_t CodeDatlen;
	
	CodeDatlen = queue_find_cmdForCode(&gExtCodeQueu,gExtCodeBuff,CODE_CMD_MAXLEN,CODE_CMD_HEAD,CODE_CMD_TAIL);//ȡ��һ֡����
	if(CodeDatlen  >0)
	{
		 DBG_PRINTF("����1-->��������%s\r\n",gExtCodeBuff);
		//FrameDecMonEXT((CodeDatlen-5),&gExtCodeBuff[1],g_tFlg.gDecMon,Config.deviceid);
		gExtCodeBuff[CodeDatlen-4] = 0;
		memcpy(g_tFlg.VipIDString,&gExtCodeBuff[1],(CodeDatlen-5)); 
		SysVar.GetVipIdFlg = 1;								
		sprintf((char*)g_tFlg.VipIDString,"%s",&gExtCodeBuff[1]); //������ת��Ϊ�ַ���
		//DBG_PRINTF("codeString is��%s\r\n",(char*)g_tFlg.VipIDString);  
//		  printDat(g_tFlg.pString);
	}
	
}







/*
 *�������ظ�����ѯָ��
 *
 *
 **/
void ExpAmountCmd(uint8_t *pbuff)
{
}
/*
 *�������ظ��۷�ָ��
 *
 *
 **/
void ExpDecMonCmd(uint8_t *pbuff)
{
}

/*
 *�������ظ���¼ָ��
 *
 *
 **/
void ExpLoginCmd(uint8_t *pbuff)
{
	
	Config.deviceid = ((u32)pbuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	Config.PromptTim = ((u32)pbuff[6]<<8)+((u32)pbuff[7]<<0);

	Config.DecMon[0] = ((uint16_t)pbuff[8] << 8) + ((uint16_t)pbuff[9]<<0);
	Config.DecMon[1] = ((uint16_t)pbuff[10] << 8) + ((uint16_t)pbuff[11]<<0);
	Config.DecMon[2] = ((uint16_t)pbuff[12] << 8) + ((uint16_t)pbuff[13]<<0);
	Config.DecMon[3] = ((uint16_t)pbuff[14] << 8) + ((uint16_t)pbuff[15]<<0);
	Config.DecMon[4] = ((uint16_t)pbuff[16] << 8) + ((uint16_t)pbuff[17]<<0);
	g_tFlg.gDecMon = Config.DecMon[0];
	
	Config.ICKey[5] = pbuff[18];
	Config.ICKey[4] = pbuff[19];
	Config.ICKey[3] = pbuff[20];
	Config.ICKey[2] = pbuff[21];
	Config.ICKey[1] = pbuff[22];
	Config.ICKey[0] = pbuff[23];
	

	VipImfor.wDecNum = ((u32)pbuff[24]<<24)+((u32)pbuff[25]<<16)+((u32)pbuff[26]<<8)+((u32)pbuff[27]<<0);

	VipImfor.wIdexpos = ((uint16_t)pbuff[28] << 8) + ((uint16_t)pbuff[29]<<0);				//��ʾx����
	VipImfor.wIdeypos = ((uint16_t)pbuff[30] << 8) + ((uint16_t)pbuff[31]<<0);				//��ʾy����
	VipImfor.ucIdeFcolor = ((uint16_t)pbuff[32] << 8) + ((uint16_t)pbuff[33]<<0); 			//��ʾǰ��ɫ
	VipImfor.ucIdeBcolor = ((uint16_t)pbuff[34] << 8) + ((uint16_t)pbuff[35]<<0); 			//��ʾ����ɫ
	
	VipImfor.ucIdeFontsize = pbuff[36];														//��ʾ�����С
	
	SoundCtr.Type = SOUND_LOGINOK_MOD;
	DlyVar.LCDIdeT = Config.PromptTim *1000;
	lcd_parm.distype = DIS_LOGIN_MOD;

	
	sprintf(VipImfor.IdeShowStr,"%s",&pbuff[39]); //���������ַ�
	DBG_PRINTF("�յ���¼ָ��,x����Ϊ:%u,y����Ϊ:%u,ǰ��ɫ:%u,����ɫ:%u,�����С:%u,���Ѷ��:%u,�����ַ�Ϊ:%s\r\n",VipImfor.wIdexpos,VipImfor.wIdeypos,VipImfor.ucIdeFcolor,VipImfor.ucIdeBcolor,VipImfor.ucIdeFontsize,VipImfor.wDecNum,VipImfor.IdeShowStr);


	SysParmWrite();
	SysParmExplain();
	SysParmPrint();
	ClearQ(&gNetUpCmpQueu);
	ClearQ(&gNetDwDxQueu);
	//FrameAckConfig();
}
/*
 *�������������Ѷ��
 *
 *
 **/
void ExpSetCostCmd(uint8_t *pbuff)
{
	Config.DecMon[1] = (((uint32_t)pbuff[6])<<16)+(((uint32_t)pbuff[7])<<8)+(((uint32_t)pbuff[8])<<0);					
	SysParmWrite();
	SysParmExplain();
	SysParmPrint();
	FrameAckConfig();
}
/*
 *�����������豸ID
 *
 *
 **/
void ExpSetIDCmd(uint8_t *pbuff)
{
	uint32_t tmp;
	tmp = ((u32)pbuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		Config.deviceid = ((u32)pbuff[6]<<24)+((u32)pbuff[7]<<16)+((u32)pbuff[8]<<8)+((u32)pbuff[9]<<0);
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		SysReset();
	}
}
/*
 *�����������豸����ģʽ
 *
 *
 **/
void ExpSetRunModeCmd(uint8_t *pbuff)
{
	uint32_t tmp;
	tmp = ((u32)pbuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		Config.runmod = pbuff[6];
		if(Config.runmod == RunMod_CHECK)
		{
			g_tFlg.gDecMon = 0;
		}
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		FrameAckConfig();
	}
}
/*
 *�����������豸ͨ�ŷ�ʽ
 *
 *
 **/
void ExpSetNetModeCmd(uint8_t *pbuff)
{
	uint32_t tmp;
	tmp = ((u32)pbuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		Config.NetMod = pbuff[6];
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		SysReset();
	}
}
/*
 *���������ô�������ָ�ʱ��
 *
 *
 **/
void ExpSetPromptTimCmd(uint8_t *pbuff)
{
	uint32_t tmp;
	tmp = ((u32)pbuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		Config.PromptTim = ((u16)pbuff[6]<<8)+((u16)pbuff[7]<<0);
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		FrameAckConfig();
	}
}

/*
 *�����������豸�ϱҲ���
 *
 *
 **/
void ExpSetPlusPramCmd(uint8_t *pbuff)
{
	uint32_t tmp;
	tmp = ((u32)pbuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		Config.PlusWith = pbuff[6];
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		FrameAckConfig();
	}
}
/*
 *�����������豸ip��Ϣ
 *
 *
 **/
void ExpSetIPPramCmd(uint8_t *pbuff)
{
	uint32_t tmp;
	tmp = ((u32)gNetDwCmdBuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		Config.Localip[3] = pbuff[6];//������ip
		Config.Localip[2] = pbuff[7];//������ip
		Config.Localip[1] = pbuff[8];//������ip
		Config.Localip[0] = pbuff[9];//������ip
		Config.Rmoteip[1] = Config.Localip[1];//������ip���θ��汾��ip����������
		
		Config.GateW[3] = pbuff[10];//����������
		Config.GateW[2] = pbuff[11];//����������
		Config.GateW[1] = pbuff[12];//����������
		Config.GateW[0] = pbuff[13];//����������
		
		Config.Mass[3] = pbuff[14];//��������
		Config.Mass[2] = pbuff[15];//��������
		Config.Mass[1] = pbuff[16];//��������
		Config.Mass[0] = pbuff[17];//��������										
		Config.dhcpsw = 0;
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		SysReset();
	}
}
/*
 *���������÷�����ip��Ϣ
 *
 *
 **/
void ExpSetRemoteIPPramCmd(uint8_t *pbuff)
{
	uint32_t tmp;
	tmp = ((u32)gNetDwCmdBuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		Config.Rmoteip[3] = pbuff[6];//������ip
		Config.Rmoteip[2] = pbuff[7];//������ip
		Config.Rmoteip[1] = pbuff[8];//������ip
		Config.Rmoteip[0] = pbuff[9];//������ip
		
		Config.RemotePort = (((uint16_t)pbuff[10])<<8)+(((uint16_t)pbuff[11])<<0);//�������˿�
		Config.Localip[1] = Config.Rmoteip[1];	  //����ip���θ��������ip����������
		Config.GateW[1]   = Config.Rmoteip[1];		//����������
						
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		SysReset();
	}
}
/*
 *����������wifi���߲���
 *
 *
 **/
void ExpSetWiFiPramCmd(uint8_t *pbuff)
{
	uint8_t i;
	uint32_t tmp;
	
	tmp = ((u32)gNetDwCmdBuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if((Config.deviceid == tmp))//���Ŀ��id�Ƿ���ȷ
	{
		for(i=0;i<gNetDwCmdBuff[6];i++)//ap���ƺ�����
		{
			Config.APName[i]= (uint8_t)gNetDwCmdBuff[8+i];//����
		}
		Config.APName[i] = 0;
		for(i=0;i<gNetDwCmdBuff[7];i++)//ap���ƺ�����
		{
			Config.APPassword[i] = (uint8_t)gNetDwCmdBuff[8+gNetDwCmdBuff[6]+i];//����
		}
		Config.APPassword[i] = 0;
#if NetDatExp_DBG >0 
			printf("�����������ȵ����ƺ�����:%s,%s\r\n",Config.APName,Config.APPassword);
#endif
		SysParmWrite();
		SysParmExplain();
		SysParmPrint();
		SysReset();
	}
}
/*
 *�������ظ���ҳɹ�
 *
 *
 **/
void ExpACKSavedCoinCmd(uint8_t *pbuff)
{
}



/*
 *����������dhcp����
 *
 *
 **/
void ExpSetDHCPSwCmd(uint8_t *pbuff)
{
	Config.dhcpsw = pbuff[6];
	SysParmWrite();
	SysParmExplain();
	SysParmPrint();
}





void ExpSnUpdateGUI(uint8_t *pbuff){
	char *pname;
	uint32_t ucNum=0;
	uint32_t ucI=0;
	uint32_t tmp=0;
	
	tmp = ((u32)pbuff[2]<<24)+((u32)pbuff[3]<<16)+((u32)pbuff[4]<<8)+((u32)pbuff[5]<<0);
	if(Config.deviceid == tmp)//���Ŀ��id�Ƿ���ȷ 
	{
		VipImfor.wDecNum        = ((u32)pbuff[8]<<24)+((u32)pbuff[9]<<16)+((u32)pbuff[10]<<8)+((u32)pbuff[11]<<0);
		VipImfor.cmdid          = pbuff[6];
		switch(Config.runmod)
		{
			case RunMod_KEYINPUT:
				break;
			case RunMod_NORMAL_FIX:
				break;
			case RunMod_NORMAL_DANGWEI:
				break;
			case RunMod_CHECK:
				break;
			case RunMod_SALE_COIN:
				break;
			case RunMod_SALE_SAVER_COIN:
				if((SAVE_CAI_PIAO == VipImfor.cmdid) || ((SAVE_COIN_DAI == VipImfor.cmdid)))//���Ʊ���ߴ��Ҽ�ȥ�Ѵ�Ĳ�Ʊ���ߴ���
				{
					if(SysVar.WaitUpPlusCntSum >= VipImfor.wDecNum)//�����ǰϵͳ����������ڴ���ϵͳ�����������ȥ�Ѿ�������λ��������
					{
						SysVar.WaitUpPlusCntSum -= VipImfor.wDecNum;
					}
				}
				break;
			case RunMod_SAVER_COIN:
				if((SAVE_CAI_PIAO == VipImfor.cmdid) || ((SAVE_COIN_DAI == VipImfor.cmdid)))//���Ʊ���ߴ��Ҽ�ȥ�Ѵ�Ĳ�Ʊ���ߴ���
				{
					if(SysVar.WaitUpPlusCntSum >= VipImfor.wDecNum)//�����ǰϵͳ����������ڴ���ϵͳ�����������ȥ�Ѿ�������λ��������
					{
						SysVar.WaitUpPlusCntSum -= VipImfor.wDecNum;
					}
				}
				break;
			case RunMod_GATE_CTRL:
				break;
			default:
				break;
		}
		
		
		VipImfor.wCoinCnt 			= ((u16)pbuff[12]<<8)+((u16)pbuff[13]<<0);
		VipImfor.wGateCnt 			= ((u16)pbuff[14]<<8)+((u16)pbuff[15]<<0);
		VipImfor.wSountType 		= pbuff[16];
		VipImfor.ScreenWaitTim 	= ((u16)pbuff[17]<<8)+((u16)pbuff[18]<<0);
		VipImfor.wxpos 					= ((u16)pbuff[19]<<8)+((u16)pbuff[20]<<0);
		VipImfor.wypos 					= ((u16)pbuff[21]<<8)+((u16)pbuff[22]<<0);
		VipImfor.ucFcolor 			= ((u16)pbuff[23]<<8)+((u16)pbuff[24]<<0);
		VipImfor.ucBcolor 			= ((u16)pbuff[25]<<8)+((u16)pbuff[26]<<0);
		VipImfor.ucFontsize 		= pbuff[27];
				
		g_tFlg.CoinSigNum += VipImfor.wCoinCnt;
		g_tFlg.GateSigNum += VipImfor.wGateCnt;
		SoundCtr.Type = VipImfor.wSountType;
		if(VipImfor.ScreenWaitTim)
			DlyVar.LCDIdeT = VipImfor.ScreenWaitTim*1000;
		else
			DlyVar.LCDIdeT = Config.PromptTim;
		lcd_parm.distype = DIS_Cmp_MOD;								
		
		pname = (char*)&pbuff[28];
		ucNum = strlen(pname);
		if(ucNum >0 && ucNum<400)
		{
			while(pname[ucI] != 0)
			{
				VipImfor.name[ucI] = pname[ucI];
				ucI++;
			}
		}

		//sprintf(VipImfor.IdeShowStr,"%s",&pbuff[39]); //���������ַ�
		//DBG_PRINTF("�ϱ�����:%u\r\n���Ŵ���:%u\r\n�������:%u\r\n�ָ�ʱ��:%u\r\nx����:%u\r\ny����:%u\r\nǰ��ɫ:%u\r\n����ɫ:%u\r\n�����С:%u\r\n�����ַ�Ϊ:%s\r\n",VipImfor.wCoinCnt,VipImfor.wGateCnt,VipImfor.wSountType,VipImfor.ScreenWaitTim,VipImfor.wxpos,VipImfor.wypos,VipImfor.ucFcolor,VipImfor.ucBcolor,VipImfor.ucFontsize,VipImfor.name);
		
	}
}

/*
 *���������Դ�ӡ
 *
 *
 **/
void ExpTestPrintCmd(uint8_t *pbuff)
{
//	sprintf((char*)TmpVar.srttmp,"%s\r\n",&pbuff[6]); //������ת��Ϊ�ַ���
	printDat("%s\r\n",&pbuff[6]);
	DBG_PRINTF("���Դ�ӡ������Ϊ��%s\r\n",&pbuff[6]);
	memset(&pbuff[6],0,strlen((char*)&pbuff[6]));
	//printDat((uint8_t*)TmpVar.srttmp);
}

/*
 *��̫�����ݽ������봦��
 *
 *
 **/
void NetDatExp(void)
{
	//char stringbuf[100];
	uint16_t NetRxbuffLen;
	uint16_t NetTxbuffLen;
	/*--------------tcp��������-------------------*/
	NetRxbuffLen = queue_find_cmdForCmp(&gNetDwDxQueu,gNetDwCmdBuff,NET_CMD_MAXLEN,NET_CMD_HEAD,NET_CMD_TAIL);//ȡ��һ֡����
	if(NetRxbuffLen >0)
	{
		printf("�������´�ָ�");
		showdbg8hex(gNetDwCmdBuff,NetRxbuffLen);
		gNetCtr.LinkGas = LinkGas_CONST;
		gNetCtr.LinkRetryCnt = 0;
		gNetCtr.NetConnectRetryCnt = 0;
		//Arr2String(stringbuf,gNetDwCmdBuff,NetRxbuffLen);
	 	//DBG_PRINTF("%s\r\n",gNetDwCmdBuff);
		switch(gNetDwCmdBuff[CMD_POS])
		{
			case SnRE_AMOUNT_CMD:			
				ExpAmountCmd(gNetDwCmdBuff);
				break;
			case SnRE_DEC_MON_CMD:
				ExpDecMonCmd(gNetDwCmdBuff);
				break;											
			case Sn_REQXnIMFo_CMD:
				//FrameAckConfig(gNetDwCmdBuff);
				break;
			case Sn_Login_CMD:
				ExpLoginCmd(gNetDwCmdBuff);
				break;
			case Sn_SETDECMON_CMD:
				ExpSetCostCmd(gNetDwCmdBuff);
				break;
			case Sn_LINK_CMD:
				if(gNetCtr.flg ==0)
				{
					gNetCtr.flg = 1;
					DlyVar.LCDIdeT = Config.PromptTim;
					FrameLogin();
				}
				break;
			case Sn_CONFIG_ID_CMD:
				ExpSetIDCmd(gNetDwCmdBuff);
				break;	
			case Sn_SET_RUMMOD_CMD:
				ExpSetRunModeCmd(gNetDwCmdBuff);
				break;	
			case Sn_SET_Netmod:
				ExpSetNetModeCmd(gNetDwCmdBuff);
				break;	
			case Sn_PromptTIM:
				ExpSetPromptTimCmd(gNetDwCmdBuff);
				break;	
			case Sn_CONFIG_PLUS_CMD:
				ExpSetPlusPramCmd(gNetDwCmdBuff);
			break;	
			case Sn_CONFIG_IP_CMD:
				ExpSetIPPramCmd(gNetDwCmdBuff);
				break;	
			case Sn_SET_RemotIP:
				ExpSetRemoteIPPramCmd(gNetDwCmdBuff);
				break;	
			case Sn_SET_AP_NAME_PASSWORD:
				ExpSetWiFiPramCmd(gNetDwCmdBuff);
				break;	
			case Sn_ACK_COIN:
				ExpACKSavedCoinCmd(gNetDwCmdBuff);
				break;		
			case Sn_TEST:
				break;
			
			case Sn_UPDATE_GUI:
				ExpSnUpdateGUI(gNetDwCmdBuff);
				memset(gNetDwCmdBuff,0,NetRxbuffLen);
				break;
			case Sn_OUT_TEST:
				g_tFlg.CoinSigNum += gNetDwCmdBuff[6];
				break;
			case Sn_Config_DHCP:
				ExpSetDHCPSwCmd(gNetDwCmdBuff);
				break;
			case Sn_TEST_PRINTER:
				ExpTestPrintCmd(gNetDwCmdBuff);
				memset(gNetDwCmdBuff,0,NetRxbuffLen);
				break;
			
			default:			
				break;
		}
	}
	/*--------------tcp��������-------------------*/
	NetTxbuffLen = queue_find_cmdForUp(&gNetUpCmpQueu,gNetUpCmpCmdBuf,NET_CMD_MAXLEN,NET_CMD_HEAD,NET_CMD_TAIL);
	if(NetTxbuffLen>0){
//	 DBG_PRINTF("%s\r\n",gNetUpCmpCmdBuf);
	printf("��Ʊ���ϴ�ָ�");
	showdbg8hex(gNetUpCmpCmdBuf,NetTxbuffLen);
	gNetCtr.netsta |= TCP_WAIT_TO_SEND;
	gNetCtr.RxFrameBufLen = NetTxbuffLen;
	}
	else if(gNetCtr.LinkGas == 0){
		gNetCtr.LinkGas = LinkGas_CONST;
		FrameLink();
		if(++gNetCtr.LinkRetryCnt>LINK_MAX_NUM){
			DBG_PRINTF("�����Ѿ��Ͽ�\r\n");
			gNetCtr.LinkRetryCnt = 0;
			gNetCtr.flg = 0;
			//gNetCtr.netsta &=(~TCP_CONNECTED);//�������failed,����������
		}
	}
}







/*
 *7�紮�ڲ������ݽ������봦��
 *
 *
 **/
void ScomTftCmdExp(void)
{
	uint16_t STFTCmdLen;
/*--------------tcp��������-------------------*/
	STFTCmdLen = queue_find_cmdForTFT(&gExtTFTLCDQueu,gExtTFTLCDCmdBuff,TFT_CMD_MAXLEN,TFT_CMD_HEAD,TFT_CMD_TAIL);//ȡ��һ֡����
	if(STFTCmdLen>0)
	{
		//DBG_PRINTF("%s\r\n",gExtTFTLCDCmdBuff);
		ProcessMessage((PCTRL_MSG)gExtTFTLCDCmdBuff, STFTCmdLen);//ָ���
		
//		/****************************************************************************************************************
//		�ر�ע��
//		MCU��ҪƵ���򴮿����������ݣ����򴮿������ڲ��������������Ӷ��������ݶ�ʧ(��������С����׼��8K��������4.7K)
//		1) һ������£�����MCU�򴮿����������ݵ����ڴ���100ms���Ϳ��Ա������ݶ�ʧ�����⣻
//		2) �����Ȼ�����ݶ�ʧ�����⣬���жϴ�������BUSY���ţ�Ϊ��ʱ���ܷ������ݸ���������
//		******************************************************************************************************************/

//		//TODO: ����û�����
//		//�����и���ʱ��ÿ100����ˢ��һ��
//		if(update_en&&timer_tick_count-timer_tick_last_update>=TIME_100MS)
//		{
//			update_en = 0;
//			timer_tick_last_update = timer_tick_count;			

//			UpdateUI();
//		}

//		//����Ϊ����ʾ���㣬ÿ100�����Զ�����һ��
//		if(timer_tick_count-timer_tick_last_update>=TIME_100MS)
//		{
//			timer_tick_last_update = timer_tick_count;
//			//UpdateUI();
//		}
//		//FrameDecMonEXT((SLen-5),&ExtDev[1],gFlg.gDecMon,Config.deviceid);
	}
}


/*! 
 *  \brief  ��Ϣ��������
 *  \param msg ��������Ϣ
 *  \param size ��Ϣ����
 *  \��Ϣ�����ͣ�
			0xB1 :
 */
void ProcessMessage( PCTRL_MSG msg, uint16_t size )
{
	uint8_t cmd_type = msg->cmd_type;//ָ������
	uint8_t ctrl_msg = msg->ctrl_msg;   //��Ϣ������
	uint8_t control_type = msg->control_type;//�ؼ�����
	uint16_t screen_id = PTR2U16(&msg->screen_id);//����ID
	uint16_t control_id = PTR2U16(&msg->control_id);//�ؼ�ID
	uint32_t value = PTR2U32(msg->param);//��ֵ


	lcd_parm.current_screen_id = screen_id;
	lcd_parm.old_screen_id = lcd_parm.new_screen_id;
	lcd_parm.new_screen_id= lcd_parm.current_screen_id;
	
	switch(cmd_type)
	{		
	case NOTIFY_TOUCH_PRESS://����������
	case NOTIFY_TOUCH_RELEASE://�������ɿ�
		NotifyTouchXY(gExtTFTLCDCmdBuff[1],PTR2U16(gExtTFTLCDCmdBuff+2),PTR2U16(gExtTFTLCDCmdBuff+4));
		break;	
	case NOTIFY_WRITE_FLASH_OK://дFLASH�ɹ�
		NotifyWriteFlash(1);
		break;
	case NOTIFY_WRITE_FLASH_FAILD://дFLASHʧ��
		NotifyWriteFlash(0);
		break;
	case NOTIFY_READ_FLASH_OK://��ȡFLASH�ɹ�
		NotifyReadFlash(1,gExtTFTLCDCmdBuff+2,size-6);//ȥ��֡ͷ֡β
		break;
	case NOTIFY_READ_FLASH_FAILD://��ȡFLASHʧ��
		NotifyReadFlash(0,0,0);
		break;
	case NOTIFY_READ_RTC://��ȡRTCʱ��
		NotifyReadRTC(gExtTFTLCDCmdBuff[1],gExtTFTLCDCmdBuff[2],gExtTFTLCDCmdBuff[3],gExtTFTLCDCmdBuff[4],gExtTFTLCDCmdBuff[5],gExtTFTLCDCmdBuff[6],gExtTFTLCDCmdBuff[7]);
		break;
	case NOTIFY_CONTROL:
		{
			if(ctrl_msg==MSG_GET_CURRENT_SCREEN)//����ID�仯֪ͨ
			{
				NotifyScreen(screen_id);
			}
			else
			{
				switch(control_type)
				{
				case kCtrlButton: //��ť�ؼ�
					NotifyButton(screen_id,control_id,msg->param[1]);
					break;
				case kCtrlText://�ı��ؼ�
					NotifyText(screen_id,control_id,msg->param);
					break;
				case kCtrlProgress: //�������ؼ�
					NotifyProgress(screen_id,control_id,value);
					break;
				case kCtrlSlider: //�������ؼ�
					NotifySlider(screen_id,control_id,value);
					break;
				case kCtrlMeter: //�Ǳ�ؼ�
					NotifyMeter(screen_id,control_id,value);
					break;
				case kCtrlMenu://�˵��ؼ�
					NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);
					break;
				case kCtrlSelector://ѡ��ؼ�
					NotifySelector(screen_id,control_id,msg->param[0]);
					break;
				case kCtrlRTC://����ʱ�ؼ�
					NotifyTimer(screen_id,control_id);
					break;
				default:
					break;
				}
			}			
		}
		break;
	default:
		break;
	}
}

/*! 
 *  \brief  �����л�֪ͨ
 *  \details  ��ǰ����ı�ʱ(�����GetScreen)��ִ�д˺���
 *  \param screen_id ��ǰ����ID
 */
void NotifyScreen(uint16_t screen_id)
{
	//TODO: ����û�����
	lcd_parm.current_screen_id = screen_id;//�ڹ��������п��������л�֪ͨ����¼��ǰ����ID

	if(lcd_parm.current_screen_id==4)//�¶�����
	{
		uint16_t i = 0;
		uint8_t dat[100] = {0};

		//���ɷ���
		for (i=0;i<100;++i)
		{
			if((i%20)>=10)
				dat[i] = 200;
			else
				dat[i] = 20;
		}
		GraphChannelDataAdd(4,1,0,dat,100);//������ݵ�ͨ��0

		//���ɾ�ݲ�
		for (i=0;i<100;++i)
		{
			dat[i] = 16*(i%15);
		}
		GraphChannelDataAdd(4,1,1,dat,100);//������ݵ�ͨ��1
	}
	else if(lcd_parm.current_screen_id==9)//��ά��
	{
		//��ά��ؼ���ʾ�����ַ�ʱ����Ҫת��ΪUTF8���룬
		//ͨ����ָ�����֡���ת�������ݴ��123�� ���õ��ַ�����������
		uint8_t dat[] = {0xE5,0xB9,0xBF,0xE5,0xB7,0x9E,0xE5,0xA4,0xA7,0xE5,0xBD,0xA9,0x31,0x32,0x33};
		SetTextValue(9,1,dat);
	}
}

/*! 
 *  \brief  ���������¼���Ӧ
 *  \param press 1���´�������3�ɿ�������
 *  \param x x����
 *  \param y y����
 */
void NotifyTouchXY(uint8_t press,uint16_t x,uint16_t y)
{
	//TODO: ����û�����
}

void SetTextValueInt32(uint16_t screen_id, uint16_t control_id,uint32_t value)
{
	uint8_t buffer[12] = {0};
	sprintf((char*)buffer,"%ld",value); //������ת��Ϊ�ַ���
	SetTextValue(screen_id,control_id,buffer);
}

void SetTextValueFloat(uint16_t screen_id, uint16_t control_id,float value)
{
	uint8_t buffer[12] = {0};
	sprintf((char*)buffer,"%.1f",value);//�Ѹ�����ת��Ϊ�ַ���(����һλС��)
	SetTextValue(screen_id,control_id,buffer);
}

/*! 
 *  \brief  ��ť�ؼ�֪ͨ
 *  \details  ����ť״̬�ı�(�����GetControlValue)ʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param state ��ť״̬��0����1����
 */
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t  state)
{
	switch(screen_id){					
/*   ��ʾϵͳ��������   */
			case SHOW_SYSPARM_SCREEN_ID:
				
				switch(control_id){
					//���ÿ���
					case SHOW_SYSPARM_SCREEN_SET_BUTTON_ID:
						lcd_parm.LcdTaskRunFlg = 1;
						break;
					//�˳�����
					case SHOW_SYSPARM_SCREEN_QUIT_BUTTON_ID:
						lcd_parm.LcdTaskRunFlg = 0;
						break;
					case SHOW_SYSPARM_SCREEN_COIN_STA_BUTTON_ID:
						/*Ͷ�ҿ�״̬*/
						switch(Config.ttlLe)
						{
							case TTL_NC:
								Config.ttlLe = TTL_NO;
								//Lcd_Show(147,415,1,ASCII_12X24,"NO "); 
								break;
							case TTL_NO:
								Config.ttlLe = TTL_NC;
								//Lcd_Show(147,415,1,ASCII_12X24,"NC "); 
								break;
							default:
								Config.ttlLe = TTL_NC;
								//Lcd_Show(147,415,1,ASCII_12X24,"NC "); 
								break;
						}
						break;
					case SHOW_SYSPARM_SCREEN_GATE_STA_BUTTON_ID:
						/*�����ź�״̬*/
						switch(Config.GateSta)
						{
							case GATE_NC:
								Config.GateSta = GATE_NO;
								//Lcd_Show(147,375,1,ASCII_12X24,"NO "); 
								break;
							case GATE_NO:
								Config.GateSta = GATE_NC;
								//Lcd_Show(147,375,1,ASCII_12X24,"NC "); 
								break;
							default:
								Config.GateSta = GATE_NO;
								//Lcd_Show(147,375,1,ASCII_12X24,"NO "); 
								break;
						}
						break;
					case SHOW_SYSPARM_SCREEN_DHCP_SW_BUTTON_ID:
						/*DHCP����*/
						switch(Config.dhcpsw)
						{
							case DHCP_OFF:
								Config.dhcpsw = DHCP_ON;
								//Lcd_Show(680,130,1,ASCII_12X24,"ON "); 
								break;
							case DHCP_ON:
								Config.dhcpsw = DHCP_OFF;
								//Lcd_Show(680,130,1,ASCII_12X24,"OFF"); 
								break;
							default:
								Config.dhcpsw = DHCP_ON;
								//Lcd_Show(680,130,1,ASCII_12X24,"ON "); 
								break;
						}
					break;
					case SHOW_SYSPARM_SCREEN_NET_MOD_BUTTON_ID:
						switch(Config.NetMod)
						{
							case NET_RJ45:
								Config.NetMod = NET_WIFI;
								//Lcd_Show(675,75,1,ASCII_12X24,"WiFi "); 
								break;
							case NET_WIFI:
								Config.NetMod = NET_RJ45;
								//Lcd_Show(675,75,1,ASCII_12X24,"���� "); 
								break;
							default:
								Config.NetMod = NET_RJ45;
								//Lcd_Show(675,75,1,ASCII_12X24,"���� "); 
								break;
						}
					break;
					case SHOW_SYSPARM_SCREEN_RUN_MOD_BUTTON_ID:
						/*����ģʽ*/
						switch(Config.runmod)
						{
							case RunMod_KEYINPUT:
								Config.runmod = RunMod_NORMAL_FIX;
								//Lcd_Show(626,180,1,ASCII_12X24,"�̶�����ģʽ "); 
								break;
							case RunMod_NORMAL_FIX:
								Config.runmod = RunMod_NORMAL_DANGWEI;
								//Lcd_Show(626,180,1,ASCII_12X24,"��λ����ģʽ "); 
								break;
							case RunMod_NORMAL_DANGWEI:
								Config.runmod = RunMod_CHECK;
								//Lcd_Show(626,180,1,ASCII_12X24,"  ��ѯ��ģʽ "); 
								break;
							case RunMod_CHECK:
								Config.runmod = RunMod_SAVER_COIN;
								//Lcd_Show(626,180,1,ASCII_12X24,"   ���ģʽ  "); 
								break;
							case RunMod_SAVER_COIN:
								Config.runmod = RunMod_SALE_COIN;
								//Lcd_Show(626,180,1,ASCII_12X24,"   �۱�ģʽ  "); 
								break;
							case RunMod_SALE_COIN:
								Config.runmod = RunMod_SALE_SAVER_COIN;
								//Lcd_Show(626,180,1,ASCII_12X24,"��ȡһ��ģʽ "); 
								break;
							case RunMod_SALE_SAVER_COIN:
								Config.runmod = RunMod_GATE_CTRL;
								//Lcd_Show(626,180,1,ASCII_12X24,"��բ����ģʽ "); 
								break;
							case RunMod_GATE_CTRL:
								Config.runmod = RunMod_KEYINPUT;
								//Lcd_Show(626,180,1,ASCII_12X24,"��������ģʽ "); 
								break;
							default:
								Config.runmod = RunMod_NORMAL_FIX;
								//Lcd_Show(626,180,1,ASCII_12X24,"�̶�����ģʽ "); 
								break;
						}
						break;
					default:
						break;
			}
			SysParmWrite();
			SysParmExplain();
			LCDShowSysParm();
			SysParmPrint();
	break;
/*   ����ϵͳ�����������    */
			case SET_SYSPARM_FOR_NET_SCREEN_ID:
			break;
			
/*   �̶�������ѻ�����*/
		case FIXED_MON_SCREEN_ID:
			switch(control_id){
			}							
		break;
/*   �ɱ䵵λ���ѻ����� */
			case STALL_MON_SCREEN_ID:
				switch(control_id)
				{ 
					case BT_STALL_MON_SCREEN_ID:
					break;
				}
				break;
/*   �ɱ䵵λ���ѻ����� */
			case IDE_STALL_MON_SCREEN_ID:
				switch(control_id)
				{
					case BT_STALL_MON_SCREEN_ID:
						if(++g_tFlg.gDecMonCnt >= DEC_CNT_MAX)
							g_tFlg.gDecMonCnt = 0;
						g_tFlg.gDecMon = Config.DecMon[g_tFlg.gDecMonCnt];
						ClearLayer(0);
						SetScreen(IDE_STALL_MON_SCREEN_ID);
						Lcd_Show(250, 180,0,GBK_64X64,"%d.%d Ԫ/��\r\n ",g_tFlg.gDecMon/10,g_tFlg.gDecMon%10);
					break;
					default:
					break;
				}
			break;
/*  �����������ѻ����� */
		case KEY_INPUT_MON_SCREEN_ID:
				switch(control_id){
				}
		break;
/*  ��Աȡ�ҽ���  */
		case VIP_QUBI_SCREEN_ID:
		break;
/*  ��Ա��ҽ���  */
		case VIP_CUN_SCREEN_ID:
		break;
/* ��Ա���ҽ����µĲ��� */	
		case VIP_GOUBI_SCREEN_ID:
			/* ���˿��Ѿ���ѯ���������Ϣ������Խ��й��Ҳ��� */
			if((SysVar.ALLFlg && CHECK_MON_FLG)){
				switch(control_id){
				}				
			}
		break;
		default:
		break;
	}
	//TODO: ����û�����
	if(screen_id==3)//��ť��ͼ�ꡢ��������
	{
		if(control_id==3)//���а�ť
		{
			if(state==0)//ֹͣ����
			{				
				AnimationPlayFrame(3,1,1);//��ʾֹͣͼ��
				AnimationStop(3,2);//����ֹͣ����
			}
			else//��ʼ����
			{				
				SetControlVisiable(3,1,1);//��ʾͼ��
				SetControlVisiable(3,2,1);//��ʾ����

				AnimationPlayFrame(3,1,0);//��ʾ����ͼ��
				AnimationStart(3,2);//������ʼ����
			}		
		}
		else if(control_id==4)//��λ��ť
		{
			SetControlVisiable(3,1,0);//����ͼ��
			SetControlVisiable(3,2,0);//���ض���
			SetButtonValue(3,3,0);//��ʾ��ʼ����
		}
	}
}


uint8_t CheckCharNum(char c,char *str)
{
	uint8_t inum = 0;
	uint8_t i=0;
	while(str[i])
	{
		if(str[i] == c)inum++;
		i++;
	}
	return inum;
}



/*
 *����ַ����Ƿ���Ϲ淶���ַ������ȱ���<max >min �Ұ��� cnt���ַ� c
 *
 **/
int CheckStr(uint8_t min,uint8_t max,char c,uint8_t cnt,uint8_t *tmpbuf,char *mstrpc)
{
	uint8_t i=0;
	
	/* ����ַ������� */
	if(strlen(mstrpc)<= max && strlen(mstrpc)>= min)
	{
		/* �������ƶ��ַ������� */
		if(CheckCharNum(c,mstrpc) == cnt)
		{
			strcpy(TmpVar.srttmp,mstrpc);
			TmpVar.pc[0] = TmpVar.srttmp;
			for(i=0;i<cnt;i++) 
			{
				TmpVar.pc[i+1]=strchr(TmpVar.pc[i],c);
				*TmpVar.pc[i+1] = 0;
				TmpVar.pc[i+1] += 1;
				
			}
			for(i=0;i<cnt+1;i++) 
			{
				/* ����ַ����Ƿ���Ч */
				if(strlen(TmpVar.pc[i]) <1)
				{
					DBG_PRINTF("�����ַ������Ϲ淶���˳���鲽��\r\n");
					return -1;
				}
				tmpbuf[i] = atoi(TmpVar.pc[i]);
				DBG_PRINTF("%d",tmpbuf[i]);
			}
			return 0;
		}
		else
		{
			DBG_PRINTF("δ�����ƶ��������ַ�\r\n");
			return -1;
		}
	}
	else
	{
		DBG_PRINTF("�ַ����Ȳ���ȷ\r\n");
		return -1;
	}
}


uint32_t GetStrValue(char *tmpbuf)
{
	uint32_t itmp=0;
	strcpy(TmpVar.srttmp,tmpbuf);
	TmpVar.pc[0] = TmpVar.srttmp;
	if(strlen(TmpVar.srttmp)>0 && strlen(TmpVar.srttmp) <=8)
	{
		TmpVar.pc[1] = strchr(TmpVar.pc[0],'.');//��������
		if(TmpVar.pc[1] != NULL)//��������Ƿ���С������
		{
			(*TmpVar.pc[1]) = 0;
			TmpVar.pc[2] = (TmpVar.pc[1]+1);
			if(strlen(TmpVar.pc[2]) > 0 && strlen(TmpVar.pc[2]) < 2 )//С������Ϊһλ��
			{
				itmp = atoi(TmpVar.pc[0])*10 + atoi(TmpVar.pc[2])*1;	
				Lcd_Show(400,450,0,ASCII_12X24,"               "); 
			}
			else
			{
				Lcd_Show(400,450,0,ASCII_12X24,"С��������Ϊһλ "); 
				//Update_LcdText(IDE_KEY_INPUT_MON_SCREEN_ID,KEY_INPUT_MON_SCREEN_TEXT_ID,"����");				
				itmp = 0;
			}
			//return(atoi(TmpVar.pc[0])*10 + atoi(TmpVar.pc[2])*1);//����С�����֣�����С������������		
		}
		else{
			itmp = atoi(TmpVar.pc[0])*10;	
			//return(atoi(TmpVar.pc[0])*10);//����ֻ���������֣�ֱ��ת��
		}
		return(itmp);
	}
	return(0);
}

/*! 
 *  \brief  �ı��ؼ�֪ͨ
 *  \details  ���ı�ͨ�����̸���(�����GetControlValue)ʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param str �ı��ؼ�����
 */
void NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str)
{
	char *pc;
	uint8_t ucbuf[100];
	uint16_t ucNum;
	uint32_t uiNum;
	//TODO: ����û�����
//	uint32_t value = 0; 
	pc = (char*)str;
	switch(screen_id){					
/*   ��ʾϵͳ��������   */
			case SHOW_SYSPARM_SCREEN_ID:
				switch(control_id){
//������ip�ı���
					case SHOW_SYSPARM_SCREEN_REMOTE_IP_TEXT_ID:
						if(CheckStr(7,15,'.',3,ucbuf,pc) == 0 )
						{
							Config.Rmoteip[0] = ucbuf[0];
							Config.Rmoteip[1] = ucbuf[1];
							Config.Rmoteip[2] = ucbuf[2];
							Config.Rmoteip[3] = ucbuf[3];
						}
						break;
//���������ı���
					case SHOW_SYSPARM_SCREEN_SUB_NET_TEXT_ID:
						if(CheckStr(7,15,'.',3,ucbuf,pc) == 0 )
						{
							Config.Mass[0] = ucbuf[0];
							Config.Mass[1] = ucbuf[1];
							Config.Mass[2] = ucbuf[2];
							Config.Mass[3] = ucbuf[3];
						}
						break;
//Ĭ�������ı���
					case SHOW_SYSPARM_SCREEN_GATE_WAY_TEXT_ID:
						if(CheckStr(7,15,'.',3,ucbuf,pc) == 0 )
						{
							Config.GateW[0] = ucbuf[0];
							Config.GateW[1] = ucbuf[1];
							Config.GateW[2] = ucbuf[2];
							Config.GateW[3] = ucbuf[3];
						}
					break;
//����ip�ı���
					case SHOW_SYSPARM_SCREEN_LOCAL_IP_TEXT_ID:
						if(CheckStr(7,15,'.',3,ucbuf,pc) == 0 )
						{
							Config.Localip[0] = ucbuf[0];
							Config.Localip[1] = ucbuf[1];
							Config.Localip[2] = ucbuf[2];
							Config.Localip[3] = ucbuf[3];
						}
					break;
//WIFI�����ı���
					case SHOW_SYSPARM_SCREEN_WIFI_NAME_TEXT_ID:
						if(strlen(pc)>0 && strlen(pc) <=64)
						{
							strcpy((char*)Config.APName,pc);
						}
						break;
//WIFI�����ı���
					case SHOW_SYSPARM_SCREEN_WIFI_PWD_TEXT_ID:
						if(strlen(pc)>0 && strlen(pc) <=64)
						{
							strcpy((char*)Config.APPassword,pc);
						}
						break;
//�������˿ں��ı���
					case SHOW_SYSPARM_SCREEN_REMOTE_PORT_TEXT_ID:
						if(strlen(pc)>0 && strlen(pc) <=5)
						{
							ucNum = atoi(pc);
							Config.RemotePort = (uint16_t)ucNum;
						}
						break;
//����ʱ��
					case SHOW_SYSPARM_SCREEN_GATE_TIM_TEXT_ID:
						if(strlen(pc)>0 && strlen(pc) <=10)
						{
							uiNum = atoi(pc);
							Config.GateWith = (uint32_t)uiNum;
						}
						break;
//�ϱ�ʱ��
					case SHOW_SYSPARM_SCREEN_PULS_TIM_TEXT_ID:
						if(strlen(pc)>0 && strlen(pc) <=10)
						{
							uiNum = atoi(pc);
							Config.PlusWith = (uint32_t)uiNum;
						}
						break;
//���ż��
					case SHOW_SYSPARM_SCREEN_GATE_GAS_TEXT_ID:
						if(strlen(pc)>0 && strlen(pc) <=10)
						{
							uiNum = atoi(pc);
							Config.GateGas = (uint32_t)uiNum;
						}
						break;
//�ϱҼ��
					case SHOW_SYSPARM_SCREEN_PULS_GAS_TEXT_ID:
						if(strlen(pc)>0 && strlen(pc) <=10)
						{
							uiNum = atoi(pc);
							Config.PlusGas = (uint32_t)uiNum;
						}
						break;
//����mac�ı���
					case SHOW_SYSPARM_SCREEN_MAC_ADDR_TEXT_ID:
						if(CheckStr(11,23,'.',5,ucbuf,pc) == 0 )
						{
							Config.Mac[0] = ucbuf[0];
							Config.Mac[1] = ucbuf[1];
							Config.Mac[2] = ucbuf[2];
							Config.Mac[3] = ucbuf[3];
							Config.Mac[4] = ucbuf[4];
							Config.Mac[5] = ucbuf[5];
						}
						break;					
					default:
						break;
			}
			SysParmWrite();
			SysParmExplain();
			LCDShowSysParm();
			SysParmPrint();
			W5500Init();
	break;
/*   ����ϵͳ�����������    */
			case SET_SYSPARM_FOR_NET_SCREEN_ID:
			break;
			
/*   �̶�������ѻ�����*/
		case FIXED_MON_SCREEN_ID:
			switch(control_id){
			}							
		break;
/*   �ɱ䵵λ���ѻ����� */
			case STALL_MON_SCREEN_ID:
				switch(control_id){
					case 1:
						if(++g_tFlg.gDecMonCnt >= DEC_CNT_MAX)
							g_tFlg.gDecMonCnt = 0;
						g_tFlg.gDecMon = Config.DecMon[g_tFlg.gDecMonCnt];
						ClearLayer(0);
						Lcd_Show(250, 180,0,GBK_64X64,"%d.%d Ԫ/��\r\n\r\n ",g_tFlg.gDecMon/10,g_tFlg.gDecMon%10);
					break;
					default:
					break;
			}
			break;
/*  �����������ѻ����� */
		case IDE_KEY_INPUT_MON_SCREEN_ID:
				switch(control_id){
					case KEY_INPUT_MON_SCREEN_TEXT_ID:
						g_tFlg.gDecMon =GetStrValue(pc);
						Lcd_Show(350,50,0,GBK_24X24,"���ѽ��Ϊ��%d.%d\r\n   ��ˢ��",g_tFlg.gDecMon / 10,g_tFlg.gDecMon % 10); 		
						break;
						
				}
		break;
/*  ��Աȡ�ҽ���  */
		case VIP_QUBI_SCREEN_ID:
		break;
/*  ��Ա��ҽ���  */
		case VIP_CUN_SCREEN_ID:
		break;
/* ��Ա���ҽ����µĲ��� */	
		case VIP_GOUBI_SCREEN_ID:
			/* ���˿��Ѿ���ѯ���������Ϣ������Խ��й��Ҳ��� */
			if((SysVar.ALLFlg && CHECK_MON_FLG)){
				switch(control_id){
				}				
			}
		break;
		default:
		break;
	}
}

/*! 
 *  \brief  �������ؼ�֪ͨ
 *  \details  ����GetControlValueʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param value ֵ
 */
void NotifyProgress(uint16_t screen_id, uint16_t control_id, uint32_t value)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  �������ؼ�֪ͨ
 *  \details  ���������ı�(�����GetControlValue)ʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param value ֵ
 */
void NotifySlider(uint16_t screen_id, uint16_t control_id, uint32_t value)
{
	//TODO: ����û�����
	if(screen_id==5&&control_id==2)//�������
	{
		lcd_parm.test_value = value;

		SetProgressValue(5,1,lcd_parm.test_value); //���½�������ֵ
	}
}

/*! 
 *  \brief  �Ǳ�ؼ�֪ͨ
 *  \details  ����GetControlValueʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param value ֵ
 */
void NotifyMeter(uint16_t screen_id, uint16_t control_id, uint32_t value)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  �˵��ؼ�֪ͨ
 *  \details  ���˵���»��ɿ�ʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param item �˵�������
 *  \param state ��ť״̬��0�ɿ���1����
 */
void NotifyMenu(uint16_t screen_id, uint16_t control_id, uint8_t  item, uint8_t  state)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  ѡ��ؼ�֪ͨ
 *  \details  ��ѡ��ؼ��仯ʱ��ִ�д˺���
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 *  \param item ��ǰѡ��
 */
void NotifySelector(uint16_t screen_id, uint16_t control_id, uint8_t  item)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  ��ʱ����ʱ֪ͨ����
 *  \param screen_id ����ID
 *  \param control_id �ؼ�ID
 */
void NotifyTimer(uint16_t screen_id, uint16_t control_id)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  ��ȡ�û�FLASH״̬����
 *  \param status 0ʧ�ܣ�1�ɹ�
 *  \param _data ��������
 *  \param length ���ݳ���
 */
void NotifyReadFlash(uint8_t status,uint8_t *_data,uint16_t length)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  д�û�FLASH״̬����
 *  \param status 0ʧ�ܣ�1�ɹ�
 */
void NotifyWriteFlash(uint8_t status)
{
	//TODO: ����û�����
}

/*! 
 *  \brief  ��ȡRTCʱ�䣬ע�ⷵ�ص���BCD��
 *  \param year �꣨BCD��
 *  \param month �£�BCD��
 *  \param week ���ڣ�BCD��
 *  \param day �գ�BCD��
 *  \param hour ʱ��BCD��
 *  \param minute �֣�BCD��
 *  \param second �루BCD��
 */
void NotifyReadRTC(uint8_t year,uint8_t month,uint8_t week,uint8_t day,uint8_t hour,uint8_t minute,uint8_t second)
{
}

