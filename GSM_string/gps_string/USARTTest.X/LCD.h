#ifndef LCD_H
#define LCD_H


//INCLUDES
//#include "delay.h"

#define Delay(x) __delay_ms(x);
//DEFINE CONSTANT
#define LOW		0
#define HIGH	1
#define OUTPUTPIN 0


//DEFINES PORT/PINS
#define LCD_DDR					  TRISD
#define LCDEnablePin 		      RD3
#define LCDRegisterSelectPin      RD2
#define LCDDataPort			      PORTD

//DEFINE MACROS
#define LCDClear() LCDWriteCommand(0x01)	  /* Clear display LCD */
#define LCDRow1()  LCDWriteCommand(0x80)	  /* Begin at Line 1 */
#define LCDRow2()  LCDWriteCommand(0xC0)   /* Begin at Line 2 */

//USERDEFINE DATA TYPES
typedef unsigned char LCDubyte;

//DEFINE PROTOTYPES
inline void  LCDEnable(void);
void LCDWriteCommand(LCDubyte command);
void LCDWriteData(LCDubyte ascii);
void LCDWriteString(const char *lcd_string);
void LCDWriteString1(volatile char *lcd_string);
void LCDWriteStringWithLength (volatile unsigned char * str, unsigned char length);
void LCDWriteByte(LCDubyte  LCDData);
void LCDInitialize(void);
void LCDDisplayInitializing(void);
void LCDDisplayByte(LCDubyte LCDAdress, LCDubyte Value);
void LCDReset(void);

#endif

