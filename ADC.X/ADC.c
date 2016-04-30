/* 
 * File:   ADC.c
 * Author: Dell
 *
 * Created on 15 May, 2014, 1:57 PM
 */
#include<xc.h>
#include "usart_pic16.h"

#pragma config FOSC = HS // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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
#define _XTAL_FREQ 16000000

void ADC_Init()
{
   ADCON0 = 0xC1;
   ADCON1 = 0x80;
}

unsigned int ADC_Read(unsigned char channel)
{

  ADCON0bits.CHS=channel;

  //Wait for aquisition
  __delay_us(100);

  //Start Conversion
  ADCON0bits.GO=1;
  //Wait for the conversion to complete
  while(ADCON0bits.GO);

  return ((ADRESH<<8)+ADRESL);
}

void main()
{
	  USARTInit(9600);
	  __delay_ms(10);

	unsigned long ADC_value = 0;
	unsigned int digit1, digit2, digit3, digit4;
	TRISB = 0x00;
    TRISC = 0x00;
    ADC_Init();
	USARTWriteString("Checking");
 
   while(1)
   {
     ADC_value = (ADC_Read(0)/2)-1;
//     PORTB = a;
     PORTC = ADC_value;
     __delay_ms(100);
		digit1 = (unsigned int)(ADC_value/1000);									 // Calculate digit1 of ADC_value
		digit2 = (unsigned int)((ADC_value - digit1*1000)/100);						 // Calculate digit2 of ADC_value
		digit3 = (unsigned int)((ADC_value - (digit1*1000+digit2*100))/10);			 // Calculate digit3 of ADC_value
		digit4 = (unsigned int)(ADC_value - (digit1*1000+digit2*100+digit3*10));	 // Calculate digit4 of ADC_value

		USARTWriteChar(digit1+0x30);		// Display digit1 of ADC_value on LCD
		__delay_ms(1);
		USARTWriteChar(digit2+0x30);		// Display digit2 of ADC_value on LCD
		__delay_ms(1);
		USARTWriteChar(digit3+0x30);		// Display digit3 of ADC_value on LCD
		__delay_ms(1);
		USARTWriteChar(digit4+0x30);		// Display digit4 of ADC_value on LCD
		__delay_ms(1);
        USARTWriteChar(0xF8);               // to print oC symbol
        USARTWriteString("C (Temperature in celsius)");
		USARTWriteString(" \r");		// Display digit4 of ADC_value on LCD
		__delay_ms(1000);
   }
 }