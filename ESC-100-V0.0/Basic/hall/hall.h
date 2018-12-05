// -----------------------------------------------------------
// FILE: hall.h
//
// Description: Head file for hall.c.
//
// -----------------------------------------------------------
// Release Date: 2018-09-10;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __HALL_H
#define __HALL_H
//
// 1st.macros
// -----------------------------------------------------------
   # include "ESC_Device.h"
	 
   # define ORNT_CLOCKWISE 0

   # define RCC_Hall_A RCC_AHBPeriph_GPIOC
   # define RCC_Hall_B RCC_AHBPeriph_GPIOC
   # define RCC_Hall_C RCC_AHBPeriph_GPIOC

   # define Pin_Hall_A GPIO_Pin_13
   # define Pin_Hall_B GPIO_Pin_14
   # define Pin_Hall_C GPIO_Pin_15
                                      
   # define Port_Hall_A GPIOC
   # define Port_Hall_B GPIOC
   # define Port_Hall_C GPIOC

//
// 2nd.datatypes
// -----------------------------------------------------------
   /* define types here */

//
// 3rd. variables
// -----------------------------------------------------------
   /* define variables here */

//
// 4th.function prototypes
// -----------------------------------------------------------
   void Hall_Sink_Init(void);
   u8 Get_Hall(void);

#endif/*#ifndef __ESC_HALL_H*/
// no more.
// ----------------------------------------------------------- 

