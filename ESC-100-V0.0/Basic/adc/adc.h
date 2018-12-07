// -----------------------------------------------------------
// FILE: adc.h
//
// Description: This is a template for newly created .h files.
//
// -----------------------------------------------------------
// Release Date: 2018-mm-dd;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __ADC_H
#define __ADC_H
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"
 # include "delay.h"
//
// 2nd.datatypes
// -----------------------------------------------------------
   /**
   @brief
   */
   /* define types here */

//
// 3rd. variables
// -----------------------------------------------------------
   /* define variables here */

//
// 4th.function prototypes
// -----------------------------------------------------------
   void ADC_DMA_Init(void);
   void ADC_GPIO_Init(void);
   void ADC_Configuration_ADC1(void);
   void ADC_Configuration_ADC2(void);

#endif/*#ifndef __ADC_H*/
// no more.
// ----------------------------------------------------------- 

