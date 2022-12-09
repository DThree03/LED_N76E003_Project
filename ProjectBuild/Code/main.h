#ifndef	_MAIN_H__
#define	_MAIN_H__

#include <string.h>
#include "Function_define.h"
#include "initsystem.h"

#include "TM1629A_MRLG.h"
/*		DATA ZONE		*/
#define START_FLASH_ADDRESS	16000

/*		MAIN STATE ZONE		*/
#define	STATE_0     0
#define	STATE_1	    1
#define	STATE_ERR	2
volatile unsigned char	MainState = STATE_0;

#define DATA_LED7_TYPE      1
#define UPDATE_LED7_TYPE    2
#define DATA_LEDXL_TYPE     3
#define UPDATE_BLINK_STATE  4

/*		TIMING ZONE		*/

#define TASK1 1000
#define TASK2 1000 
#define TASK3 100
#define	TASK4 5000
#define	TASK5 1000

typedef struct
{
	unsigned char Task1;
	unsigned char Task2;
	unsigned char Task3;
	unsigned char Task4;
	unsigned char Task5;
} _StrTask;
_StrTask	StrTask;

static void  Task_Serial_Display(void);
static void  Task1(void);
static void  Task2(void);
static void  Task3(void);
static void  Task4(void);
static void  Task5(void);

static int get_board_addr(void);
#endif
