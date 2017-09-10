#ifndef __COMMON_H
#define __COMMON_H



#include "stm32f10x.h"
#include <stdlib.h>
#include <string.h>


/******************************* �궨�� ***************************/
#define            macNVIC_PriorityGroup_x                     NVIC_PriorityGroup_2



/********************************** �������� ***************************************/
void                     USART_printf                       ( USART_TypeDef * USARTx, char * Data, ... );



//#define DBG_PRINTF( fmt, ... )	NetPrintf( fmt, ##__VA_ARGS__ )
#define DBG_PRINTF( fmt, ... )	printf( fmt, ##__VA_ARGS__ )



//��source�ַ���������s1�ַ�ȫ���滻���ַ�s2

void replace_char(char *result, char *source, char s1, char s2);
//void Arr2String(char *strbuf,uint8_t *pc,uint32_t len);

#endif /* __COMMON_H */

