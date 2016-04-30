/******************************************************************************

 Temperature Sensor LM35 calculation functions for PIC16F series MCUs.

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
#include <stdint.h>

#include "ADC.h"
#include "lm35_pic16.h"


float LM35ReadTemp()
{
    //Temperature
    float t;

    //Read ADC
    uint16_t adc_value=ADC_Read(LM35_ADC_CH);
    __delay_us(100);

    adc_value+=ADC_Read(LM35_ADC_CH);
    __delay_us(100);

     adc_value+=ADC_Read(LM35_ADC_CH);
    __delay_us(100);

    adc_value=adc_value/3;

    //Convert to degree Centrigrade
    t=((adc_value/1023.00)*500.00);

    return t;
}

