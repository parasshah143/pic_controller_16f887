/******************************************************************************
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
/*****************************************************************************************/

// Header:     Home Automation using PC & microcontroller PIC16F887
// File Name:  usart_test.c
// Author:     TARAL SHAH
// Date:       06/08/14

/*****************************************************************************************

                                     NOTICE

NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM THE AUTHOR. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
Taral Shah
taralshah.shah@gmail.com


 * //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

/*******************************************************************************/
///////////////////////Include Section/////////////////////////////////////////////////////

#include <xc.h>
#include <GenericTypeDefs.h>
#include "usart_pic16.h"
#include <string.h>
#include "LCD.h"
// Configuration Byte
#pragma config FOSC = HS// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define BUZ RC4

void main()
{
  //Initialize USART with baud rate 9600
	unsigned int i = 1;
	unsigned int j = 0;
    unsigned char p[10]= "meera";
    unsigned char m[10];
    unsigned int k = 0;
    unsigned int mflag = 0;
    
    TRISD = 0x00;
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC4 = 0;
	USARTInit(9600);
	LCDEnable();
	__delay_ms(1000);
	LCDInitialize();
	__delay_ms(1000);
	LCDWriteString("welcome");
	__delay_ms(1000);
	USARTWriteString("Hii.. Bluetooth is ready\r\n");
	LCDClear();
	__delay_ms(100);

  while(1)
  {
      //Get the amount of data waiting in USART queue
      uint8_t n= USARTDataAvailable();

      //If we have some data
      if(n!=0)
      {
          //Read it

         char ch=USARTReadData();
		 if((i%16) == 0)
		 {
			 if(j == 0)
			 {
				 LCDRow2();
				 j = 1;
			 }
			 else if (j == 1)
			 {
				 LCDRow1();
				 LCDClear();
				 __delay_ms(2);
				 j = 0;
			 }
		}
		 if((ch!='\r') || (ch!='\n'))
		 {
		LCDWriteData(ch);
		 i++;
		 }
         if(mflag)
         {
          m[k] = ch;
         k++;
         USARTWriteChar(k+48);
         if (k >= 6)
         {
//             USARTWriteChar(m[0]);
//              USARTWriteChar(m[1]);
//               USARTWriteChar(m[2]); 
//               USARTWriteChar(m[3]);
//                USARTWriteChar(m[4]);
             USARTWriteString(m);
             USARTWriteString("\r\n");
             if(strncmp(m,p,5) == 0)
             {
                 BUZ = 1;
                 for(int x = 0; x<=6; x++)
                     m[x] = 0;
             }
             k = 0;
         mflag = 0;
         }
   
         }
         if(ch == 'm')
         {
             m[k] = ch;
             mflag++;
             k++;
             USARTWriteString("Flagset");
             BUZ = 0;
         }

    }
}


}