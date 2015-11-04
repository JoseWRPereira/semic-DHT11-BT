#include "dht11.h"
#include "SysTick.h"

struct dht11_T sensor;
unsigned long DHT11_In( unsigned long * ptrValor )
{
	unsigned char crc;
	unsigned char checkSum;
  unsigned char DHT11_STATE = 0;
  unsigned char DHT11_cBits = 0;
	
	do
	{	
	  switch( DHT11_STATE )
	  {
	    case 0: DHT11_STATE = 1;
							GPIO_PORTD_DIR_R |= 0x00000008; 			// PD3 <- OUT
							SysTick_Init_us( 1 );
							DHT11_PIN = 0x00;
							crc = 0;
							checkSum = 0;
							DHT11_cBits = 0;
							*ptrValor = 0;
							break;
		  case 1:	DHT11_STATE = 2;
							SysTickWaitBusy( 20000 );
							break;
		  case 2:	DHT11_STATE = 3;
							DHT11_PIN = 0xFF;
							GPIO_PORTD_DIR_R &= 0xFFFFFFF7; 			// PD3 <- IN
							break;
		  case 3: 																			// wait 0 - 20..40us - Inicio de recepção
							if( !DHT11_PIN )
								DHT11_STATE = 4;
							break;
		  case 4: 																			// wait 1 - 80us
							if( DHT11_PIN )
								DHT11_STATE = 5;
							break;
		  case 5:																				// wait 0 - 80us
							if( !DHT11_PIN )
								DHT11_STATE = 6;
							break;
		  case 6:																				// wait 1 - 50us
							if( DHT11_PIN )
							{
								SysTickWaitBusy( 30 );							// wait 30us
								DHT11_STATE = 7;
							}
							break;
		  case 7:	DHT11_STATE = 8;											// Read Bit
							if( ++DHT11_cBits <= 32 )
							{
								*ptrValor <<= 1;
								if( DHT11_PIN )
									++*ptrValor;
							}
							else
							{
								crc <<= 1;
								if( DHT11_PIN )
									++crc;
							}
							break;
		  case 8:																				// wait 0
							if( DHT11_cBits >= 40 )
								DHT11_STATE = 9;
							else
								if( !DHT11_PIN )
									DHT11_STATE = 6;
							break;
		  case 9: DHT11_STATE = 0;
							checkSum  = *(((unsigned char *)ptrValor)+3);
							checkSum += *(((unsigned char *)ptrValor)+2);
							checkSum += *(((unsigned char *)ptrValor)+1);
							checkSum += *(((unsigned char *)ptrValor)+0);
							SysTick_Init_ms( 1 );
							SysTickWaitBusy( 100 );
							break;
	  }
	}
	while( DHT11_STATE );
	
  return(crc==checkSum);
}

