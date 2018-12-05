// -----------------------------------------------------------
// FILE: delay.h
//
// Description: Delay methods header.
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __DELAY_H
#define __DELAY_H
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"
 # define AHB_INPUT 72 //72 Mhz system clock

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
   void delay_s(u16 s);
   void delay_ms(u16 ms);
   void delay_us(u32 us);

#endif/*#ifndef __DELAY_H*/
// no more.
// ----------------------------------------------------------- 

