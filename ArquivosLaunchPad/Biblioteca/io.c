#include "io.h"

struct io_T led;


void PortF_Init(void)																// PortF: MSB xxxIOOOI LSB
{ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     								// 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           								// allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   								// 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           								// allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        								// 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   								// 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          								// 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        								// 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          								// enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          								// 7) enable digital I/O on PF4-0
}

void PortE_Init(void)																// PortE: MSB xxxxxxII LSB
{ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;     								// 1) activate clock for Port E
  delay = SYSCTL_RCGC2_R;           								// allow time for clock to start
  GPIO_PORTE_LOCK_R = 0x4C4F434B;   								// 2) unlock GPIO Port E
  GPIO_PORTE_CR_R = 0x1F;           								// allow changes to PE4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTE_AMSEL_R = 0x00;        								// 3) disable analog on PF
  GPIO_PORTE_PCTL_R = 0x00000000;   								// 4) PCTL GPIO on PE4-0
  GPIO_PORTE_DIR_R = 0x00;          								// 5) PE7-0 in
  GPIO_PORTE_AFSEL_R = 0x00;        								// 6) disable alt funct on PE7-0
  GPIO_PORTE_PDR_R = 0x03;          								// enable pull-down on PE0 and PE1
  GPIO_PORTE_DEN_R = 0x03;          								// 7) enable digital I/O on PE1-0
}

void PortD_Init(void)																// PortD: 
{ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000008;     								// 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;           								// allow time for clock to start
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   								// 2) unlock GPIO Port D
  GPIO_PORTD_CR_R = 0x1F;           								// allow changes to PD4-0
  GPIO_PORTD_AMSEL_R = 0x00;        								// 3) disable analog on PD
  GPIO_PORTD_PCTL_R = 0x00000000;   								// 4) PCTL GPIO on PD4-0
  GPIO_PORTD_DIR_R = 0x08;          								// 5) PD3 out/in One-Wire
  GPIO_PORTD_AFSEL_R = 0x00;        								// 6) disable alt funct on PD7-0
  GPIO_PORTD_PUR_R = 0x08;          								// enable pull-down on PD3
  GPIO_PORTD_DEN_R = 0x08;          								// 7) enable digital I/O on PD3
}

void PortC_Init_off(void)																// PortC: 
{ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000004;     								// 1) activate clock for Port C
  delay = SYSCTL_RCGC2_R;           								// allow time for clock to start
  GPIO_PORTC_LOCK_R = 0x4C4F434B;   								// 2) unlock GPIO Port C
  GPIO_PORTC_CR_R = 0x20; 			     								// allow changes to PC7-4 OBS.: PC3-0 JTAG/SWD pins 
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTC_AMSEL_R = 0x0F;        								// 3) disable analog on PC
  GPIO_PORTC_PCTL_R = 0x00001111;   								// 4) PCTL GPIO on PC4-0
  GPIO_PORTC_DIR_R = 0xF0;          								// 5) PC5 pin EN Bluetooth
  GPIO_PORTC_AFSEL_R = 0x0F;        								// 6) disable alt funct on PC7-0
  GPIO_PORTC_PUR_R = 0x0F;          								// enable pull-down on PC5
  GPIO_PORTC_DEN_R = 0xFF;          								// 7) enable digital I/O on PC5
	// Table 10.7 GPIO Pins With Special Consideration
}
void PortC_Init(void)																// PortC: 
{ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000004;     								// 1) activate clock for Port C
  delay = SYSCTL_RCGC2_R;           								// allow time for clock to start
  GPIO_PORTC_CR_R = 0x20; 			     								// allow changes to PC7-4 OBS.: PC3-0 JTAG/SWD pins 
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTC_AMSEL_R = 0x00;        								// 3) disable analog on PC
  GPIO_PORTC_PCTL_R &= 0xFF0FFFFF;   								// 4) PCTL GPIO on PC4-0
  GPIO_PORTC_DIR_R |= 0x20;          								// 5) PC5 pin EN Bluetooth
  GPIO_PORTC_AFSEL_R &= ~0x20;        								// 6) disable alt funct on PC7-0
  GPIO_PORTC_DEN_R |= 0x20;          								// 7) enable digital I/O on PC5
	// Table 10.7 GPIO Pins With Special Consideration
}



void busSpeedPLL( void )														// MainOSC 16MHz
{
	SYSCTL_RCC_R = 0x00000000;
	SYSCTL_RCC_R =  (unsigned long)
									(
										SYSCTL_RCC_XTAL_16MHZ |  				// 16 MHz
										//SYSCTL_RCC_MOSCDIS |     			// Main Oscillator Disable
										SYSCTL_RCC_OSCSRC_MAIN | 				// MOSC
										SYSCTL_RCC_PWRDN |        			// PLL Power Down
										SYSCTL_RCC_BYPASS |      				// PLL Bypass
										//SYSCTL_RCC_USESYSDIV |    		// Enable System Clock Divider
										(0x15<<SYSCTL_RCC_SYSDIV_S)  		// System Divisor: n << Bit Number : 1 <= n <= 16
								  );
}


void IO_Init( void )
{
	busSpeedPLL();
	PortF_Init();
	PortE_Init();
	PortD_Init();
	PortC_Init();

//  ADC0_InitSWTriggerSeq3_Ch1();
//	SysTick_Init_ms( 1 );
//  UART_Init_16MHz();
//	Nokia5110_Init();
//  Nokia5110_PrintBMP( 0, 47, jwrp, 0 );
// 	Nokia5110_DisplayBuffer();
//	SysTickWaitBusy( 3 );

//	Nokia5110_PrintBMP( 0, 47, cruzamento, 0 );
// 	Nokia5110_DisplayBuffer();
}

	
