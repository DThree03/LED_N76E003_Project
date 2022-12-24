#include "main.h"
#include "Serial_Link_Task.h"
/*****************************************************************************
* Static variable
*****************************************************************************/
static int    BOARD_ADDR;

static unsigned char    blink_line = 1;
static unsigned char    blink_flag = 0;

static unsigned char    read_type;
static unsigned char    read_addr;
unsigned char*          read_buff = NULL;

static unsigned char    DATA_LED_7[16] = {21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21};
static unsigned char    DATA_LED_XL[4] = {0, 0, 0, 0};
/*****************************************************************************
* Main Loop
*****************************************************************************/
void main(void)
{
	SystemInit();
    Serial_Link_Init();
    delay_ms(2000);
    
    BOARD_ADDR = get_board_addr();
    //printf("Read addr %d\n", BOARD_ADDR);
    if(BOARD_ADDR == 0)
    {
        MainState = STATE_ERR;
        goto error;
    }
        
    TM1629_Begin();
    
    //setNshowAllSeg(DATA_LED_7);
	while (1)
	{	
		switch (MainState)
		{
			case STATE_0:

			while(1)
			{
                Task_Serial_Display();
				if(MainState!=STATE_0)
				{
					break;
				}
			}
			break;
			
			case STATE_1:

			while(1)
			{
                Task_Serial_Display();
				Task1();
				if(MainState!=STATE_1)
				{
					break;
				}
			}
			break;
			case STATE_ERR:
                while(1)
                {
error:              Task5();                    
                    if(MainState!=STATE_ERR)
                        break;
                }	
                break;
		}
	}
}

/*****************************************************************************
* ISR 
*****************************************************************************/
void Timer0_ISR (void) interrupt 1					//interrupt address is 0x000B
{
	/* Reload counter */
	TH0 = (unsigned int)TIMER_DIV12_VALUE_1ms/256;
	TL0 = (unsigned int)TIMER_DIV12_VALUE_1ms%256; 
	/* Increase system click and set flag task enable */
	sys_millis++;
	if(bFlagDelay==1)
	{
		uCountDelay++;
	}
	else
	{
		uCountDelay=0;
	}
	if(sys_millis>=10000)	 		sys_millis=0;
	if(sys_millis%TASK1==0)			StrTask.Task1=1;
	if(sys_millis%TASK2==0)			StrTask.Task2=1;
	if(sys_millis%TASK3==0)			StrTask.Task3=1;
	if(sys_millis%TASK4==0)			StrTask.Task4=1;
	if(sys_millis%TASK5==0)			StrTask.Task5=1;
}
/*
void Timer1_ISR (void) interrupt3					//interruptaddress is 0x001B
{	
	  TH1 = (unsignedint)TIMER_DIV12_VALUE_1ms/256;
	  TL1 = (unsignedint)TIMER_DIV12_VALUE_1ms%256;
	//Custom Code
	
}

void Timer3_ISR(void) interrupt 16 
{
    clr_TF3; 
		
}
*/

void WakeUp_Timer_ISR (void)   interrupt 17     //ISR for self wake-up timer
{
			//set_SWRST;
			clr_WKTF;//clear interrupt flag   	
}
/////////////////////////////////////////////////////////////
static void Task_Serial_Display(void)
{ 
    int i;
	  
    if(Serial_Link_Task() == 0)
        return;
    read_addr = Serial_Get_DataAddr();
    if((read_addr != BOARD_ADDR) && (read_addr != 0))
        return;
        
    read_type = Serial_Get_DataType();
    switch(read_type)
    {
        case DATA_LED7_TYPE:
        {
            read_buff = Serial_Get_DataIn();
            for(i=0;i<16;i++){
                DATA_LED_7[i] = *(read_buff+i);
            }
            break;
        }
        case UPDATE_LED7_TYPE:
        {
            setNshowAllSeg(DATA_LED_7);
            break;
        }
        case UPDATE_BLINK_STATE:
        {
            read_buff = Serial_Get_DataIn();
            if(*read_buff == 1){
                blink_line = *(read_buff+1);
                MainState = STATE_1;
            }
            else{
                setNshowAllSeg(DATA_LED_7);
                MainState = STATE_0;
            }
            break;
        }
        case DATA_LEDXL_TYPE:
        {
            read_buff = Serial_Get_DataIn();
            LED_WRITE(LED1, (*read_buff&0x01)); 
            LED_WRITE(LED2, (*read_buff&0x02)>>1);
            LED_WRITE(LED3, (*read_buff&0x04)>>2);
            LED_WRITE(LED4, (*read_buff&0x08)>>3);
            break;
        }
    }       
    
}

static void Task1(void)
{ 
	if(StrTask.Task1==1)
	{	
        StrTask.Task1=0;
        
        if(blink_flag){
            setNshowAllSeg(DATA_LED_7);
            blink_flag = 0;
            return;
        }
        
        blinkSegwithLine(blink_line);
        blink_flag = 1;
    }
}

static void Task2(void)
{
	if(StrTask.Task2==1)
	{
        StrTask.Task2=0;
        
	}
}

static void Task3(void)
{
	if(StrTask.Task3==1)
	{		

		
		StrTask.Task3=0;
	}
}


static void	Task4(void)
{
	if(StrTask.Task4==1)
	{
		//printf("Vo Tan Dat");
		//putchar(0x0D);
		StrTask.Task4=0;
	}
}
static void	Task5(void)
{
	if(StrTask.Task5==1)
	{
        LED_WRITE(LED1, ON); LED_WRITE(LED2, ON); LED_WRITE(LED3, ON); LED_WRITE(LED4, ON);
        delay_ms(500);
        LED_WRITE(LED1, OFF); LED_WRITE(LED2, OFF); LED_WRITE(LED3, OFF); LED_WRITE(LED4, OFF);
        delay_ms(500);
        
        StrTask.Task5 = 0;
        if(BOARD_ADDR == 0){
            BOARD_ADDR = get_board_addr();
            if(BOARD_ADDR == 0)
                return;
        }
	}
}

static int get_board_addr(void)
{
    int address = 0;

	bitWrite(address, 0, ADD1_VAL);
	bitWrite(address, 1, ADD2_VAL);
	bitWrite(address, 2, ADD3_VAL);
	bitWrite(address, 3, ADD4_VAL);
	
	if(address == 14){// only ADD1 connect to GND -> address = 14
		address = 1;
	}
	else if(address == 13){// only ADD2 connect to GND -> address = 13
		address = 2;
	}
	else if(address == 11){// only ADD3 connect to GND -> address = 11
		address = 3;
	}
	else if(address == 7){// only ADD4 connect to GND -> address = 7
		address = 4;
	}
	else{
		address = 0;// Jump Failed or Not Jump Yet
	}		
//	printf("\nAddress = %d", address);
	
	return address;
        
}
/////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_FULL_ASSERT
	
	/**
		* @brief	Reports the name of the source file and the source line number
		*	 where the assert_param error has occurred.
		* @param file: pointer to the source file name
		* @param line: assert_param error line source number
		* @retval : None
	*/
	void assert_failed(u8* file, u32 line)
	{ 
		/* User can add his own implementation to report the file name and line number,
		ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
		
		/* Infinite loop */
		while (1)
		{
		}
	}
#endif
