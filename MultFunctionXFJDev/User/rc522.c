
#define RC522_C
#include "rc522.h"
//#include "WT588D.H"
//#include "sys.h"
//#include "spi.h"
#include "string.h" 
#include <stdint.h>
//#include "types.h"
#include "utility.h"
//#include "FramePkg.h"
#include "hmi_driver.h"
#include "SysConfig.h"
#include "tcp_demo.h"


__Rc522_ctr RC522Ctr;	
//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI3_ReadWriteByte(u8 TxData){		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI3, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI3); //����ͨ��SPIx������յ�����					    
}

void delay_ns(u32 ns)
{
  u32 i;
  for(i=0;i<ns;i++)
  {
    __nop();
    __nop();
    __nop();
  }
}


void Spi3Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	/* ʹ��SPIʱ�� */
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ����SPI�� CS���ţ���ͨIO���� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* ����SPI�� RST���ţ���ͨIO���� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* ����SPI�� SCK����*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* SPI ģʽ���� */
  // FLASHоƬ ֧��SPIģʽ0��ģʽ3���ݴ�����CPOL CPHA
	 SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//???
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//???
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//8?????   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//????,???SPI???SCK????
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//????,??????
	 SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;													//?????
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//??????   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;//????   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//???????????   SPI_InitStructure.SPI_CRCPolynomial = 7;//?????
	 SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;									//?????MSB???
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;	//??????????:????????16
  SPI_Init(SPI3, &SPI_InitStructure);




//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI??????????
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;												//SPI??
//  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;										//????8????
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;													//?????
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;												//??????1????
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;														//NSS???????
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	//??????????:????????16
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;									//?????MSB???
//	SPI_InitStructure.SPI_CRCPolynomial = 7;														//CRC???????
/* ʹ�� SPI  */
  SPI_Cmd(SPI3 , ENABLE);

}


//void Spi2Init(void)
//{
//		GPIO_InitTypeDef GPIO_InitStructure;
//	  SPI_InitTypeDef  SPI_InitStructure;
//	
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 
//		RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2,  ENABLE );//SPI2ʱ��ʹ��	
//	 
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 					//PB13/14/15����������� 
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);										//��ʼ��GPIOB
//		GPIO_SetBits(GPIOB,GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);  //PB13/14/15����
//	
//	
//		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//SPI����Ϊ˫��˫��ȫ˫��
//		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;												//SPI����
//	  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 									//���ͽ���8λ֡�ṹ
//		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;													//ʱ�����յ�
//		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;												//���ݲ����ڵ�1��ʱ����
//		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;														//NSS�ź����������
//		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
//		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;									//���ݴ����MSBλ��ʼ
//		SPI_InitStructure.SPI_CRCPolynomial = 7;														//CRCֵ����Ķ���ʽ
//		SPI_Init(SPI2, &SPI_InitStructure); 																//����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
//		SPI_Cmd(SPI2, ENABLE);																							//ʹ��SPI����



//  /*����RESET����*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;					       /*ѡ��Ҫ���Ƶ�GPIO����*/		 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		     /*��������ģʽΪͨ���������*/	
//  GPIO_Init(GPIOB, &GPIO_InitStructure);		 /*���ÿ⺯������ʼ��GPIO*/ 
//  GPIO_SetBits(GPIOB, GPIO_Pin_12);		

//  /*����CS����*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					       /*ѡ��Ҫ���Ƶ�GPIO����*/		 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     /*������������Ϊ50MHz */		
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     /*��������ģʽΪͨ���������*/	
//  GPIO_Init(GPIOB, &GPIO_InitStructure);		 /*���ÿ⺯������ʼ��GPIO*/ 
//  GPIO_SetBits(GPIOB, GPIO_Pin_11);		

//}

