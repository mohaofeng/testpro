#ifndef _W5500_CONF_H_
#define _W5500_CONF_H_

#include "stm32f10x.h"
#include "stdio.h"
#include <stdint.h>
//#include "types.h"
#define __GNUC__

typedef  void (*pFunction)(void);

extern uint8_t    remote_ip[4];                            	  /* Զ��IP��ַ                   */
extern uint8_t    use_dhcp;                              	    /* �Ƿ�ʹ��DHCP��ȡIP           */
extern uint8_t    use_eeprom;                             	  /* �Ƿ�ʹ��EEPROM�е�IP������Ϣ */

/*
 * ͨ���궨��ѡ��Ŀ�꿪����
 * STM32F103ZET6 -> ����ISO-V3������
 * STM32F103VET6 -> ����ISO-MINI-V3������
 */
/*ʹ�ñ���ISO-MINI-V3������*/
#define STM32F103VET6
#undef  STM32F103ZET6

/*����SPI1��ΪW5500��Ӳ���ӿ�*/
#define WIZ_SPIx_GPIO_PORT      GPIOA								  	  	/* GPIO�˿�                     */
#define WIZ_SPIx_GPIO_CLK       RCC_APB2Periph_GPIOA	  	  /* GPIO�˿�ʱ��                 */
#define WIZ_SPIx                SPI1                   	    /* ����W5500���õ�SPI�ӿ�       */
#define WIZ_SPIx_CLK_CMD        RCC_APB2PeriphClockCmd
#define WIZ_SPIx_CLK            RCC_APB2Periph_SPI1    	    /* ����W5500���õ�SPI�ӿ�ʱ��   */
#define WIZ_SPIx_SCLK           GPIO_Pin_5						   	  /* ����W5500��ʱ�ӹܽ�          */
#define WIZ_SPIx_MISO           GPIO_Pin_6						   	  /* ����W5500��MISO�ܽ�          */
#define WIZ_SPIx_MOSI           GPIO_Pin_7						   	  /* ����W5500��MOSI�ܽ�          */



#ifdef  STM32F103ZET6 
  #define WIZ_SPIx_SCS          GPIO_Pin_9						   	  /* ����W5500��Ƭѡ�ܽ�          */
  #define WIZ_SPIx_SCS_PORT     GPIOG									   	  /* GPIO�˿�                     */
  #define WIZ_SPIx_SCS_CLK      RCC_APB2Periph_GPIOG	   	  /* GPIO�˿�ʱ��                 */
   
	#define WIZ_RESET             GPIO_Pin_4									/* ����W5500��RESET�ܽ�         */
  #define WIZ_SPIx_RESET_PORT   GPIOA									   	  /* GPIO�˿�                     */
  #define WIZ_SPIx_RESET_CLK    RCC_APB2Periph_GPIOA	  	  /* GPIO�˿�ʱ��                 */
  
	#define WIZ_INT               GPIO_Pin_4									/* ����W5500��INT�ܽ�           */
  #define WIZ_SPIx_INT_PORT     GPIOC									      /* GPIO�˿�                     */
  #define WIZ_SPIx_INT_CLK      RCC_APB2Periph_GPIOC	      /* GPIO�˿�ʱ��                 */
#endif


#ifdef STM32F103VET6 
  #define WIZ_SPIx_SCS          GPIO_Pin_3						 	    /* ����W5500��Ƭѡ�ܽ�          */
  #define WIZ_SPIx_SCS_PORT     GPIOC									 	    /* GPIO�˿�                     */
  #define WIZ_SPIx_SCS_CLK      RCC_APB2Periph_GPIOC	 	    /* GPIO�˿�ʱ��                 */
  
	#define WIZ_RESET             GPIO_Pin_4									/* ����W5500��RESET�ܽ�         */
  #define WIZ_SPIx_RESET_PORT   GPIOA									  	  /* GPIO�˿�                     */
  #define WIZ_SPIx_RESET_CLK    RCC_APB2Periph_GPIOA	 	    /* GPIO�˿�ʱ��                 */
  
	#define WIZ_INT               GPIO_Pin_4									/* ����W5500��INT�ܽ�           */
  #define WIZ_SPIx_INT_PORT     GPIOC									      /* GPIO�˿�                     */
  #define WIZ_SPIx_INT_CLK      RCC_APB2Periph_GPIOC	      /* GPIO�˿�ʱ��                 */
