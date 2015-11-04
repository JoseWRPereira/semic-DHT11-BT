#ifndef __DHT11_H__
#define __DHT11_H__

#include "tm4c123gh6pm.h"

#define PORTD										0x40007000
#define DHT11_PIN								(*((volatile unsigned long *)(PORTD|(0x08<<2)))) //PD3


struct dht11_T
{
  unsigned char temperaturad;
	unsigned char temperatura;
	unsigned char umidaded;
	unsigned char umidade;
};
extern struct dht11_T sensor;
unsigned long DHT11_In( unsigned long * ptrValor );


#endif // __DHT11_H__
