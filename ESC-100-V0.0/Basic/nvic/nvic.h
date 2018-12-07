// -----------------------------------------------------------
// FILE: nvic.h
//
// Description: 
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include"ESC_Device.h"
//
// 2nd.datatypes
// -----------------------------------------------------------
// # ifndef _MACRONAME_DATATYPES
// # define _MACRONAME_DATATYPES
//   /* define types here */
// # endif

//
// 3rd. variables
// -----------------------------------------------------------
// # ifndef _MACRONAME_VARIABLES
// # define _MACRONAME_VARIABLES
//   /* define variables here */
// # endif

//
// 4th.function prototypes
// -----------------------------------------------------------
   void NVIC_Configuration_USART1(void);
   void NVIC_Configuration_TIM8_Update(void);
	 void NVIC_Configuration_TIM1_Capture(void);
	 void NVIC_Configuration_ADC1_2(void);

// no more.
// -----------------------------------------------------------/
