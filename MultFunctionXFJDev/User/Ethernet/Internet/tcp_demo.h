#ifndef __TCP_DEMO_H
#define __TCP_DEMO_H
#include <stdint.h>
#include "stdarg.h"	 	 

//#include "types.h"

//extern uint16 W5500_tcp_server_port;
void do_tcp_server(void);//TCP Server�ػ���ʾ����
void do_tcp_client(void);//TCP Clinet�ػ���ʾ����


void NetPrintf(uint8_t *fmt, ...);




#endif 