#endif

#define FW_VER_HIGH  						1               
#define FW_VER_LOW    					0
#define ON	                 		1
#define OFF	                 		0
#define HIGH	           	 			1
#define LOW		             			0

#define MAX_BUF_SIZE		 				1460       			            /*����ÿ�����ݰ��Ĵ�С*/
#define KEEP_ALIVE_TIME	     		30	// 30sec
#define TX_RX_MAX_BUF_SIZE      2048							 
#define EEPROM_MSG_LEN        	sizeof(EEPROM_MSG)

#define IP_FROM_DEFINE	        0       			              /*ʹ�ó�ʼ�����IP��Ϣ*/
#define IP_FROM_DHCP	          1       			              /*ʹ��DHCP��ȡIP��Ϣ*/
#define IP_FROM_EEPROM	        2       			              /*ʹ��EEPROM�����IP��Ϣ*/




//extern uint8_t	ip_from;											  


///*ѡ��IP��Ϣ����Դ*/
/*�˽ṹ�嶨����W5500�ɹ����õ���Ҫ����*/
typedef struct _CONFIG_MSG											
{
  uint8_t mac[6];																							/*MAC��ַ*/
  uint8_t lip[4];																							/*local IP����IP��ַ*/
  uint8_t sub[4];																							/*��������*/
  uint8_t gw[4];																							/*����*/	
  uint8_t dns[4];																							/*DNS��������ַ*/
  uint8_t rip[4];																							/*remote IPԶ��IP��ַ*/
	uint8_t sw_ver[2];																					/*����汾��*/
}CONFIG_MSG;
extern CONFIG_MSG  	ConfigMsg;




extern uint8_t dhcp_ok;																				/*DHCP��ȡ�ɹ�*/
extern uint32_t	dhcp_time;																		/*DHCP���м���*/
extern vu8	ntptimer;																				/*NPT�����*/

/*MCU������غ���*/
void gpio_for_w5500_config(void);														/*SPI�ӿ�reset ���ж�����*/
void timer2_init(void);																			/*STM32��ʱ��2��ʼ��*/
void timer2_isr(void);																			/*��ʱ���ж�ִ�еĺ���*/
void reboot(void);																					/*STM32��λ*/
void write_config_to_eeprom(void);													/*д������Ϣ��EEPROM��*/
void read_config_from_eeprom(void);													/*��EEPROM�ж�����Ϣ*/

/*W5500SPI��غ���*/
void IINCHIP_WRITE( uint32_t addrbsb,  uint8_t data);						/*д��һ��8λ���ݵ�W5500*/
uint8_t IINCHIP_READ(uint32_t addrbsb);													/*��W5500����һ��8λ����*/
uint16_t wiz_write_buf(uint32_t addrbsb,uint8_t* buf,uint16_t len);	/*��W5500д��len�ֽ�����*/
uint16_t wiz_read_buf(uint32_t addrbsb, uint8_t* buf,uint16_t len);	/*��W5500����len�ֽ�����*/

/*W5500����������غ���*/
void reset_w5500(void);																			/*Ӳ��λW5500*/
void set_w5500_mac(void);																		/*����W5500��MAC��ַ*/
void set_w5500_ip(void);																		/*����W5500��IP��ַ*/

/*��Ҫ�ö�ʱ�ĵ�Ӧ�ú���*/
void dhcp_timer_init(void);																	/*dhcp�õ��Ķ�ʱ����ʼ��*/
void ntp_timer_init(void);																	/*npt�õ��Ķ�ʱ����ʼ��*/
void W5500Init(void);

#endif
