
#include "SysConfig.h"
volatile uint32_t ChipUniqueID[3];




void showdbg32hex(u32 *bf,u8 len)
{
	u8 cnt;
	for(cnt=0;cnt<len;cnt++)
	{
		printf("%x,",bf[cnt]);
	}
	printf("\r\n");
}
void showdbg32dec(u32 *bf,u8 len)
{
	u8 cnt;
	for(cnt=0;cnt<len;cnt++)
	{
		printf("%d,",bf[cnt]);
	}
	printf("\r\n");
}

void showdbg8hex(u8 *bf,u8 len)
{
	u8 cnt;
	for(cnt=0;cnt<len;cnt++)
	{
		printf("%02x,",bf[cnt]);
	}
	printf("\r\n");
}
void showdbg16hex(u16 *bf,u8 len)
{
	u8 cnt;
	for(cnt=0;cnt<len;cnt++)
	{
		printf("%x,",bf[cnt]);
	}
	printf("\r\n");
}
void showdbg8dec(u8 *bf,u8 len)
{
	u8 cnt;
	for(cnt=0;cnt<len;cnt++)
	{
		printf("%d,",bf[cnt]);
	}
	printf("\r\n");
}

void GetSysSn(void){
	ChipUniqueID[2] = *(__IO u32*)(0X1FFFF7E8);  
	ChipUniqueID[1] = *(__IO u32 *)(0X1FFFF7EC); 
	ChipUniqueID[0] = *(__IO u32 *)(0X1FFFF7F0); 
}



/***********************************************
Function: д��ϵͳ���ò���
************************************************/
void SysParmWrite(void)
{	
	uint8_t i;

	uint16_t wtbf[FLASH_DAT_LEN];
	wtbf[0]					= (uint16_t)Config.tagflg;							  
	wtbf[1]      			= (uint16_t)Config.hwver;				
	wtbf[2]					= (uint16_t)Config.swver;				
	wtbf[3]					= (uint16_t)Config.DeviceType;		
	
	wtbf[4]   				= (uint16_t)(Config.deviceid>>16);
	wtbf[5]   				= (uint16_t)(Config.deviceid>>0);

	wtbf[8]   				= (uint16_t)(Config.GateWith>>16);
	wtbf[9]   				= (uint16_t)(Config.GateWith>>0);
	
	wtbf[12]   				= (uint16_t)(Config.GateGas>>16);
	wtbf[13]   				= (uint16_t)(Config.GateGas>>0);
		
	wtbf[16]   				= (uint16_t)(Config.PlusWith>>16);
	wtbf[17]   				= (uint16_t)(Config.PlusWith>>0);
	
	wtbf[18]					= (uint16_t)(Config.PlusGas>>8);		
	wtbf[19]					= (uint16_t)(Config.PlusGas>>0);		
	
	wtbf[20] 				= (uint16_t)(Config.PlusGas>>16);
	wtbf[21] 				= (uint16_t)(Config.PlusGas>>0);

	wtbf[24] 				= (uint16_t)(Config.PromptTim>>16);
	wtbf[25] 				= (uint16_t)(Config.PromptTim>>0);
	
	wtbf[28]    			= (uint16_t)Config.NetMod;					
	
	wtbf[29]					= (uint16_t)Config.Rmoteip[0];				
	wtbf[30]					= (uint16_t)Config.Rmoteip[1];				
	wtbf[31]					= (uint16_t)Config.Rmoteip[2];				
	wtbf[32]					= (uint16_t)Config.Rmoteip[3];				
		
	wtbf[33]					= (uint16_t)Config.Localip[0];				
	wtbf[34]					= (uint16_t)Config.Localip[1];				
	wtbf[35]					= (uint16_t)Config.Localip[2];				
	wtbf[36]					= (uint16_t)Config.Localip[3];				
			
	wtbf[37]					= (uint16_t)Config.GateW[0];				
	wtbf[38]					= (uint16_t)Config.GateW[1];				
	wtbf[39]					= (uint16_t)Config.GateW[2];				
	wtbf[40]					= (uint16_t)Config.GateW[3];				
			
	wtbf[41]					= (uint16_t)Config.Mass[0];				
	wtbf[42]					= (uint16_t)Config.Mass[1];				
	wtbf[43]					= (uint16_t)Config.Mass[2];				
	wtbf[44]					= (uint16_t)Config.Mass[3];				
					
	wtbf[45]					= (uint16_t)(Config.RemotePort>>0);				
	wtbf[47]					= (uint16_t)(Config.runmod>>0);		
	wtbf[48]					= (uint16_t)(Config.ttlLe>>0);		
	wtbf[50]					= (uint16_t)(Config.dhcpsw>>0);		
		
	wtbf[51]					= (uint16_t)Config.Mac[0];
	wtbf[52]					= (uint16_t)Config.Mac[1];
	wtbf[53]					= (uint16_t)Config.Mac[2];
	wtbf[54]					= (uint16_t)Config.Mac[3];
	wtbf[55]					= (uint16_t)Config.Mac[4];
	wtbf[56]					= (uint16_t)Config.Mac[5];
	wtbf[57]					= (uint16_t)Config.GateSta;

	wtbf[58]					= (uint16_t)(Config.DecMon[0]>>0);
	wtbf[60]					= (uint16_t)(Config.DecMon[1]>>0);
	wtbf[62]					= (uint16_t)(Config.DecMon[2]>>0);
	wtbf[64]					= (uint16_t)(Config.DecMon[3]>>0);
	wtbf[66]					= (uint16_t)(Config.DecMon[4]>>0);
	
	wtbf[68]				 	= (uint16_t)Config.ICKey[0];	
	wtbf[69]				 	= (uint16_t)Config.ICKey[1];	
	wtbf[70]				 	= (uint16_t)Config.ICKey[2];	
	wtbf[71]				 	= (uint16_t)Config.ICKey[3];	
	wtbf[72]				 	= (uint16_t)Config.ICKey[4];	
	wtbf[73]				 	= (uint16_t)Config.ICKey[5];	
	
	for(i=0;i<MAX_APNAME_LEN;i++){															//ap���ƺ�����
	
		wtbf[82+i] 								= (uint16_t)Config.APName[i];											//����
		wtbf[83+MAX_APNAME_LEN+i] 	= (uint16_t)Config.APPassword[i];;	//����
	}
	
	STMFLASH_Write(STM32_FLASH_BASE,wtbf,FLASH_DAT_LEN);	
	
//	if(ee_WriteBytes(wtbf, FLASH_STORE_BASE, FLASH_DAT_LEN)==0)
//	{
//		printf("ϵͳ����д��ʧ��\r\n");
//	}
	
	delay_ms(10);																							
}

