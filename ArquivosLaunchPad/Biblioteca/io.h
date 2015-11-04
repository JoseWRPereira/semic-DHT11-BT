#ifndef __IO_H__
#define __IO_H__

#include "tm4c123gh6pm.h"



#define PORTD										0x40007000
#define PORTE										0x40024000
#define PORTF										0x40025000

// 																								Color    LED(s) PortF
#define DARK										0								// dark     ---    0
#define RED											(0x02<<2)				// red      R--    0x02
#define BLUE										(0x04<<2)				// blue     --B    0x04
#define GREEN										(0x08<<2) 			// green    -G-    0x08
#define YELLOW									(0x0A<<2)  			// yellow   RG-    0x0A
#define PINK										(0x06<<2) 			// pink     R-B    0x06
#define SKYBLUE									(0x0C<<2)	    	// sky blue -GB    0x0C
#define WHITE										(0x0E<<2)				// white    RGB    0x0E

#define LED_GREEN								(*((volatile unsigned long *)(PORTF|GREEN)))
#define LED_RED									(*((volatile unsigned long *)(PORTF|RED)))
#define LED_BLUE								(*((volatile unsigned long *)(PORTF|BLUE)))
#define LED_YELLOW							(*((volatile unsigned long *)(PORTF|YELLOW)))
#define LED_PINK								(*((volatile unsigned long *)(PORTF|PINK)))
#define LED_SKYBLUE							(*((volatile unsigned long *)(PORTF|SKYBLUE)))
#define LED_WHITE								(*((volatile unsigned long *)(PORTF|WHITE)))
#define LED_DARK								(*((volatile unsigned long *)(PORTF|DARK)))


#define SW1											!(*((volatile unsigned long *)(PORTF|(0x01<<6))))
#define SW2											!(*((volatile unsigned long *)(PORTF|(0x01<<2))))
#define SW3											(*((volatile unsigned long *)(PORTE|(0x01<<2))))
#define SW4											(*((volatile unsigned long *)(PORTE|(0x01<<3))))


struct io_T
{
  volatile unsigned long * ptrCOR;
	unsigned int tempo;
};

extern struct io_T led;

void PortF_Init(void);
void PortE_Init(void);
void PortD_Init(void);
void PortC_Init(void);
void busSpeedPLL( void );
void IO_Init( void );




#endif //__IO_H__
