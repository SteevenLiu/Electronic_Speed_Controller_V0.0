// -----------------------------------------------------------
// FILE: ESC_ISRs_USART1.c
//
// Description: USART 1 interrupt service routine.
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_ISRs_USART1.h"

// 2nd.funcions
// -----------------------------------------------------------
// 1.USART1 interrupt service routine(ISR)
// ...........................................................
// @ brief ISR service routine.
// @ param None.
// @ retval None.
//
   void USART1_IRQHandler(void)
   {
     StdSci_Receive_in_ISR(USART1);
		 
//   USART_ClearITPendingBit ( USART1,USART_IT_WU);
//   USART_ClearITPendingBit (USART_IT_CM);
//   USART_ClearITPendingBit (USART_IT_EOB); 
//   USART_ClearITPendingBit (USART_IT_RTO);
//   USART_ClearITPendingBit (USART_IT_PE);
//   USART_ClearITPendingBit (USART_IT_TXE);
//   USART_ClearITPendingBit (USART_IT_TC);
//   USART_ClearITPendingBit (USART_IT_RXNE);
//   USART_ClearITPendingBit (USART_IT_IDLE);
//   USART_ClearITPendingBit (USART_IT_LBD);
//   USART_ClearITPendingBit (USART_IT_CTS);
//   USART_ClearITPendingBit (USART_IT_ERR);
//   USART_ClearITPendingBit (USART_IT_ORE);
//   USART_ClearITPendingBit (USART_IT_NE);
//   USART_ClearITPendingBit (USART_IT_FE);
   }

// no more.
// -----------------------------------------------------------

