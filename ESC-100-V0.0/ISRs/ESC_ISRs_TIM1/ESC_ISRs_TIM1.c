// -----------------------------------------------------------
// FILE: ESC_ISRs_TIM1.c
//
// Description: Timer 1 interrupt service routine.
//
// -----------------------------------------------------------
// Release Date: 2018-09-07;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_ISRs_TIM1.h"

//
// 2nd. variables
// -----------------------------------------------------------
   u32 d_Cap = 0;
   u32 t_Cap_Rising = 0;
   u32 t_Cap_Falling = 0;
//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
// 1.TIM1 capture Interrupt Service Routine (ISR)
// ...........................................................
// @ brief ISR for TIM1 capture.
// @ param None.
// @ retval None.
//
   void TIM1_CC_IRQHandler(void)
   {
//   CC1 capture falling edge, i.e. PWM rising edge, which is inverted by optocoupler.
     if(TIM_GetFlagStatus(TIM1, TIM_FLAG_CC1) == SET)
     {
			 t_Cap_Rising = TIM_GetCapture1(TIM1);
			 
       TIM_ClearFlag(TIM1,TIM_FLAG_CC1);
       TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
     }

//   CC1 capture rising edge, i.e. PWM falling edge, which is inverted by optocoupler.
     if(TIM_GetFlagStatus(TIM1, TIM_FLAG_CC2) == SET)
     {
			 t_Cap_Falling = TIM_GetCapture2(TIM1);
			 
			 if (t_Cap_Falling>t_Cap_Rising)
       {
         d_Cap = t_Cap_Falling - t_Cap_Rising;
			 }
       else
       {
         d_Cap = t_Cap_Falling - t_Cap_Rising + ARR_PWM_CAP;
			 }

       TIM_ClearFlag(TIM1,TIM_FLAG_CC2);
       TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
     }		 
   }
//
// 2.PWM in duty get method
// ...........................................................
// @ brief Get captured duty.
// @ param None.
// @ retval Captured duty.
//
   u32 Get_d_Cap(void) {return d_Cap;}
	 
// no more.
// -----------------------------------------------------------

