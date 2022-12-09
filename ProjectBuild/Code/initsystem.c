
#include "initsystem.h"
#include "Function_define.h"

/*****************************************************************************
* Globals variable
*****************************************************************************/
bit BIT_TMP;
volatile bit bFlagDelay = 0;
volatile unsigned int sys_millis = 0;
volatile unsigned long uCountDelay = 0;

/*****************************************************************************
* Static functions prototype
*****************************************************************************/
static void GPIO_User_Init(void);
static void InitClock(void);
static void Init_Timer0(void);

/*****************************************************************************
* Public functions
*****************************************************************************/
void SystemInit(void)
{
	InitClock();
	GPIO_User_Init();
	Init_Timer0();
	set_EA;			//Enable golbalInterrupt
}

void delay_ms(unsigned int x)
{
	static unsigned long uDelay = 0;
	uDelay = x;
	bFlagDelay = 1;
	uCountDelay = 0;
	while(uCountDelay<=uDelay)
	{
		
	}
	bFlagDelay = 0;
}

/*****************************************************************************
* Static functions
*****************************************************************************/
static void InitClock(void)
{
	/* MCU power on system clock is HIRC (16 MHz) */
	
	/*Or you can modify to other HIRC clock*/
	//MODIFY_HIRC(HIRC_24);
	
	/*Or you can select other clock source*/
	/**
  * @brief This API configures system clock source
  * @param[in] u8FsysMode . Valid values are:
  *                       - \ref FSYS_HIRC                :Internal HIRC (16MHz as default).
  *                       - \ref FSYS_LIRC                :Internal LIRC.
  *                       - \ref FSYS_OSCIN_P00           :External clock input from P0.0.
  * @note      None.
  * @exmaple : FsysSelect(FSYS_LIRC);
  */
	//FsysSelect(FSYS_HIRC);
	//MODIFY_HIRC(HIRC_16);
}

static void GPIO_User_Init(void)
{
	ADD1_INIT; ADD2_INIT; ADD3_INIT; ADD4_INIT;
    
    LED1_INIT; LED_WRITE(LED1, OFF);
    LED2_INIT; LED_WRITE(LED2, OFF);
    LED3_INIT; LED_WRITE(LED3, OFF);
    LED4_INIT; LED_WRITE(LED4, OFF);
}

static void Init_Timer0(void)
{		//Timer0_Mode1
	clr_T0M;
	TIMER0_MODE1_ENABLE;    
	TH0 = (unsigned int)TIMER_DIV12_VALUE_1ms/256;	
	TL0 = (unsigned int)TIMER_DIV12_VALUE_1ms%256;
	set_ET0;   //enable interrupts
	set_TR0;  //Timer0 run
}
