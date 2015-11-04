// UART2.c
// Runs on LM3S811, LM3S1968, LM3S8962, LM4F120, TM4C123
// Simple device driver for the UART.
// Daniel Valvano
// September 11, 2013
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
   Program 4.12, Section 4.9.4, Figures 4.26 and 4.40

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// U0Rx (VCP receive)  connected to PD6
// U0Tx (VCP transmit) connected to PD7
#include "tm4c123gh6pm.h"
#include "UART2.h"

//------------UART2_Init------------
// Initialize the UART for 115,200 baud rate (assuming 50 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART2_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART2; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
  UART2_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART2_IBRD_R = 27;                    // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
  UART2_FBRD_R = 8;                     // FBRD = int(0.1267 * 64 + 0.5) = 8
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART2_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART2_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTD_AFSEL_R |= 0xC0;           // enable alt funct on PD7-7
  GPIO_PORTD_DEN_R |= 0xC0;             // enable digital I/O on PD7-6
                                        // configure PD7-6 as UART
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000;
  GPIO_PORTD_AMSEL_R &= ~0xC0;          // disable analog functionality on PD
}

//------------UART_Init_16MHz_9600bps------------
// Initialize the UART for 9600 baud rate (assuming 16 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART2_Init_16MHz_9600bps(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART2; // activate UART2
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
  UART2_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART2_IBRD_R = 104;                   // IBRD = int(16,000,000 / (16 * 9600)) = int(104.1667)
  UART2_FBRD_R = 11;                    // FBRD = int(0.1667 * 64 + 0.5) = 11
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART2_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART2_CTL_R |= (UART_CTL_UARTEN);       // enable UART
  
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   								// 2) unlock GPIO Port D
	GPIO_PORTD_CR_R |= 0xC0;
	
	GPIO_PORTD_AFSEL_R |= 0xC0;           // enable alt funct on PD7-7
  GPIO_PORTD_DEN_R |= 0xC0;             // enable digital I/O on PD7-6
                                        // configure PD7-6 as UART
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000;
  GPIO_PORTD_AMSEL_R &= ~0xC0;          // disable analog functionality on PD
}

void UART2_Init_16MHz_38400bps(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART2; // activate UART2
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
  UART2_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART2_IBRD_R = 26;                    // IBRD = int(16,000,000 / (16 * 38400)) = int(26.0416667)
  UART2_FBRD_R =  3;                    // FBRD = int(0.1667 * 64 + 0.5) = 3.16666
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART2_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART2_CTL_R |= (UART_CTL_UARTEN);       // enable UART
  
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   								// 2) unlock GPIO Port D
	GPIO_PORTD_CR_R |= 0xC0;
	
	GPIO_PORTD_AFSEL_R |= 0xC0;           // enable alt funct on PD7-7
  GPIO_PORTD_DEN_R |= 0xC0;             // enable digital I/O on PD7-6
                                        // configure PD7-6 as UART
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000;
  GPIO_PORTD_AMSEL_R &= ~0xC0;          // disable analog functionality on PD
}


unsigned char UART2_InCharAvailable( void )
{
  return( !(UART2_FR_R&UART_FR_RXFE) );
}


//------------UART2_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART2_InChar(void){
  while((UART2_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART2_DR_R&0xFF));
}
//------------UART2_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART2_OutChar(unsigned char data){
  while((UART2_FR_R&UART_FR_TXFF) != 0);
  UART2_DR_R = data;
}


//------------UART2_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART2_OutString(char *pt){
  while(*pt){
    UART2_OutChar(*pt);
    pt++;
  }
}

//------------UART2_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
unsigned long UART2_InUDec(void){
unsigned long number=0, length=0;
char character;
  character = UART2_InChar();
  while(character != CR){ // accepts until <enter> is typed
// The next line checks that the input is a digit, 0-9.
// If the character is not 0-9, it is ignored and not echoed
    if((character>='0') && (character<='9')) {
      number = 10*number+(character-'0');   // this line overflows if above 4294967295
      length++;
      UART2_OutChar(character);
    }
// If the input is a backspace, then the return number is
// changed and a backspace is outputted to the screen
    else if((character==BS) && length){
      number /= 10;
      length--;
      UART2_OutChar(character);
    }
    character = UART2_InChar();
  }
  return number;
}

//-----------------------UART2_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void UART2_OutUDec(unsigned long n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    UART2_OutUDec(n/10);
    n = n%10;
  }
  UART2_OutChar(n+'0'); /* n is between 0 and 9 */
}

//---------------------UART2_InUHex----------------------------------------
// Accepts ASCII input in unsigned hexadecimal (base 16) format
// Input: none
// Output: 32-bit unsigned number
// No '$' or '0x' need be entered, just the 1 to 8 hex digits
// It will convert lower case a-f to uppercase A-F
//     and converts to a 16 bit unsigned number
//     value range is 0 to FFFFFFFF
// If you enter a number above FFFFFFFF, it will return an incorrect value
// Backspace will remove last digit typed
unsigned long UART2_InUHex(void){
unsigned long number=0, digit, length=0;
char character;
  character = UART2_InChar();
  while(character != CR){
    digit = 0x10; // assume bad
    if((character>='0') && (character<='9')){
      digit = character-'0';
    }
    else if((character>='A') && (character<='F')){
      digit = (character-'A')+0xA;
    }
    else if((character>='a') && (character<='f')){
      digit = (character-'a')+0xA;
    }
// If the character is not 0-9 or A-F, it is ignored and not echoed
    if(digit <= 0xF){
      number = number*0x10+digit;
      length++;
      UART2_OutChar(character);
    }
// Backspace outputted and return value changed if a backspace is inputted
    else if((character==BS) && length){
      number /= 0x10;
      length--;
      UART2_OutChar(character);
    }
    character = UART2_InChar();
  }
  return number;
}

//--------------------------UART2_OutUHex----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1 to 8 digits with no space before or after
void UART2_OutUHex(unsigned long number){
// This function uses recursion to convert the number of
//   unspecified length as an ASCII string
  if(number >= 0x10){
    UART2_OutUHex(number/0x10);
    UART2_OutUHex(number%0x10);
  }
  else{
    if(number < 0xA){
      UART2_OutChar(number+'0');
     }
    else{
      UART2_OutChar((number-0x0A)+'A');
    }
  }
}

//------------UART2_InString------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until <enter> is typed
//    or until max length of the string is reached.
// It echoes each character as it is inputted.
// If a backspace is inputted, the string is modified
//    and the backspace is echoed
// terminates the string with a null character
// uses busy-waiting synchronization on RDRF
// Input: pointer to empty buffer, size of buffer
// Output: Null terminated string
// -- Modified by Agustinus Darmawan + Mingjie Qiu --
void UART2_InString(char *bufPt, unsigned short max) {
int length=0;
char character;
  character = UART2_InChar();
  while(character != CR){
    if(character == BS){
      if(length){
        bufPt--;
        length--;
        UART2_OutChar(BS);
      }
    }
    else if(length < max){
      *bufPt = character;
      bufPt++;
      length++;
      UART2_OutChar(character);
    }
    character = UART2_InChar();
  }
  *bufPt = 0;
}