void InitRc522(void)
{
	Spi3Init();
	//gpio_for_Rc522_config();
	
  PcdReset();
  PcdAntennaOff();
	delay_ms(10);
  PcdAntennaOn();
  M500PcdConfigISOType( 'A' );
}
void InitRc522Per(void){
  PcdReset();
  PcdAntennaOff();
		delay_ms(10);
  PcdAntennaOn();
  M500PcdConfigISOType( 'A' );

}
void Reset_RC522(void)
{
  PcdReset();
  PcdAntennaOff();
		delay_ms(10);
  PcdAntennaOn();
}                         
/////////////////////////////////////////////////////////////////////
//��    �ܣ�Ѱ��
//����˵��: req_code[IN]:Ѱ����ʽ
//                0x52 = Ѱ��Ӧ�������з���14443A��׼�Ŀ�
//                0x26 = Ѱδ��������״̬�Ŀ�
//          pTagType[OUT]����Ƭ���ʹ���
//                0x4400 = Mifare_UltraLight
//                0x0400 = Mifare_One(S50)
//                0x0200 = Mifare_One(S70)
//                0x0800 = Mifare_Pro(X)
//                0x4403 = Mifare_DESFire
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdRequest(u8   req_code,u8 *pTagType)
{
	char   status;  
	u8   unLen;
	u8   ucComMF522Buf[MAXRLEN]; 

	ClearBitMask(Status2Reg,0x08);
	WriteRawRC(BitFramingReg,0x07);
	SetBitMask(TxControlReg,0x03);
 
	ucComMF522Buf[0] = req_code;

	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);

	if ((status == MI_OK) && (unLen == 0x10))
	{    
		*pTagType     = ucComMF522Buf[0];
		*(pTagType+1) = ucComMF522Buf[1];
	}
	else{   
		status = MI_ERR;   
	}
	return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�����ײ
