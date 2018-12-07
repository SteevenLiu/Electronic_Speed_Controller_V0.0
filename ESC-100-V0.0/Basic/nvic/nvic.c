// -----------------------------------------------------------
// FILE: nvic.c
//
// Description: this is a template for newly created .c files
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
   # include "nvic.h"

//
// 2nd. variables
// -----------------------------------------------------------

//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
// 1.NVIC configuration for USART1
// ...........................................................
   /**
   @brief Configure NVIC for USART1.
   @param None.
   @retval None.
   */
   void NVIC_Configuration_USART1(void)
   {
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;    // Pre-emption Priority 1
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		       // SubPriority 3
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // IRQ enable
     NVIC_Init(&NVIC_InitStructure);
	 }
//
// 2.NVIC configuration for TIM 8 update interrupt
// ...........................................................
   /**
   @brief Configure NVIC for TIM 8 update interrupt.
   @param None.
   @retval None.
   */
   void NVIC_Configuration_TIM8_Update(void)
   {
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; // Pre-emption Priority 0
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	     // SubPriority 0
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         // IRQ enable
     NVIC_Init(&NVIC_InitStructure);
   }
//
// 3.NVIC configuration for TIM 1 capture interrupt
// ...........................................................
   /**
   @brief Configure NVIC for TIM 1 capture interrupt.
   @param None.
   @retval None.
   */
   void NVIC_Configuration_TIM1_Capture(void)
   {
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; // Pre-emption Priority 1
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	     // SubPriority 3
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         // IRQ enable
     NVIC_Init(&NVIC_InitStructure);
   }
//
// 4.NVIC configuration for ADC1 and ADC2
// ...........................................................
   /**
   @brief Configure NVIC for ADC1 and ADC2.
   @param None.
   @retval None.
   */
   void NVIC_Configuration_ADC1_2(void)
   {
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; // Pre-emption Priority 1
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	     // SubPriority 3
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         // IRQ enable
     NVIC_Init(&NVIC_InitStructure);
   }
//
// 4.NVIC configuration for SysTick
// ...........................................................
// /**
// @brief Configure NVIC for SysTick.
// @param None.
// @retval None.
// */
//   void NVIC_Configuration_SysTick(void)
//   {
//     NVIC_InitTypeDef NVIC_InitStructure;
//     NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;    // Pre-emption Priority 3
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		       // SubPriority 3
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // IRQ enable
//     NVIC_Init(&NVIC_InitStructure);
//	 }
// no more.
// -----------------------------------------------------------

