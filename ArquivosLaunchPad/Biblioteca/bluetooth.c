#include "bluetooth.h"
#include "UART2.h"
#include "io.h"
#include "UART.h"


unsigned char atcmd;
void Bluetooth_Init( void )
{
  UART2_Init_16MHz_9600bps();
  //UART2_Init_16MHz_38400bps();
  PortC_Init();
  BT_ENABLE = 0xFF; 
}

void Bluetooth_OutChar( unsigned char data )
{
  UART2_OutChar( data );
}

void Bluetooth_OutString( char * ptr )
{
  UART2_OutString( ptr );
}	

unsigned char Bluetooth_InCharAvailable( void )
{
  return( UART2_InCharAvailable() );
}

unsigned char Bluetooth_InChar( void )
{
  return ( UART2_InChar() );
}

void Bluetooth_OutUDec(unsigned long n)
{
  UART2_OutUDec( n );
}

void Bluetooth_StartATcmd( void )
{
//  UART2_Init_16MHz_9600bps();
  UART2_Init_16MHz_38400bps();
  BT_ENABLE = 0xFF; 
}

void Bluetooth_StopATcmd( void )
{
	BT_ENABLE = 0x00;
  UART2_Init_16MHz_9600bps();
	BT_ENABLE = 0xFF;  
}

unsigned char Bluetooth_ATcmd( void )
{
	unsigned char aux;
	
	if( UART_InCharAvailable() )
	{
		Bluetooth_OutChar( aux = UART_InChar() );
	}
	if( UART2_InCharAvailable() )
	{
	  UART_OutChar( Bluetooth_InChar() );
	}
	
	if( aux == '#' )
	  return( 0 );
	else
		return( 1 );
}
