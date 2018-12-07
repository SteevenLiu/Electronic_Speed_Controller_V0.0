// -----------------------------------------------------------
// FILE: hall.c
//
// Description: Hall I/O driver.
//
// -----------------------------------------------------------
// Release Date: 2018-09-10;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "hall.h"
//
// 2nd. variables
// -----------------------------------------------------------

//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
// 1.function 1
// ...........................................................
   /**
   @brief This is the discription of function 1.
   @param argument1: This is the discription of argument 1.
   @param argument2: This is the discription of argument 2.
   @param argument3: This is the discription of argument 3.
   @retval This is the discription of the return value.
   */
   void Hall_Sink_Init(void)
   {
//   Parameter Declarations
//   .........................................................
     GPIO_InitTypeDef          GPIO_InitStruct;

//   IO Port configuration
//   .........................................................
//   enable clock for GPIO portA, GPIO portB, AFIO
     RCC_AHBPeriphClockCmd(RCC_Hall_A,ENABLE);
     RCC_AHBPeriphClockCmd(RCC_Hall_B,ENABLE);
     RCC_AHBPeriphClockCmd(RCC_Hall_C,ENABLE);

//   configure pin mode as GPIO input
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//   configure pin speed as 50MHz
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//   enable internal Pll-Up
     GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
   
     GPIO_InitStruct.GPIO_Pin = Pin_Hall_A;  // Hall_A
     GPIO_Init(Port_Hall_A,&GPIO_InitStruct);

     GPIO_InitStruct.GPIO_Pin = Pin_Hall_B;  // Hall_B
     GPIO_Init(Port_Hall_B,&GPIO_InitStruct);

     GPIO_InitStruct.GPIO_Pin = Pin_Hall_C;  // Hall_C
     GPIO_Init(Port_Hall_C,&GPIO_InitStruct);
   }
 
// 2.function 2
// ...........................................................
   /**
   @brief This is the discription of function 1.
   @param argument1: This is the discription of argument 1.
   @param argument2: This is the discription of argument 2.
   @param argument3: This is the discription of argument 3.
   @retval This is the discription of the return value.
   */
   u8 Get_Hall(void)
   {
     u8 hall;
   # if ORNT_CLOCKWISE
     hall  = (GPIO_ReadInputDataBit(Port_Hall_A, Pin_Hall_A)<<2);
     hall |= (GPIO_ReadInputDataBit(Port_Hall_B, Pin_Hall_B)<<1);
     hall |=  GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_C);
   # else
     hall  = ((GPIO_ReadInputDataBit(Port_Hall_A, Pin_Hall_C))<<2);
     hall |= ((GPIO_ReadInputDataBit(Port_Hall_B, Pin_Hall_B))<<1);
     hall |= GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_A);
   # endif

//     hall = (~hall) & 0x07; //optc
		 
     return hall;
   }	
	 
// no more.
// -----------------------------------------------------------

