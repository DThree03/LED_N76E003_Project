/******************** (C) COPYRIGHT 2021 H3ElTeam ********************
* File Name          : Uart_RingBuff.c
* Author             : DThree
* Date First Issued  : 22/09/2021
* Description        : 
*********************************************************************************/

/**		Hardware Define		**/
#include "Function_Define.h"

#include "Queue.h"
#include "Uart_Buff.h"

static tsQueue	asUart_RxQueue;

bit bUartRead(unsigned char *pu8Data)
{
    return(bQueue_Read(&asUart_RxQueue, pu8Data));
}

void UART_Init(unsigned long u32Baudrate, unsigned char *pu8RxBuffer, unsigned long u32RxBufferLen)
{
	vQueue_Init(&asUart_RxQueue, pu8RxBuffer, u32RxBufferLen);

    P06_Quasi_Mode;
	P07_Quasi_Mode;
	SFRS = 0;
	
	SCON = 0x50;          //UART0 Mode1,REN=1,TI=1
	set_SMOD;        //UART0 Double Rate Enable
	T3CON &= 0xF8;        //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
	set_BRCK;        //UART0 baud rate clock source = Timer3
	RH3    = HIBYTE(65536 - (1000000/u32Baudrate) - 1);
	RL3    = LOBYTE(65536 - (1000000/u32Baudrate) - 1);
	set_TR3;         //Trigger Timer3
	set_ES;
}
void UART_Send_Data(unsigned char c)
{
    _push_(SFRS);
    SFRS = 0;
	
    SBUF = c;
	while(!TI);
	TI=0;
    _pop_(SFRS);
}

void SerialPort0_ISR(void) interrupt 4
{
	_push_(SFRS);
	if (RI == 1)
	{
		bQueue_Write(&asUart_RxQueue, (unsigned char)SBUF);
		clr_RI;            	// Clear RI (Receive Interrupt).
	}
	_pop_(SFRS);
}

#ifdef PRINTF_TO_UART0
char putchar(char c)
{
	SBUF = c;
	while (!TI);
	TI = 0;
	return (c);
}
#else
char putchar(char c)
{
	SBUF_1 = c;      /* output character */
	while (!TI_1);  /* wait until transmitter ready */
	TI_1 = 0;
	return (c);
}
#endif		