/***********************************************
Function: ϵͳ���ò�������
************************************************/
void SysParmExplain(void)
{
	
	uint16_t expbf[FLASH_DAT_LEN];
	uint8_t i;
	STMFLASH_Read(STM32_FLASH_BASE,expbf,FLASH_DAT_LEN);//??????
	
	Config.tagflg     		= expbf[0];							  
	Config.hwver      		= (uint8_t)expbf[1];					
	Config.swver      		= (uint8_t)expbf[2];					
	Config.DeviceType 		=	(uint8_t)expbf[3];					
    Config.deviceid   		= ((uint32_t)expbf[4]<<16)+((uint32_t)expbf[5]<<0);													
    Config.GateWith   		= ((uint32_t)expbf[8]<<16)+((uint32_t)expbf[9]<<0);												
	Config.GateGas   		= ((uint32_t)expbf[12]<<16)+((uint32_t)expbf[13]<<0);
	Config.PlusWith   		= ((uint32_t)expbf[16]<<16)+((uint32_t)expbf[17]<<0);
	Config.PlusGas   		= ((uint32_t)expbf[20]<<16)+((uint32_t)expbf[21]<<0);
	Config.PromptTim   		= ((uint32_t)expbf[24]<<16)+((uint32_t)expbf[25]<<0);
	Config.NetMod     		=  expbf[28];					
	
	Config.Rmoteip[0] 		= (uint8_t)expbf[29];									
	Config.Rmoteip[1] 		= (uint8_t)expbf[30];									
	Config.Rmoteip[2] 		= (uint8_t)expbf[31];									
	Config.Rmoteip[3] 		= (uint8_t)expbf[32];	
	
	Config.Localip[0] 		= (uint8_t)expbf[33];									
	Config.Localip[1] 		= (uint8_t)expbf[34];									
	Config.Localip[2]		 	= (uint8_t)expbf[35];									
	Config.Localip[3]		 	= (uint8_t)expbf[36];
	
	Config.GateW[0] 			= (uint8_t)expbf[37];									
	Config.GateW[1] 			= (uint8_t)expbf[38];									
	Config.GateW[2] 			= (uint8_t)expbf[39];									
	Config.GateW[3] 			= (uint8_t)expbf[40];			
	
	Config.Mass[0] 				= (uint8_t)expbf[41];									
	Config.Mass[1] 				= (uint8_t)expbf[42];									
	Config.Mass[2] 				= (uint8_t)expbf[43];									
	Config.Mass[3] 				= (uint8_t)expbf[44];		
	
	Config.RemotePort 					= ((uint16_t)expbf[45]<<0);		
	Config.runmod 				= (uint8_t)expbf[47];
	Config.ttlLe 					= (uint8_t)expbf[48];
	Config.dhcpsw 				= (uint8_t)expbf[50];
	
	
	Config.Mac[0] 				= (uint8_t)(expbf[51]);
	Config.Mac[1] 				= (uint8_t)(expbf[52]);
	Config.Mac[2] 				= (uint8_t)(expbf[53]);
	Config.Mac[3] 				= (uint8_t)(expbf[54]);
	Config.Mac[4] 				= (uint8_t)(expbf[55]);
	Config.Mac[5] 				= (uint8_t)(expbf[56]);
	Config.GateSta 					= (uint8_t)(expbf[57]);	

	Config.DecMon[0]			= ((uint16_t)expbf[58]<<0);	
	Config.DecMon[1] 			= ((uint16_t)expbf[60]<<0);	
	Config.DecMon[2] 			= ((uint16_t)expbf[62]<<0);	
	Config.DecMon[3] 			= ((uint16_t)expbf[64]<<0);	
	Config.DecMon[4] 			= ((uint16_t)expbf[66]<<0);	
	
	Config.ICKey[0] 			= (uint8_t)(expbf[68]);	
	Config.ICKey[1] 			= (uint8_t)(expbf[69]);	
	Config.ICKey[2] 			= (uint8_t)(expbf[70]);	
	Config.ICKey[3] 			= (uint8_t)(expbf[71]);	
	Config.ICKey[4] 			= (uint8_t)(expbf[72]);	
	Config.ICKey[5] 			= (uint8_t)(expbf[73]);	
	
	for(i=0;i<MAX_APNAME_LEN;i++){															//ap���ƺ�����
	
		Config.APName[i]= (uint8_t)expbf[82+i];											//����
		Config.APPassword[i] = (uint8_t)expbf[83+MAX_APNAME_LEN+i];	//����
	}
	COIN_SIG = !Config.ttlLe;
	GATE_CTR_SIG = !Config.GateSta; 
	g_tFlg.gDecMon 	=  Config.DecMon[0];


	switch(Config.NetMod){
		case NET_RJ45:
		memcpy(gNetCtr.LanRmoteip,Config.Rmoteip,4);
		memcpy(gNetCtr.LanLocalip,Config.Localip,4);
		memcpy(gNetCtr.LanMass,Config.Mass,4);
		memcpy(gNetCtr.LanGateW,Config.GateW,4);
		gNetCtr.LanRemotePort = Config.RemotePort;
		
		memcpy(gNetCtr.WiFiRmoteip,Config.Rmoteip,4);
		memcpy(gNetCtr.WiFiLocalip,Config.Localip,4);
		memcpy(gNetCtr.WiFiMass,Config.Mass,4);
		memcpy(gNetCtr.WiFiGateW,Config.GateW,4);
		gNetCtr.WiFiRemotePort = Config.RemotePort+1;
		break;
		case NET_WIFI:
			memcpy(gNetCtr.LanRmoteip,Config.Rmoteip,4);
			memcpy(gNetCtr.LanLocalip,Config.Localip,4);
			memcpy(gNetCtr.LanMass,Config.Mass,4);
			memcpy(gNetCtr.LanGateW,Config.GateW,4);
			gNetCtr.LanRemotePort = Config.RemotePort+1;
			
			memcpy(gNetCtr.WiFiRmoteip,Config.Rmoteip,4);
			memcpy(gNetCtr.WiFiLocalip,Config.Localip,4);
			memcpy(gNetCtr.WiFiMass,Config.Mass,4);
			memcpy(gNetCtr.WiFiGateW,Config.GateW,4);
			gNetCtr.WiFiRemotePort = Config.RemotePort;
			break;
		default:
			break;
	}
	
//	SysParmPrint();
}


