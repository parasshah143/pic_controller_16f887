/******************************************************************************

 ADC functions library for PIC16F series MCUs.

 Compiler: Microchip XC8 v1.12 (http://www.microchip.com/xc)

 MCU: PIC16F877A
 Frequency: 20MHz

                                     NOTICE

NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
TARAL SHAH
taralshah.shah@gmail.com

*******************************************************************************/
#include <xc.h>
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


