/*
**************************************************************************************************
* @file    		w5500_conf.c
* @author  		WIZnet Software Team 
* @version 		V1.0
* @date    		2015-02-14
* @brief  		����MCU����ֲW5500������Ҫ�޸ĵ��ļ�������W5500��MAC��IP��ַ
**************************************************************************************************
*/
#include <stdio.h> 
#include <string.h>

#include "w5500_conf.h"
//#include "bsp_i2c_ee.h"
#include "utility.h"
#include "w5500.h"
#include "dhcp.h"
#include "bsp_TiMbase.h"
#include "SysConfig.h"
//#include "esp07.h"


CONFIG_MSG  ConfigMsg;																	/*���ýṹ��*/


/*IP���÷���ѡ��������ѡ��*/
//uint8_t	ip_from=IP_FROM_DEFINE;				
uint8_t	ip_from=IP_FROM_DHCP;				

uint8_t   dhcp_ok   = 0;													   			/*dhcp�ɹ���ȡIP*/
uint32_t	ms        = 0;															  	/*�������*/
uint32_t	dhcp_time = 0;															  	/*DHCP���м���*/
vu8	    ntptimer  = 0;															  	/*NPT�����*/

/**
*@brief		����W5500��IP��ַ
*@param		��
*@return	��
*/
void set_w5500_ip(void)
{	
//   /*���ƶ����������Ϣ�����ýṹ��*/
	memcpy(ConfigMsg.mac, Config.Mac, 6);
	memcpy(ConfigMsg.lip,gNetCtr.LanLocalip,4);
	memcpy(ConfigMsg.sub,gNetCtr.LanMass,4);
	memcpy(ConfigMsg.gw,gNetCtr.LanGateW,4);
	memcpy(ConfigMsg.dns,Config.dns,4);
//	if(ip_from==IP_FROM_DEFINE)	
//		printf(" ʹ�ö����IP��Ϣ����W5500\r\n");
//#if 0		
//	
//	/*ʹ��EEPROM�洢��IP����*/	
//	if(ip_from==IP_FROM_EEPROM)
//	{
//    
//		/*��EEPROM�ж�ȡIP������Ϣ*/
//		read_config_from_eeprom();		
//		
//		/*�����ȡEEPROM��MAC��Ϣ,��������ã����ʹ��*/		
//		if( *(EEPROM_MSG.mac)==0x00&& *(EEPROM_MSG.mac+1)==0x08&&*(EEPROM_MSG.mac+2)==0xdc)		
//		{
//			printf(" IP from EEPROM\r\n");
//			/*����EEPROM������Ϣ�����õĽṹ�����*/
//			memcpy(ConfigMsg.lip,EEPROM_MSG.lip, 4);				
//			memcpy(ConfigMsg.sub,EEPROM_MSG.sub, 4);
//			memcpy(ConfigMsg.gw, EEPROM_MSG.gw, 4);
//		}
//		else
//		{
//			printf(" EEPROMδ����,ʹ�ö����IP��Ϣ����W5500,��д��EEPROM\r\n");
//			write_config_to_eeprom();	/*ʹ��Ĭ�ϵ�IP��Ϣ������ʼ��EEPROM������*/
//		}			
//	}
//#endif
//	/*ʹ��DHCP��ȡIP�����������DHCP�Ӻ���*/		
//	if(ip_from==IP_FROM_DHCP)								
//	{
//		/*����DHCP��ȡ��������Ϣ�����ýṹ��*/
//		if(dhcp_ok==1)
//		{
//			printf(" IP from DHCP\r\n");		 
//			memcpy(Config.Localip,DHCP_GET.lip, 4);
//			memcpy(Config.Mass,DHCP_GET.sub, 4);
//			memcpy(Config.GateW,DHCP_GET.gw, 4);
//			memcpy(Config.dns,DHCP_GET.dns,4);
//		}
//		else
//		{
//			printf(" DHCP�ӳ���δ����,���߲��ɹ�\r\n");
//			printf(" ʹ�ö����IP��Ϣ����W5500\r\n");
//		}
//	}
		
	/*����������Ϣ��������Ҫѡ��*/	
//	ConfigMsg.sw_ver[0]=FW_VER_HIGH;
//	ConfigMsg.sw_ver[1]=FW_VER_LOW;	

	/*��IP������Ϣд��W5500��Ӧ�Ĵ���*/	
	setSUBR(ConfigMsg.sub);
	setGAR(ConfigMsg.gw);
	setSIPR(ConfigMsg.lip);
  //memcpy(ConfigMsg.dns,dns_server,4);
	getSIPR (gNetCtr.LanLocalip);			
	printf(" W5500 IP��ַ   : %d.%d.%d.%d\r\n", gNetCtr.LanLocalip[0],gNetCtr.LanLocalip[1],gNetCtr.LanLocalip[2],gNetCtr.LanLocalip[3]);
	getSUBR(gNetCtr.LanMass);
	printf(" W5500 �������� : %d.%d.%d.%d\r\n", gNetCtr.LanMass[0],gNetCtr.LanMass[1],gNetCtr.LanMass[2],gNetCtr.LanMass[3]);
	getGAR(gNetCtr.LanGateW);
	printf(" W5500 ����     : %d.%d.%d.%d\r\n", gNetCtr.LanGateW[0],gNetCtr.LanGateW[1],gNetCtr.LanGateW[2],gNetCtr.LanGateW[3]);
}

