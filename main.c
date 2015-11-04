/******************************************************************************

						Faculdade de Tecnologia SENAI Anchieta
	
							Pós-Graduação - Especialização em 
							Sistemas Eletrônicos para Controle
	
	Implementação de sistema contendo:
		comunicação Bluetooth utilizando módulo HC-05
		leitura de sensor de temperatura DHT11
		
					Programador: José William Rodrigues Pereira
					
					Versão: 9.0							Data: 30/09/20015

******************************************************************************/

#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "io.h"
#include "UART.h"
#include "UART2.h"
#include "SysTick.h"
#include "Bluetooth.h"
#include "Nokia5110.h"
#include "dht11.h"

int main( void )
{
	unsigned long * ptr;
	unsigned char aux;
	unsigned int tempo = 500;

	IO_Init();
	SysTick_Init_ms( tempo );
	UART_Init_16MHz();
	Nokia5110_Init();
	Bluetooth_Init();
	
  Nokia5110_OutString("SENAI");	

	for(;;)
	{
		if( UART_InCharAvailable() )
			Bluetooth_OutChar( UART_InChar() );
		
		if( Bluetooth_InCharAvailable() )
		  UART_OutChar ( aux = Bluetooth_InChar() );


		if( SysTickRun() )
		{
			if( *ptr )
		    *ptr = 0x00; 
			else
			  *ptr = 0xFF; 
		}

			switch( aux )
			{
				case 0:
				case 'R': 	*ptr = 0x00; ptr = (unsigned long *)&LED_RED;				break;
				case 'B': 	*ptr = 0x00; ptr = (unsigned long *)&LED_BLUE;			break;
				case 'G': 	*ptr = 0x00; ptr = (unsigned long *)&LED_GREEN;			break;
				case 'Y': 	*ptr = 0x00; ptr = (unsigned long *)&LED_YELLOW;		break;
				case 'P': 	*ptr = 0x00; ptr = (unsigned long *)&LED_PINK;			break;
				case 'S': 	*ptr = 0x00; ptr = (unsigned long *)&LED_SKYBLUE;		break;
				case 'W':   *ptr = 0x00; ptr = (unsigned long *)&LED_WHITE;			break;
				case 'D':   *ptr = 0x00; ptr = (unsigned long *)&LED_DARK;			break;
				case 'T': 	DHT11_In( (unsigned long *) &sensor );
										UART_OutString( "Temp: " );
										UART_OutUDec( (unsigned long)sensor.temperatura );
										UART_OutString( "\r\n" );
										Bluetooth_OutString( "Temp: " );
										Bluetooth_OutUDec( (unsigned long)sensor.temperatura ); 		
										Bluetooth_OutString( "\r\n" );
										SysTick_Init_ms( tempo );
										break;
				case 'U': 	DHT11_In( (unsigned long *) &sensor );
										UART_OutString( "Umidade: " );
										UART_OutUDec( (unsigned long)sensor.umidade );
										UART_OutString( "\r\n" );
										Bluetooth_OutString( "Umidade: " );
										Bluetooth_OutUDec( (unsigned long)sensor.umidade ); 
										Bluetooth_OutString( "\r\n" );
										SysTick_Init_ms( tempo );
										break;
			}


	} //for(;;)	
} //int main( void )
