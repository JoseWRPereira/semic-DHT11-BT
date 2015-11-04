#include "SysTick.h"


void SysTick_Init_ms( unsigned long baseTempo_ms ) 	// baseTempo_ms max = 1048 ms
{
	NVIC_ST_CTRL_R = 0; 									// Desabilita SysTick durante o setup
	NVIC_ST_RELOAD_R = baseTempo_ms*16000;// 16MHz/1 => 1MHz -> 62.5ns * 16000 -> 1ms (Base de Tempo)
	NVIC_ST_CURRENT_R = 0;								// Qq valor para limpar contagem atual
	NVIC_ST_CTRL_R =  (unsigned long)
										(
											0x04 | 						// 1=System Clock; 0=PIOSC/4;
											//0x02 |					// 1=Interrupt Enable; 0=Interrupt Disable
											0x01							// SysTick Enable
										);
}
void SysTick_Init_us( unsigned long baseTempo_us ) 	//
{
	NVIC_ST_CTRL_R = 0; 									// Desabilita SysTick durante o setup
	NVIC_ST_RELOAD_R = baseTempo_us*16;   // 16MHz/1 => 1MHz -> 62.5ns * 16 -> 1us (Base de Tempo)
	NVIC_ST_CURRENT_R = 0;								// Qq valor para limpar contagem atual
	NVIC_ST_CTRL_R =  (unsigned long)
										(
											0x04 | 						// 1=System Clock; 0=PIOSC/4;
											//0x02 |					// 1=Interrupt Enable; 0=Interrupt Disable
											0x01							// SysTick Enable
										);
}

unsigned char SysTickRun( void )										// Sinaliza fim de Contagem Setada em SysTick_Init_ms( baseTempo_ms )
{
  if( NVIC_ST_CTRL_R & 0x00010000 )	
		return( 1 );
	else
		return( 0 );
}

void SysTickWaitBusy( unsigned long time )					// Aguarda fim da contagem de 0 .. time; 
{																										// Cada unidade de tempo é configurada em SysTick_Init_ms( baseTempo_ms )
	unsigned long auxCont = 0;
	while( auxCont < time )
	{
	  if( SysTickRun() )
			auxCont++;
	}
}

