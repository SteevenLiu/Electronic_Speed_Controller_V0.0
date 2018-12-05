// -----------------------------------------------------------
// FILE: ESC_ISRs_TIM8.c
//
// Description: Timer 8 interrupt service routine.
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_ISRs_TIM8.h"
//
// 2nd. variables
// -----------------------------------------------------------

//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
	 u16 cntr_mid;
	 u16 cntr_out;

   void TIM8_UP_IRQHandler(void)
   {
     STDSCI_BLOCK_TX* btx_ptr;
     btx_ptr = &block_tx;

     ESC_Observer_Hall();

		 control_state_machine();

		 TIM_ClearITPendingBit(TIM8, TIM_IT_Update); //clear pending bit.

		 cntr_mid = (u16)TIM_GetCounter(TIM8);
		 cntr_out = (u16)TIM_GetCounter(TIM8);

//		 feedback_CodeEfficiency_SMC = (cntr_in>cntr_out)? (1200-cntr_out):cntr_out;
		 feedback_CodeEfficiency_SMC = (cntr_out>cntr_mid)? cntr_out:(2400-cntr_out);
     SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xC0), feedback_CodeEfficiency_SMC);
	 }

// no more.
// -----------------------------------------------------------