/**
*@brief		����W5500��MAC��ַ
*@param		��
*@return	��
*/
void set_w5500_mac(void)
{
	//memcpy(ConfigMsg.mac, mac, 6);
	setSHAR(Config.Mac);	/**/
	memcpy(DHCP_GET.mac, Config.Mac, 6);
}

/**
*@brief		����W5500��GPIO�ӿ�
*@param		��
*@return	��
*/
void gpio_for_w5500_config(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(WIZ_SPIx_RESET_CLK|WIZ_SPIx_INT_CLK, ENABLE);
	
  /* Enable SPI1 and GPIO clocks */
  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO, 
       SPI_FLASH_SPI_MISO_GPIO, SPI_FLASH_SPI_DETECT_GPIO 
       and SPI_FLASH_SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(WIZ_SPIx_GPIO_CLK|WIZ_SPIx_SCS_CLK, ENABLE);

  /*!< SPI_FLASH_SPI Periph clock enable */
  WIZ_SPIx_CLK_CMD(WIZ_SPIx_CLK|RCC_APB2Periph_AFIO, ENABLE);
 
  
  /*!< Configure SPI_FLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = WIZ_SPIx_SCLK;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(WIZ_SPIx_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = WIZ_SPIx_MISO;
  GPIO_Init(WIZ_SPIx_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = WIZ_SPIx_MOSI;
  GPIO_Init(WIZ_SPIx_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
  GPIO_InitStructure.GPIO_Pin = WIZ_SPIx_SCS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(WIZ_SPIx_SCS_PORT, &GPIO_InitStructure);


  /* SPI1 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(WIZ_SPIx, &SPI_InitStructure);
  SPI_Cmd(WIZ_SPIx, ENABLE);
	
  /*����RESET����*/
  GPIO_InitStructure.GPIO_Pin = WIZ_RESET;					       /*ѡ��Ҫ���Ƶ�GPIO����*/		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     /*������������Ϊ50MHz */		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     /*��������ģʽΪͨ���������*/	
  GPIO_Init(WIZ_SPIx_RESET_PORT, &GPIO_InitStructure);		 /*���ÿ⺯������ʼ��GPIO*/
  GPIO_SetBits(WIZ_SPIx_RESET_PORT, WIZ_RESET);		
  /*����INT����*/	
  GPIO_InitStructure.GPIO_Pin = WIZ_INT;						       /*ѡ��Ҫ���Ƶ�GPIO����*/		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     /*������������Ϊ50MHz*/		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				     /*��������ģʽΪͨ������ģ����������*/		
  GPIO_Init(WIZ_SPIx_INT_PORT, &GPIO_InitStructure);			 /*���ÿ⺯������ʼ��GPIO*/

//  /*������ģʽ��λwifiģ��*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;					       /*ѡ��Ҫ���Ƶ�GPIO����*/		 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		     /*������������Ϊ50MHz */		
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     /*��������ģʽΪͨ���������*/	
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//  GPIO_ResetBits(GPIOA, GPIO_Pin_0);		

}

/**
*@brief		W5500Ƭѡ�ź����ú���
*@param		val: Ϊ��0����ʾƬѡ�˿�Ϊ�ͣ�Ϊ��1����ʾƬѡ�˿�Ϊ��
*@return	��
*/
void wiz_cs(uint8_t val)
{
	if (val == LOW) 
	{
	  GPIO_ResetBits(WIZ_SPIx_SCS_PORT, WIZ_SPIx_SCS); 
	}
	else if (val == HIGH)
	{
	  GPIO_SetBits(WIZ_SPIx_SCS_PORT, WIZ_SPIx_SCS); 
	}
}

/**
*@brief		����W5500��Ƭѡ�˿�SCSnΪ��
*@param		��
*@return	��
*/
void iinchip_csoff(void)
{
	wiz_cs(LOW);
}

/**
*@brief		����W5500��Ƭѡ�˿�SCSnΪ��
*@param		��
*@return	��
*/
void iinchip_cson(void)
{	
   wiz_cs(HIGH);
}

/**
*@brief		W5500��λ���ú���
*@param		��
*@return	��
*/
void reset_w5500(void)
{
	GPIO_ResetBits(WIZ_SPIx_RESET_PORT, WIZ_RESET);
	delay_us(2);  
	GPIO_SetBits(WIZ_SPIx_RESET_PORT, WIZ_RESET);
	delay_ms(1600);
}

