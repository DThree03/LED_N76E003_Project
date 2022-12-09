/*
 * Queue.h
 *
 *  Created on: Oct 29, 2021
 *  Author: DThree
 */

#ifndef  QUEUE_H_INCLUDED
#define  QUEUE_H_INCLUDED

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef struct
{
	volatile unsigned long u32ReadPtr;
	volatile unsigned long u32WritePtr;
	unsigned long u32Length;
	unsigned char *pau8Buffer;
}tsQueue;

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

void vQueue_Init(tsQueue *psQueue, unsigned char *pau8Buffer, unsigned long u32Length);
void vQueue_Flush(tsQueue *psQueue);
bit bQueue_Write(tsQueue *psQueue, unsigned char u8Item);
bit bQueue_Read(tsQueue *psQueue, unsigned char *pu8Item);
bit bQueue_IsEmpty(tsQueue *psQueue);
bit bQueue_IsFull(tsQueue *psQueue);
unsigned long u32Queue_GetDepth(tsQueue *psQueue);

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/


#endif  /* QUEUE_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/