void SysParmPrint(void)
{
 	printf("��ȡϵͳ����---------------------------------:\r\n");	
	printf("ϵͳ��־    		��%d\r\n",Config.tagflg);
	printf("Ӳ���汾��  		��%d\r\n",Config.hwver);
	printf("����汾��  		��%d\r\n",Config.swver);
	printf("�豸����    		��%d\r\n",Config.DeviceType);
	printf("�豸ID      		��%d\r\n",Config.deviceid);
	printf("��¼����    		��%d\r\n",Config.LoginKey);
	printf("Ͷ��������    ��%d ms\r\n",Config.PlusWith);
	printf("Ͷ�Ҽ��ʱ��		��%d ms\r\n",Config.PlusGas);
	printf("���ų���ʱ��    ��%d ms\r\n",Config.GateWith);
	printf("���ż��ʱ��		��%d ms\r\n",Config.GateGas);
	printf("�����ظ�ʱ��		��%d ms\r\n",Config.PromptTim);

	printf("������ʽ	��");
	switch(Config.NetMod)
	{
		case NET_RJ45:
			printf("����\r\n");
			break;
		case NET_WIFI:
			printf("wi-fi\r\n");
			break;
		case NET_GPRS:
			printf("GPRS\r\n");
			break;
		case NET_2_4G:
			printf("2.4G\r\n");
			break;
		default:
			printf("δ����\r\n");
			break;
	}
	printf("�����ź�			��");
	switch(Config.GateSta)
	{
		case GATE_NO:
			printf("����\r\n");
			break;
		case GATE_NC:
			printf("����\r\n");
			break;
		default:
			printf("δ����\r\n");
			break;
	}
	printf("Ͷ�ҿ�״̬			");
	switch(Config.ttlLe)
	{
		case TTL_NC:
			printf("����\r\n");
			break;
		case TTL_NO:
			printf("����\r\n");
			break;
		default:
			printf("δ����\r\n");
			break;
	}
	printf("dhcp����     	    ��");
	switch(Config.dhcpsw)
	{
		case DHCP_ON:
			printf("<��>\r\n");
		  break;
		case DHCP_OFF:
			printf("<��>\r\n");
		  break;			
		default:
			printf("δ����\r\n");
			break;
	}
	printf("����ģʽ			��");
	switch(Config.runmod)
	{
		case RunMod_KEYINPUT:
			printf("��������ģʽ  \r\n"); 
			break;
		case RunMod_NORMAL_FIX:
			printf("�̶�����ģʽ \r\n"); 
			break;
		case RunMod_NORMAL_DANGWEI:
			printf("��λ����ģʽ \r\n"); 
			break;
		case RunMod_CHECK:
			printf("��ѯ��ģʽ \r\n"); 
			break;
		case RunMod_SAVER_COIN:
			printf("���ģʽ  \r\n"); 
			break;
		case RunMod_SALE_COIN:
			printf("�۱�ģʽ  \r\n"); 
			break;
		case RunMod_SALE_SAVER_COIN:
			printf("��ȡһ��ģʽ \r\n"); 
			break;
		case RunMod_GATE_CTRL:
			printf("��բ����ģʽ \r\n"); 
			break;
		default:
			printf("δ����ģʽ\r\n"); 
			break;
	}
	
	printf("������ip��ַ   		��%d.%d.%d.%d\r\n",Config.Rmoteip[0],Config.Rmoteip[1],Config.Rmoteip[2],Config.Rmoteip[3]);
	printf("����ip��ַ     		��%d.%d.%d.%d\r\n",Config.Localip[0],Config.Localip[1],Config.Localip[2],Config.Localip[3]);
	printf("Ĭ������       		��%d.%d.%d.%d\r\n",Config.GateW[0],Config.GateW[1],Config.GateW[2],Config.GateW[3]);
	printf("��������       		��%d.%d.%d.%d\r\n",Config.Mass[0],Config.Mass[1],Config.Mass[2],Config.Mass[3]);
	printf("�˿ں�         		��%d\r\n",Config.RemotePort);
	printf("���Ѷ��ֵ     		��%d,%d,%d,%d,%d\r\n",Config.DecMon[0],Config.DecMon[1],Config.DecMon[2],Config.DecMon[3],Config.DecMon[4]);	
	printf("IC����֤����   		��0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\r\n",Config.ICKey[0],Config.ICKey[1],Config.ICKey[2],Config.ICKey[3],Config.ICKey[4],Config.ICKey[5]);	
	
	if(Config.NetMod == NET_WIFI)//wifiģʽ���д˲���
	{
	printf("ap����				��%s\r\n",Config.APName);
	printf("ap����				��%s\r\n",Config.APPassword);
	}
		
	printf("����mac��ַΪ		��%d:%d:%d:%d:%d:%d\r\n",Config.Mac[0],Config.Mac[1],Config.Mac[2],Config.Mac[3],Config.Mac[4],Config.Mac[5]);
}



