#include "bsp_usart1.h"
//#include<stdlib.h>
#include "queue.h"

/***********************************************
Function: Create a empty stack;
************************************************/
PQUEUE CreateLanQueue(PQUEUE Q)
{
	Q->front=0;         //?????
	Q->rear=0;
	Q->qlen=0;
	return Q;       
}


void ClearQ(PQUEUE Q)
{
	Q->front=0;         
	Q->rear=0;
	Q->qlen=0;
}

void TraverseLanQueue(PQUEUE Q)
{
	int i=Q->front;
	#if QUEUE_DBG
	printf("�����е�Ԫ����:\r\n");
	#endif
	while(i%QLEN_MAX != Q->rear)
	{
		//printf("%d ",Q->dat[i]);
		i++;
	}
	//printf("\r\n");
}

BOOL FullLanQueue(PQUEUE Q)
{
	if(Q->front==(Q->rear+1)%QLEN_MAX)
	{    
		#if QUEUE_DBG
		printf("��������\r\n");
		#endif		
		return TRUE;
	}
	else
	{
		#if QUEUE_DBG
		printf("���пգ�\r\n");
		#endif		
		return FALSE;
	}
}
BOOL EmptyLanQueue(PQUEUE Q)
{
	if(Q->front == Q->rear) 
	{		
		#if QUEUE_DBG
		printf("���пգ�\r\n");
		#endif		
		return TRUE;
	}
	else
	{
		#if QUEUE_DBG
		printf("���зǿգ�\r\n");
		#endif		
		return FALSE;
	}
}

/***********************************************
Function: Print the stack element;
************************************************/
// BOOL EnQueue(PQUEUE Q,elementType val)
// {
// 	if(FullLanQueue(Q))
// 	{
// 		return FALSE;
// 	}
// 	else
// 	{
// 		Q->dat[Q->rear]=val;
// 		Q->rear=(Q->rear+1)%QLEN_MAX;
// 		Q->qlen++;
// 		#if QUEUE_DBG
// 		printf("������ӳɹ�val=0x%x\r\n",val);
// 		#endif		
// 		return TRUE;
// 	}
// }
BOOL EnQueue(PQUEUE Q,elementType val)
{
	if(Q->front!=(Q->rear+1)%QLEN_MAX)//���з���
	{    
		Q->dat[Q->rear]=val;
		Q->rear=(Q->rear+1)%QLEN_MAX;
		Q->qlen++;
		#if QUEUE_DBG
		printf("������ӳɹ�val=0x%x\r\n",val);
		#endif		
		return TRUE;
	}
	else
	{
		#if QUEUE_DBG
		printf("���������������ʧ��\r\n");
		#endif		
		return FALSE;
	}
}
/***********************************************
Function: n��Ԫ�����
************************************************/
BOOL EnQueuex(PQUEUE Q,elementType *val, qsize n)
{
	uint16_t i=0;
	#if QUEUE_DBG
	printf("��%d��Ԫ����Ҫ���\r\n",n);
	#endif			
	for(i=0;i<n;i++)
	{
		if(EnQueue(Q,val[i]) == FALSE)
		{
			return FALSE;
		}
	}
	return TRUE;
}
// BOOL EnQueuex(PQUEUE Q,elementType *val, qsize n)
// {
// 	uint16_t i=0;
// 	#if QUEUE_DBG
// 	printf("��%d��Ԫ����Ҫ���\r\n",n);
// 	#endif			
// 	for(i=0;i<n;i++)
// 	{
// 		EnQueue(Q,val[i]);
// 		{
// 			return FALSE;
// 		}
// 	}
// 	return TRUE;
// }

/***********************************************
Function: ����ʣ�೤��
************************************************/
qsize QueueEmptyLen(PQUEUE Q)
{
	qsize i;
	i= Q->front+QLEN_MAX-Q->rear;
//	i= QLEN_MAX-Q->qlen;
	
	#if QUEUE_DBG
	printf("����ʣ��ռ䳤�ȣ�%d\r\n",i);
	#endif		
	return (i);
}


/***********************************************
Function: ����������Ч����
************************************************/
qsize QueueDatLen(PQUEUE Q)
{
		//printf("���г���Ϊ%d\r\n",i);
		return (Q->qlen);
}

BOOL DeQueue(PQUEUE Q, elementType *val)
{
	if(EmptyLanQueue(Q))
	{
		return FALSE;
	}
	else
	{
		*val=Q->dat[Q->front];
		Q->front=(Q->front+1)%QLEN_MAX;
		Q->qlen--;
		#if QUEUE_DBG
		printf("���ݳ��ӳɹ���*val=0x%x\r\n",*val);
		#endif		
		return TRUE;
	}
}
/***********************************************
Function: n��Ԫ�س���
************************************************/
BOOL DeQueuex(PQUEUE Q,elementType *val, qsize n)
{
	qsize i;
	for(i=0;i<n;i++)
	{
		if(DeQueue(Q,&val[i]) == FALSE)
			return FALSE;
	}
	return TRUE;
}
