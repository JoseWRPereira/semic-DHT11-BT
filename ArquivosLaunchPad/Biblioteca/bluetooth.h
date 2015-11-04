#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "tm4c123gh6pm.h"
#include "UART2.h"

#define PORTC														0x40006000
#define BT_ENABLE 											(*((volatile unsigned long *)(PORTC|0x20<<2)))
#define BT4  														(*((volatile unsigned long *)(PORTC|0x10<<2)))
#define BT5  														(*((volatile unsigned long *)(PORTC|0x20<<2)))
#define BT6  														(*((volatile unsigned long *)(PORTC|0x40<<2)))
#define BT7  														(*((volatile unsigned long *)(PORTC|0x80<<2)))


void Bluetooth_Init( void );
void Bluetooth_OutChar( unsigned char data );
void Bluetooth_OutString( char * ptr );
unsigned char Bluetooth_InCharAvailable( void );
unsigned char Bluetooth_InChar( void );
void Bluetooth_OutUDec( unsigned long n );

void Bluetooth_StartATcmd( void );
void Bluetooth_StopATcmd( void );
unsigned char Bluetooth_ATcmd( void );


#endif //__BLUETOOTH_H__
