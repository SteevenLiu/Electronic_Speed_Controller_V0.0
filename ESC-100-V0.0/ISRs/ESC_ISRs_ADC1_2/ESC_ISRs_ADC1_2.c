// -----------------------------------------------------------
// FILE: ESC_ISRs_ADC1_2.c
//
// Description: ...
//
// -----------------------------------------------------------
// Release Date: 2018-mm-dd;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
   # include "ESC_ISRs_ADC1_2.h"

//
// 2nd. variables
// -----------------------------------------------------------
//   u16 cntr_TIM8 = 0;
//   u16 jDR1 = 0;
     u16 DR=0;
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
	 void ADC1_2_IRQHandler(void)
	 {
     BLDCM_Controller* motor_ptr;
     motor_ptr = &bldcm_m1;

     STDSCI_BLOCK_TX* btx_ptr;
     btx_ptr = &block_tx;

//     if(ADC_GetITStatus(ADC1, ADC_IT_AWD1))
//		 {
//       pwm_disable();
//       main_machine_state = STATE_MAIN_FAULT;
//       control_machine_state = STATE_CONTROL_IDLE;
//       motor_ptr->app_status |= status_over_current;			 
// 
//		   ADC_ClearITPendingBit(ADC1, ADC_IT_AWD1);
//		 }

//     if(ADC_GetCommonFlagStatus(ADC2, ADC_FLAG_SLVAWD1))
//		 {
//		   ADC_ClearITPendingBit(ADC2, ADC_IT_AWD1);
//		 }
//		 
//		 if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
//     {
//			 cntr_TIM8 = (u16)TIM_GetCounter(TIM8);
//       ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
//		 }
		 
//     if(ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOS))
//     {
//       jDR1 = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1);
//       ADC_ClearITPendingBit(ADC1, ADC_IT_JEOS);
//		 }

     if(ADC_GetITStatus(ADC1,ADC_IT_EOS))
     {
       motor_ptr->Ibus_ADC = ADC_GetConversionValue(ADC1);
       ADC_ClearITPendingBit(ADC1, ADC_IT_EOS);
		 }

     if(ADC_GetITStatus(ADC2,ADC_IT_EOS))
     {
       motor_ptr->Ibus_ADC = ADC_GetConversionValue(ADC2);
       ADC_ClearITPendingBit(ADC2, ADC_IT_EOS);
		 }
//   if(ADC_GetITStatus(ADC1,ADC_IT_JEOS))
//   {
//     jDR1 = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1);
//     ADC_ClearITPendingBit(ADC1, ADC_IT_JEOS);
//     ADC_StartInjectedConversion(ADC1);
//   }
		 
     SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0x91), motor_ptr->Ibus_ADC);
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
   /*write function 2 here*/

// ...

// no more.
// -----------------------------------------------------------

