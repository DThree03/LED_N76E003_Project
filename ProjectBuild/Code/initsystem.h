#ifndef	_INIT_SYSTEM_H__
#define	_INIT_SYSTEM_H__

//#include "sys_clock.h"
//#include "uart.h"
//#include "timer.h"
//#include "FLASH_EEPROM.h"

/*****************************************************************************
* Global typedefs
*****************************************************************************/
#define ON          1
#define OFF         0
/*		GPIO CONFIG ZONE		*/
#define ADD1_INIT   P11_Input_Mode
#define ADD1_VAL    P11
#define ADD2_INIT   P12_Input_Mode
#define ADD2_VAL    P12
#define ADD3_INIT   P13_Input_Mode
#define ADD3_VAL    P13
#define ADD4_INIT   P14_Input_Mode
#define ADD4_VAL    P14

#define	LED1_INIT	P03_PushPull_Mode
#define	LED1_TOG	P03 ^= 1
#define LED1        P03

#define	LED2_INIT	P04_PushPull_Mode
#define LED2        P04
#define	LED2_TOG	P04 ^= 1

#define	LED3_INIT	P05_PushPull_Mode
#define LED3        P05
#define	LED3_TOG	P05 ^= 1

#define	LED4_INIT	P15_PushPull_Mode
#define LED4        P15
#define	LED4_TOG	P15 ^= 1

#define LED_WRITE(LED, VAL)     LED = VAL
/*****************************************************************************
* Globals variable
*****************************************************************************/
extern bit BIT_TMP;
extern volatile bit bFlagDelay;
extern volatile unsigned int sys_millis;
extern volatile unsigned long uCountDelay;

/*****************************************************************************
* Public functions
*****************************************************************************/
void SystemInit(void);

void delay_ms(unsigned int x);

#endif