/***********************************************
Function: ����Ĭ��ϵͳ����
************************************************/
void SysParmRestorDefault(void)
{
	uint8_t tmpn[MAX_APNAME_LEN+2]="abcabc";
	uint8_t tmpp[MAX_APPASSWORD_LEN+2]="abc123456";
	uint8_t i;

#if MAIN_DBG >0	
	printf("Restore factory defaults\r\n");
#endif
	Config.tagflg = DEFAULT_TAG_FLG;
	
  	Config.deviceid = DEFAULT_ID;													
  	Config.LoginKey = DEFAULT_KEY;														
	Config.PlusWith = DEFAULT_COIN_TIM;					
	Config.PlusGas = DEFAULT_COIN_GAS;
	Config.GateWith = DEFAULT_GATE_TIM;					
	Config.GateGas = DEFAULT_GATE_GAS;					
	Config.hwver = DEFAULT_Hwver;					
	Config.swver = DEFAULT_Swver;	
	
	Config.DecMon[0] = DEFAULT_DecMon_10;		
	Config.DecMon[1] = DEFAULT_DecMon_20;		
	Config.DecMon[2] = DEFAULT_DecMon_30;		
	Config.DecMon[3] = DEFAULT_DecMon_40;		
	Config.DecMon[4] = DEFAULT_DecMon_50;	
	
	Config.DeviceType = ZN;					
	//Config.NetMod = NET_WIFI;					
	Config.NetMod = NET_RJ45;					
	Config.PromptTim = DEFAULT_PromptTim;		
	if(Config.NetMod == NET_GPRS)
	{
		Config.Rmoteip[0] = 120;
		Config.Rmoteip[1] = 25;
		Config.Rmoteip[2] = 77;
		Config.Rmoteip[3] = 214;		
	}
	else
	{
		Config.Rmoteip[0] = 192;
		Config.Rmoteip[1] = 168;
		Config.Rmoteip[2] = 1;
		Config.Rmoteip[3] = 251;
		Config.Localip[0] = 192;
		Config.Localip[1] = 168;
		Config.Localip[2] = 1;
		Config.Localip[3] = 254;
		Config.GateW[0] = 192;
		Config.GateW[1] = 168;
		Config.GateW[2] = 1;
		Config.GateW[3] = 1;
		Config.Mass[0] = 255;
		Config.Mass[1] = 255;
		Config.Mass[2] = 255;
		Config.Mass[3] = 0;
	}
	Config.Mac[0] = (uint8_t)(ChipUniqueID[0]>>0);
	Config.Mac[1] = (uint8_t)(ChipUniqueID[0]>>8);
	Config.Mac[2] = (uint8_t)(ChipUniqueID[0]>>16);
	Config.Mac[3] = (uint8_t)(ChipUniqueID[0]>>24);
	Config.Mac[4] = (uint8_t)(ChipUniqueID[1]>>0);
	Config.Mac[5] = (uint8_t)(ChipUniqueID[1]>>8);

	Config.RemotePort = 60000;
	Config.dhcpsw = DEFAULT_DHCP_STA;
	
	for(i=0;i<MAX_APNAME_LEN;i++)//ap���ƺ�����
	{
		Config.APName[i] = tmpn[i];//����
		Config.APPassword[i] = tmpp[i];//����
	}
	
	
	//Config.runmod = RunMod_SAVER;
	Config.runmod = RunMod_NORMAL_DANGWEI;
	Config.ttlLe = TTL_NO;
	Config.GateSta = GATE_NO;
	
	Config.ICKey[0] = 0xff;
	Config.ICKey[1] = 0xff;
	Config.ICKey[2] = 0xff;
	Config.ICKey[3] = 0xff;
	Config.ICKey[4] = 0xff;
	Config.ICKey[5] = 0xff;
	
}