//����˵��: pSnr[OUT]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////  
char PcdAnticoll(u8 *pSnr){
    char   status;
    u8   i,snr_check=0;
    u8   unLen;
    u8   ucComMF522Buf[MAXRLEN]; 
  
    ClearBitMask(Status2Reg,0x08);
    WriteRawRC(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
 
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;
	
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);
    if (status == MI_OK){
    	 for (i=0; i<4; i++){   
             *(pSnr+i)  = ucComMF522Buf[i];
             snr_check ^= ucComMF522Buf[i];
       }
       if (snr_check != ucComMF522Buf[i]){
					status = MI_ERR;    
			 }
    } 
    SetBitMask(CollReg,0x80);
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�ѡ����Ƭ
//����˵��: pSnr[IN]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdSelect(u8 *pSnr)
{
    char   status;
    u8   i;
    u8   unLen;
    u8   ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for (i=0; i<4; i++)
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
  
    ClearBitMask(Status2Reg,0x08);

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    
    if ((status == MI_OK) && (unLen == 0x18))
    {   status = MI_OK;  }
    else
    {   status = MI_ERR;    }

    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���֤��Ƭ����
//����˵��: auth_mode[IN]: ������֤ģʽ
//                 0x60 = ��֤A��Կ
//                 0x61 = ��֤B��Կ 
//          addr[IN]�����ַ
//          pKey[IN]������
//          pSnr[IN]����Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////               
char PcdAuthState(u8   auth_mode,u8   addr,u8 *pKey,u8 *pSnr)
{
    char   status;
    u8   unLen;
    u8   ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = auth_mode;
    ucComMF522Buf[1] = addr;
//    for (i=0; i<6; i++)
//    {    ucComMF522Buf[i+2] = *(pKey+i);   }
//    for (i=0; i<6; i++)
//    {    ucComMF522Buf[i+8] = *(pSnr+i);   }
    memcpy(&ucComMF522Buf[2], pKey, 6); 
    memcpy(&ucComMF522Buf[8], pSnr, 4); 
    
    status = PcdComMF522(PCD_AUTHENT,ucComMF522Buf,12,ucComMF522Buf,&unLen);
    if ((status != MI_OK) || (!(ReadRawRC(Status2Reg) & 0x08)))
    {   status = MI_ERR;   }
    
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���ȡM1��һ������
//����˵��: addr[IN]�����ַ
//          p [OUT]�����������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
///////////////////////////////////////////////////////////////////// 
char PcdRead(u8   addr,u8 *p )
{
    char   status;
    u8   unLen;
    u8   i,ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_READ;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
   
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    if ((status == MI_OK) && (unLen == 0x90))
 //   {   memcpy(p , ucComMF522Buf, 16);   }
    {
        for (i=0; i<16; i++)
        {    *(p +i) = ucComMF522Buf[i];   }
    }
    else
    {   status = MI_ERR;   }
    
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�д���ݵ�M1��һ��
//����˵��: addr[IN]�����ַ
//          p [IN]��д������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////                  
char PcdWrite(u8   addr,u8 *p )
{
    char   status;
    u8   unLen;
    u8   i,ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = PICC_WRITE;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
        
    if (status == MI_OK)
    {
        //memcpy(ucComMF522Buf, p , 16);
        for (i=0; i<16; i++)
        {    
        	ucComMF522Buf[i] = *(p +i);   
        }
        CalulateCRC(ucComMF522Buf,16,&ucComMF522Buf[16]);

        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,18,ucComMF522Buf,&unLen);
        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {   status = MI_ERR;   }
    }
    
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ����Ƭ��������״̬
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdHalt(void)
{
    u8   status;
    u8   unLen;
    u8   ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_HALT;
    ucComMF522Buf[1] = 0;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    return status;
}

/////////////////////////////////////////////////////////////////////
//��MF522����CRC16����
/////////////////////////////////////////////////////////////////////
void CalulateCRC(u8 *pIn ,u8   len,u8 *pOut )
{
    u8   i,n;
    ClearBitMask(DivIrqReg,0x04);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    for (i=0; i<len; i++)
    {   WriteRawRC(FIFODataReg, *(pIn +i));   }
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
    pOut [0] = ReadRawRC(CRCResultRegL);
    pOut [1] = ReadRawRC(CRCResultRegM);
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���λRC522
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdReset(void)
{
		SET_RC522RST;
		delay_ms(100);
		CLR_RC522RST;
		delay_ms(100);
		SET_RC522RST;
		delay_ms(100);
    WriteRawRC(CommandReg,PCD_RESETPHASE);
		WriteRawRC(CommandReg,PCD_RESETPHASE);
		delay_ms(10);
    
    WriteRawRC(ModeReg,0x3D);            //��Mifare��ͨѶ��CRC��ʼֵ0x6363
    WriteRawRC(TReloadRegL,30);           
    WriteRawRC(TReloadRegH,0);
    WriteRawRC(TModeReg,0x8D);
    WriteRawRC(TPrescalerReg,0x3E);
	
		WriteRawRC(TxAutoReg,0x40);//����Ҫ
   
    return MI_OK;
}
//////////////////////////////////////////////////////////////////////
//����RC632�Ĺ�����ʽ 
//////////////////////////////////////////////////////////////////////
char M500PcdConfigISOType(u8   type)
{
   if (type == 'A')                     //ISO14443_A
   { 
       ClearBitMask(Status2Reg,0x08);
       WriteRawRC(ModeReg,0x3D);//3F
       WriteRawRC(RxSelReg,0x86);//84
       WriteRawRC(RFCfgReg,0x7F);   //4F
   	   WriteRawRC(TReloadRegL,30);//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
	   WriteRawRC(TReloadRegH,0);
       WriteRawRC(TModeReg,0x8D);
	   WriteRawRC(TPrescalerReg,0x3E);
	   delay_ns(1000);
       PcdAntennaOn();
   }
   else{ return 1; }
   
   return MI_OK;
}
/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC632�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//��    �أ�������ֵ
/////////////////////////////////////////////////////////////////////
u8 ReadRawRC(u8   Address)
{
    u8   ucAddr;
    u8   ucResult=0;
	
		CLR_SPI_CS;
    ucAddr = ((Address<<1)&0x7E)|0x80;
	
		SPI3_ReadWriteByte(ucAddr);
		ucResult=SPI3_ReadWriteByte(0);
		SET_SPI_CS;
   return ucResult;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�дRC632�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//          value[IN]:д���ֵ
/////////////////////////////////////////////////////////////////////
void WriteRawRC(u8   Address, u8   value)
{  
    u8   ucAddr;
//	u8 tmp;

	CLR_SPI_CS;
  ucAddr = ((Address<<1)&0x7E);
	SPI3_ReadWriteByte(ucAddr);
	SPI3_ReadWriteByte(value);
	SET_SPI_CS;

//	tmp=ReadRawRC(Address);
//
//	if(value!=tmp)
//		printf("wrong\n");
}
/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
/////////////////////////////////////////////////////////////////////
void SetBitMask(u8   reg,u8   mask)  
{
    char   tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp | mask);  // set bit mask
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
/////////////////////////////////////////////////////////////////////
void ClearBitMask(u8   reg,u8   mask)  
{
    char   tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  // clear bit mask
} 

/////////////////////////////////////////////////////////////////////
//��    �ܣ�ͨ��RC522��ISO14443��ͨѶ
//����˵����Command[IN]:RC522������
//          pIn [IN]:ͨ��RC522���͵���Ƭ������
//          InLenByte[IN]:�������ݵ��ֽڳ���
//          pOut [OUT]:���յ��Ŀ�Ƭ��������
//          *pOutLenBit[OUT]:�������ݵ�λ����
/////////////////////////////////////////////////////////////////////
char PcdComMF522(u8   Command, u8 *pIn , u8 InLenByte,u8 *pOut, u8 *pOutLenBit){
    char   status = MI_ERR;
    u8   irqEn   = 0x00;
    u8   waitFor = 0x00;
    u8   lastBits;
    u8   n;
    u16   i;
    switch (Command){
			case PCD_AUTHENT:
				irqEn   = 0x12;
				waitFor = 0x10;
				break;
			case PCD_TRANSCEIVE:
				irqEn   = 0x77;
				waitFor = 0x30;
				break;
			default:
				break;
    }
    WriteRawRC(ComIEnReg,irqEn|0x80);
    ClearBitMask(ComIrqReg,0x80);	//�������ж�λ
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);	 	//��FIFO����
    
    for (i=0; i<InLenByte; i++){   
			WriteRawRC(FIFODataReg, pIn [i]);    
		}
    WriteRawRC(CommandReg, Command);	  
//   	 n = ReadRawRC(CommandReg);    
    if (Command == PCD_TRANSCEIVE){//��ʼ����   
			SetBitMask(BitFramingReg,0x80);  
		}	 
    i = 600;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
		//i = 2000;
    do{
        n = ReadRawRC(ComIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor));
    ClearBitMask(BitFramingReg,0x80);
    if (i!=0){    
			if(!(ReadRawRC(ErrorReg)&0x1B)){
				status = MI_OK;
				if (n & irqEn & 0x01){
					status = MI_NOTAGERR;   
				}
				if (Command == PCD_TRANSCEIVE){
					n = ReadRawRC(FIFOLevelReg);
					lastBits = ReadRawRC(ControlReg) & 0x07;
					if (lastBits){   
						*pOutLenBit = (n-1)*8 + lastBits;   
					}
					else{   
						*pOutLenBit = n*8;   
					}
					if (n == 0){   
						n = 1;   
					}
					if (n > MAXRLEN){
						n = MAXRLEN;   
					}
					for (i=0; i<n; i++){ 
						pOut [i] = ReadRawRC(FIFODataReg);    
					}
				}
			}
			else{   
				status = MI_ERR;   
			}    
    }
    SetBitMask(ControlReg,0x80);           // stop timer now
    WriteRawRC(CommandReg,PCD_IDLE); 
    return status;
}

/////////////////////////////////////////////////////////////////////
//��������  
//ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
/////////////////////////////////////////////////////////////////////
void PcdAntennaOn(void)
{
    u8   i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}


/////////////////////////////////////////////////////////////////////
//�ر�����
/////////////////////////////////////////////////////////////////////
void PcdAntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ��ۿ�ͳ�ֵ
//����˵��: dd_mode[IN]��������
//               0xC0 = �ۿ�
//               0xC1 = ��ֵ
//          addr[IN]��Ǯ����ַ
//          pValue[IN]��4�ֽ���(��)ֵ����λ��ǰ
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////                 
/*char PcdValue(u8 dd_mode,u8 addr,u8 *pValue)
{
    char status;
    u8  unLen;
    u8 ucComMF522Buf[MAXRLEN]; 
    //u8 i;
	
    ucComMF522Buf[0] = dd_mode;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
        
    if (status == MI_OK)
    {
        memcpy(ucComMF522Buf, pValue, 4);
        //for (i=0; i<16; i++)
        //{    ucComMF522Buf[i] = *(pValue+i);   }
        CalulateCRC(ucComMF522Buf,4,&ucComMF522Buf[4]);
        unLen = 0;
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,6,ucComMF522Buf,&unLen);
		if (status != MI_ERR)
        {    status = MI_OK;    }
    }
    
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = PICC_TRANSFER;
        ucComMF522Buf[1] = addr;
        CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]); 
   
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {   status = MI_ERR;   }
    }
    return status;
}*/

/////////////////////////////////////////////////////////////////////
//��    �ܣ�����Ǯ��
//����˵��: sourceaddr[IN]��Դ��ַ
//          goaladdr[IN]��Ŀ���ַ
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
/*char PcdBakValue(u8 sourceaddr, u8 goaladdr)
{
    char status;
    u8  unLen;
    u8 ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_RESTORE;
    ucComMF522Buf[1] = sourceaddr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
    
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = 0;
        ucComMF522Buf[1] = 0;
        ucComMF522Buf[2] = 0;
        ucComMF522Buf[3] = 0;
        CalulateCRC(ucComMF522Buf,4,&ucComMF522Buf[4]);
 
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,6,ucComMF522Buf,&unLen);
		if (status != MI_ERR)
        {    status = MI_OK;    }
    }
    
    if (status != MI_OK)
    {    return MI_ERR;   }
    
    ucComMF522Buf[0] = PICC_TRANSFER;
    ucComMF522Buf[1] = goaladdr;

    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }

    return status;
}*/

#define  DEC_CNT_MAX 	5			//?????
#define  IC_KEY_DATA_ADDR 	7
#define  IC_TYPE_DATA_ADDR 	6
/////////////////////////////////////////////////////////////////////
//?    ?:ic?????
//????: 				
//			



void RC522Task(void)
{		
	if(PcdRequest(PICC_REQIDL,&RC522Ctr.CT[0]) == MI_OK)
	{
		if( PcdAnticoll(&RC522Ctr.SN[0]) ==  MI_OK)
		{			
			if(PcdSelect(&RC522Ctr.SN[0]) == MI_OK)
			{				
				RC522Ctr.GetIcNum = 1;
				SysVar.icsn_old = SysVar.icsn_new;
				SysVar.icsn = ((uint32_t)RC522Ctr.SN[0]<<0)+((uint32_t)RC522Ctr.SN[1]<<8)+((uint32_t)RC522Ctr.SN[2]<<16)+((uint32_t)RC522Ctr.SN[3]<<24); 
				SysVar.icsn_new = SysVar.icsn;
				sprintf((char*)g_tFlg.pString, "%10u",SysVar.icsn); 
				replace_char((char*)g_tFlg.VipIDString, (char*)g_tFlg.pString, ' ','0');//����ַ�0
//				DBG_PRINTF("ic stringis:%s\r\n",g_tFlg.VipIDString);  
				SysVar.GetVipIdFlg = 1;								
				
				if(PcdAuthState(KEYA_CHK,IC_KEY_DATA_ADDR,&Config.ICKey[0],&RC522Ctr.SN[0])== MI_OK)
				{
					if(PcdRead(IC_TYPE_DATA_ADDR,&RC522Ctr.RFID[0]) == MI_OK)
					{	
							if(RC522Ctr.RFID[0] ==0x55 && RC522Ctr.RFID[1] == 0xaa)
							{
								if(++g_tFlg.gDecMonCnt >= DEC_CNT_MAX)
									g_tFlg.gDecMonCnt = 0;
									g_tFlg.gDecMon = Config.DecMon[g_tFlg.gDecMonCnt];
									PcdHalt();									
							}
							else if(lcd_parm.distype == DIS_IDE_MOD)   
							{
								PcdHalt();							
							}
							PcdHalt();								
					}
				}
			}
		}
	}
}
/*     1,2,3,4,5,6
 *     4-23��������
 *
 *
 */
uint8_t ickeya[6]={0,0,0,0,0,0};


void keyPlus(uint8_t *buf,uint8_t len)
{
		if(ickeya[5]++ ==0xff)
		{
			ickeya[5] = 0;
			if(ickeya[4]++ == 0xff)
			{
				ickeya[4] = 0;
				if(ickeya[3]++ == 0xff)
				{
					ickeya[3] = 0;
					if(ickeya[2]++ == 0xff)
					{
						ickeya[2] = 0;
						if(ickeya[1]++ == 0xff)
						{
							ickeya[1] = 0;
							if(ickeya[0]++ == 0xff)
							{
								ickeya[0] = 0;
								printf("�޷��ƽ⣡\r\n");
							}
						}
					}
				}
			}
		}
}
					
uint8_t addr=0;
void RC522Test(void)
{		
	if(PcdRequest(PICC_REQIDL,&RC522Ctr.CT[0]) == MI_OK){	
		if( PcdAnticoll(&RC522Ctr.SN[0]) ==  MI_OK){			
			if(PcdSelect(&RC522Ctr.SN[0]) == MI_OK){					
				RC522Ctr.GetIcNum = 1;
				
				if(PcdAuthState(KEYA_CHK,4,ickeya,&RC522Ctr.SN[0])== MI_OK){
					printf("keya is:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\r\n",ickeya[0],ickeya[1],ickeya[2],ickeya[3],ickeya[4],ickeya[5]);
					SoundCtr.Type = WT588D_LOGO_IN;
//					if(PcdRead(4,&RC522Ctr.RFID[0]) == MI_OK){	
//						printf("%d data:",addr);
//						showdbg8hex(RC522Ctr.RFID,16);     
//						}
				}
				else
				{
						//printf("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x err!",ickeya[0],ickeya[1],ickeya[2],ickeya[3],ickeya[4],ickeya[5]);
						keyPlus(ickeya,6);
				}
			}
		}
	}
}