uint8_t SPI_SendByte(uint8_t byte)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(WIZ_SPIx, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(WIZ_SPIx, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(WIZ_SPIx, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(WIZ_SPIx);
}

/**
*@brief		STM32 SPI1��д8λ����
*@param		dat��д���8λ����
*@return	��
*/
uint8_t  IINCHIP_SpiSendData(uint8_t dat)
{
   return(SPI_SendByte(dat));
}

/**
*@brief		д��һ��8λ���ݵ�W5500
*@param		addrbsb: д�����ݵĵ�ַ
*@param   data��д���8λ����
*@return	��
*/
void IINCHIP_WRITE( uint32_t addrbsb,  uint8_t data)
{
   iinchip_csoff();                              		
   IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);	
   IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
   IINCHIP_SpiSendData( (addrbsb & 0x000000F8) + 4);  
   IINCHIP_SpiSendData(data);                   
   iinchip_cson();                            
}

/**
*@brief		��W5500����һ��8λ����
*@param		addrbsb: д�����ݵĵ�ַ
*@param   data����д��ĵ�ַ����ȡ����8λ����
*@return	��
*/
uint8_t IINCHIP_READ(uint32_t addrbsb)
{
   uint8_t data = 0;
   iinchip_csoff();                            
   IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);
   IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
   IINCHIP_SpiSendData( (addrbsb & 0x000000F8))    ;
   data = IINCHIP_SpiSendData(0x00);            
   iinchip_cson();                               
   return data;    
}

/**
*@brief		��W5500д��len�ֽ�����
*@param		addrbsb: д�����ݵĵ�ַ
*@param   buf��д���ַ���
*@param   len���ַ�������
*@return	len�������ַ�������
*/
uint16_t wiz_write_buf(uint32_t addrbsb,uint8_t* buf,uint16_t len)
{
   uint16_t idx = 0;
   if(len == 0) printf("Unexpected2 length 0\r\n");
   iinchip_csoff();                               
   IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);
   IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
   IINCHIP_SpiSendData( (addrbsb & 0x000000F8) + 4); 
   for(idx = 0; idx < len; idx++)
   {
     IINCHIP_SpiSendData(buf[idx]);
   }
   iinchip_cson();                           
   return len;  
}

/**
*@brief		��W5500����len�ֽ�����
*@param		addrbsb: ��ȡ���ݵĵ�ַ
*@param 	buf����Ŷ�ȡ����
*@param		len���ַ�������
*@return	len�������ַ�������
*/
uint16_t wiz_read_buf(uint32_t addrbsb, uint8_t* buf,uint16_t len)
{
  uint16_t idx = 0;
  if(len == 0)
  {
    printf("Unexpected2 length 0\r\n");
  }
  iinchip_csoff();                                
  IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);
  IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
  IINCHIP_SpiSendData( (addrbsb & 0x000000F8));    
  for(idx = 0; idx < len; idx++)                   
  {
    buf[idx] = IINCHIP_SpiSendData(0x00);
  }
  iinchip_cson();                                  
  return len;
}

/**
*@brief		STM32��ʱ��2��ʼ��
*@param		��
*@return	��
*/
void timer2_init(void)
{
//	TIM2_NVIC_Configuration();															/* ��ʱ�����ж����ȼ� */
	TIM2_Configuration();																		/* TIM2 ��ʱ���� */
}

/**
*@brief		dhcp�õ��Ķ�ʱ����ʼ��
*@param		��
*@return	��
*/
void dhcp_timer_init(void)
{
  timer2_init();																	
}

/**
*@brief		ntp�õ��Ķ�ʱ����ʼ��
*@param		��
*@return	��
*/
void ntp_timer_init(void)
{
  timer2_init();																	
}

/**
*@brief		��ʱ��2�жϺ���
*@param		��
*@return	��
*/
void timer2_isr(void)
{
  ms++;	
  if(ms>=1000)
  {  
    ms=0;
    dhcp_time++;																					/*DHCP��ʱ��1S*/
	  #ifndef	__NTP_H__
	  ntptimer++;																						/*NTP����ʱ���1S*/
	  #endif
  }

}
/**
*@brief		STM32ϵͳ��λ����
*@param		��
*@return	��
*/
void reboot(void)
{
  pFunction Jump_To_Application;
  uint32_t JumpAddress;
  printf(" ϵͳ�����С���\r\n");
  JumpAddress = *(vu32*) (0x00000004);
  Jump_To_Application = (pFunction) JumpAddress;
  Jump_To_Application();
}



void W5500Init(void)
{
	gpio_for_w5500_config();						        /*��ʼ��MCU�������*/
	reset_w5500();											/*Ӳ��λW5500*/
	set_w5500_mac();										/*����MAC��ַ*/
	set_w5500_ip();											/*����IP��ַ*/
  //ESP07PwrOff();
//	while(dhcp_ok == 0){
//		do_dhcp();
//	}
	//set_w5500_ip();											/*����IP��ַ*/
	
	socket_buf_init(txsize, rxsize);		/*��ʼ��8��Socket�ķ��ͽ��ջ����С*/

}