void SysParmSet(void)
{
	SysParmExplain();		
	if(DEFAULT_TAG_FLG != Config.tagflg)//mcuδ��ʼ��������Ĭ��,����dec inc����ͬʱ����
	{		
		printf("���豸д��ϵͳĬ�ϲ���...\r\n");		
		SysParmRestorDefault();
		SysParmWrite();

		SysParmExplain();		
	}
}

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
  /* ���� 5 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ʹ�� PVD �ж� */
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = macESP8266_USART_IRQ;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);


  /* ���� 4 */
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);



  /* ���� 3 */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);


  /* ���� 2 */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);

  /* ���� 1 */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



//ϵͳ�����λ
void SysReset(void)
{
	*((uint32_t*)0xe000ed0c)=0x05fa0004;
}
void SysClkSet(void)
{
	 RCC_DeInit(); 				/*������RCC�Ĵ�������Ϊȱʡֵ */ 
   RCC_HSICmd(ENABLE); 
   while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)== RESET);//�ȴ�HSI���� 
   RCC_HCLKConfig(RCC_SYSCLK_Div1);   /*����AHBʱ�ӣ�HCLK�� RCC_SYSCLK_Div1����AHBʱ�� = ϵͳʱ*/  
   RCC_PCLK2Config(RCC_HCLK_Div1);   /* ���ø���AHBʱ�ӣ�PCLK2)RCC_HCLK_Div1����APB2ʱ�� = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2); /*���õ���AHBʱ�ӣ�PCLK1��RCC_HCLK_Div2����APB1ʱ�� = HCLK / 2*/      
   FLASH_SetLatency(FLASH_Latency_2);   /*����FLASH�洢����ʱʱ��������FLASH_Latency_2  2��ʱ����*/   
   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  /*ѡ��FLASHԤȡָ�����ģ,Ԥȡָ����ʹ��*/ 
   RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);/*����PLLʱ��Դ����Ƶϵ����Ƶ��Ϊ8/2*16=64Mhz*/    
   RCC_PLLCmd(ENABLE); 	 /*ʹ��PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*���ָ����RCC��־λ(PLL׼���ñ�־)�������*/    
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*����ϵͳʱ�ӣ�SYSCLK�� */  
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08��PLL��Ϊϵͳʱ�� */	    
}

