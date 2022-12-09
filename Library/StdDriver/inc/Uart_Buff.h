/******************** (C) COPYRIGHT 2021 H3ElTeam ********************
* File Name          : Uart_RingBuff.h
* Author             : DThree
* Date First Issued  : 22/09/2021
* Description        : 
*********************************************************************************/
#ifndef	_UART_BUFF_H_
#define	_UART_BUFF_H_

//#define PRINTF_TO_UART1
#ifndef PRINTF_TO_UART1
	#define		PRINTF_TO_UART0
#endif

bit bUartRead(unsigned char *pu8Data);

void UART_Init(unsigned long u32Baudrate, unsigned char *pu8RxBuffer, unsigned long u32RxBufferLen);

void UART_Send_Data(unsigned char c);

/*	Use for printf function	*/
char putchar(unsigned char c);

#endif