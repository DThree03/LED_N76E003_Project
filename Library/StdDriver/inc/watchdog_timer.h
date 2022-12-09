#ifndef	_INIT_BQ769x0_H__
#define	_INIT_BQ769x0_H__

/* Note: enable WDT config bit in Target Option -> Debug -> Setting Use		*/

/*Call Check_WDT_Reset_Config() before Init WDT*/

void Check_WDT_Reset_Config(void);

/*Check WatchDog_Timer_Init() before while(1) to see MCU reset form WDT or other reason*/
/*	Example
	if(!WatchDog_Timer_Init){
		//MCU Reset in other reason
	}
	else{
		//MCU watchdog timer reset
	}	*/
	
char WatchDog_Timer_Init(void);

#endif