void SysInit(void)
{
	SysClkSet();
	systick_init(64);										/*��ʼ��Systick����ʱ��*/
	delay_ms(500);
	NVIC_Configuration();
 	TIM3_Int_Init(100,639);							//100Khz����Ƶ�ʣ�������1000Ϊ10ms
	UART4_Config();
	SysParmSet();
	SysParmPrint();
	TFT_LCD_Init();
	PrinterInit();
	InitRc522();
	Wt588dInit(); 
	GateIoInit();
	GetSysSn();
	PVD_Config();
	W5500Init();
	ESP8266_Init();	
	switch(Config.runmod)
	{
		case RunMod_KEYINPUT:
			SysVar.CmdID = DEC_MON_CMD;
			break;
		case RunMod_NORMAL_FIX:
			SysVar.CmdID = DEC_MON_CMD;
			break;
		case RunMod_NORMAL_DANGWEI:
			SysVar.CmdID = DEC_MON_CMD;
			break;
		case RunMod_CHECK:
			SysVar.CmdID = CHECK_MON_CMD;
			break;
		case RunMod_SAVER_COIN:
			  SysVar.CmdID = SAVE_COIN_DAI;
				EXTIX_Init();
			break;
		case RunMod_SALE_COIN:
			  SysVar.CmdID = DEC_MON_CMD;
			break;
		case RunMod_SALE_SAVER_COIN:
				EXTIX_Init();
			  SysVar.CmdID = SAVE_COIN_DAI;
			break;
		case RunMod_GATE_CTRL:
			  SysVar.CmdID = DEC_MON_CMD;
			break;
		default:
			break;
	}
	SysVar.ucTcpClosedFlag = 1;
}




