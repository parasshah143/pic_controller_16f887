/******************************************************************************

 16x2 LCD library for PIC16F series MCUs.

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
#include "LCD.h"

inline void  LCDEnable(void)
{
    LCDEnablePin = HIGH;
    Delay(10);
    LCDEnablePin = LOW;
}
void LCDWriteCommand(LCDubyte LCDData)
{
    LCDRegisterSelectPin = LOW;
    LCDWriteByte(LCDData);
}

void LCDWriteData(LCDubyte LCDData)
{
    LCDRegisterSelectPin = HIGH;
    LCDWriteByte(LCDData);
}

void LCDWriteString(const char *lcd_string)
{
   while(*lcd_string)
   {
      LCDWriteData(*lcd_string++);
   }
}

void LCDWriteString1(volatile char *lcd_string)
{
   while(*lcd_string)
   {
      LCDWriteData(*lcd_string++);
   }
}

void LCDWriteStringWithLength (volatile unsigned char * str, unsigned char length)
{
	while ((length--) && (*str !=	0x0d))
	LCDWriteData(*str++); //send characters one by one
}

void LCDInitialize(void)
{
    LCD_DDR = LCD_DDR & 0x03;
    LCDEnablePin   = OUTPUTPIN;
    LCDRegisterSelectPin = OUTPUTPIN;
    LCDDataPort    &=  0x0f;
    LCDReset();
    LCDWriteCommand(0x28);
    LCDWriteCommand(0x0C);
    LCDWriteCommand(0x06);
    LCDWriteCommand(0x01);

}

void LCDReset(void)
{
   LCDWriteCommand(0x33);
   LCDWriteCommand(0x33);
   LCDWriteCommand(0x32);
}

void  LCDWriteByte(LCDubyte  LCDData)
{
    LCDDataPort = (LCDDataPort & 0x0F)|(LCDData & 0xF0);
    LCDEnable();
    LCDDataPort = (LCDDataPort & 0x0F)|(LCDData << 4);
    LCDEnable();
    Delay(5);
}

void LCDDisplayByte(LCDubyte LCDAdress, LCDubyte Value)
{
    LCDWriteCommand(LCDAdress);
    if(( Value / 100 ) == 0)
       LCDWriteData(0x20);         //put space
     else
       LCDWriteData((Value / 100) | 0x30);

       if(((Value % 100) / 10) == 0)
       if(( Value / 100 ) == 0)
          LCDWriteData(0x20);
      else
          LCDWriteData(((Value % 100) / 10) | 0x30);
     else
       LCDWriteData(((Value % 100) / 10) | 0x30);

    LCDWriteData((Value % 10) | 0x30);
}