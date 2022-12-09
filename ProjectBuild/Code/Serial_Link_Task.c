/******************** (C) COPYRIGHT 2021 H3ElTeam ********************
* File Name          : Serial_Linkl_Task.c
* Author             : DThree
* Date First Issued  : 21/09/2021
* Description        : This file run user Seriak Task
*********************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "Serial_Link_Task.h"
#include "Uart_Buff.h"

/* Private macro -------------------------------------------------------------*/
#define UART_BUFFER_LEN		200
#define BAUD_RATE			9600
#define END_CHAR            0x0A

/* Private typedef -----------------------------------------------------------*/
typedef enum{
    E_WAIT_A_CHR,
    E_WAIT_D_CHR,
    E_WAIT_D1_CHR,
    E_WAIT_R_CHR,
    E_WAIT_ADDR,
    E_WAIT_TYPE,
    E_WAIT_DATA
}e_rx_state_t;

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
//xdata volatile unsigned char uartRxBuff[UART_BUFFER_LEN];
volatile unsigned char uartRxBuff[UART_BUFFER_LEN];

static e_rx_state_t  Rx_State = E_WAIT_A_CHR;
static unsigned char  u8DataType;
static unsigned char  u8DataAddr;

static unsigned char  u8DataIn[16];
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
static unsigned char APP_vProcessRxChar(unsigned char u8Char);


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
void Serial_Link_Init(void)
{
	UART_Init(BAUD_RATE, uartRxBuff, UART_BUFFER_LEN); 
}

/*
void Serial_Tx_Send(unsigned char u8Type, unsigned int u16Length, unsigned char *pu8Data)
{
	
	
} */

bit Serial_Link_Task(void)
{
	unsigned char u8RxByte;
	while(bUartRead(&u8RxByte))
	{
		if(APP_vProcessRxChar(u8RxByte) != 0xFF)
		{			
			
			return 1;
		}
	}
	return 0;
}

unsigned char Serial_Get_DataType(void)
{
	return u8DataType;
}

unsigned char Serial_Get_DataAddr(void)
{
	return u8DataAddr;
}

unsigned char* Serial_Get_DataIn(void)
{
	return u8DataIn;
}
/****************************************************************************/
/***        Local Function			                                      ***/
/****************************************************************************/
static unsigned char APP_vProcessRxChar(unsigned char u8Char)
{
    static unsigned int RxDataCnt = 0;
	switch(Rx_State)
    {
        case E_WAIT_A_CHR:
        {
             if(u8Char == 'A')
                Rx_State = E_WAIT_D_CHR;
             break;
        }
        case E_WAIT_D_CHR:
        {
             if(u8Char == 'D')
                Rx_State = E_WAIT_D1_CHR;
             else
                Rx_State = E_WAIT_A_CHR; 
             break;
        }
        case E_WAIT_D1_CHR:
        {
             if(u8Char == 'D')
                Rx_State = E_WAIT_R_CHR;
             else
                Rx_State = E_WAIT_A_CHR; 
             break;
        }
        case E_WAIT_R_CHR:
        {
             if(u8Char == 'R')
                Rx_State = E_WAIT_ADDR;
             else
                Rx_State = E_WAIT_A_CHR; 
             break;
        }
        case E_WAIT_ADDR:
        {
             if((u8Char > 47) && (u8Char < 53)){
                u8DataAddr = u8Char - 48;
                Rx_State = E_WAIT_TYPE;
             }else
                Rx_State = E_WAIT_A_CHR; 
             break;
        }
        case E_WAIT_TYPE:
        {
             if((u8Char > 47) && (u8Char < 58)){
                u8DataType = u8Char - 48;
                RxDataCnt = 0; 
                Rx_State = E_WAIT_DATA;
             }else
                Rx_State = E_WAIT_A_CHR; 
             break;
        }
        case E_WAIT_DATA:
        {
            if(u8Char ==  END_CHAR){
                Rx_State = E_WAIT_A_CHR;
                return 1;
            }
            else if((u8Char > 47) && (u8Char < 71)){
                *(u8DataIn+RxDataCnt) = u8Char - 48;
                RxDataCnt++;
            }else
                Rx_State = E_WAIT_A_CHR; 
            break;
        }
    }
	return 0xFF;
}