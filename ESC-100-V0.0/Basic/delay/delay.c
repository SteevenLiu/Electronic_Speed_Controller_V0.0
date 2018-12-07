// -----------------------------------------------------------
// FILE: delay.c
//
// Description: Delay methods.
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "delay.h"

//
// 2nd.funcions
// -----------------------------------------------------------
// 1.microsecond (us) level delay method
// ...........................................................
// @ brief Delay x us.
// @ param us: time scale (us) to be delayed.
//             uS<233016
// @ retval None.
//
   void delay_us(u32 us)
   {
     SysTick->LOAD=AHB_INPUT*us;  // reload
     SysTick->VAL=0x00;           // clear counter
     SysTick->CTRL=0x00000005;    // set clock source as HCLK
     while(!(SysTick->CTRL&0x00010000)); // wait until counter is 0
     SysTick->CTRL=0x00000004;    // close counter
   }

// 2.millisecond (ms) level delay method
// ...........................................................
// @ brief Delay x ms.
// @ param ms: Time scale (ms) to be delayed.
//             ms < 65535
// @ retval None.
//
   void delay_ms(u16 ms)
   {
     while( ms-- != 0)
     {
       delay_us(1000);
     }
   }

// 3.second level delay method
// ...........................................................
// @ brief Delay x s.
// @ param s: Time scale (s) to be delayed.
//            s < 65535
// @ retval None.
//
   void delay_s(u16 s)
   {
     while( s-- != 0)
     {
       delay_ms(1000);
     }
   }

// no more.
// -----------------------------------------------------------

