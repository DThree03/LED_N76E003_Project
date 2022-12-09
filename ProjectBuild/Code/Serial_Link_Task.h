/******************** (C) COPYRIGHT 2021 H3ElTeam ********************
* File Name          : Serial_Link_Task.h
* Author             : DThree
* Date First Issued  : 21/09/2021
* Description        : This file 
*********************************************************************************/
#ifndef	_SERIAL_LINK_H_
#define	_SERIAL_LINK_H_

void Serial_Link_Init(void);

//void Serial_Tx_Send(unsigned char u8Type, unsigned int u16Length, unsigned char *pu8Data);

bit Serial_Link_Task(void);

unsigned char Serial_Get_DataType(void);

unsigned char Serial_Get_DataAddr(void);

unsigned char* Serial_Get_DataIn(void);
    
#endif