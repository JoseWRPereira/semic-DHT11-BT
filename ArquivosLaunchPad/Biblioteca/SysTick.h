#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "tm4c123gh6pm.h"

void SysTick_Init_ms( unsigned long baseTempo_ms );
void SysTick_Init_us( unsigned long baseTempo_us );
unsigned char SysTickRun( void );
void SysTickWaitBusy( unsigned long time );

#endif //__SYSTICK_H__
