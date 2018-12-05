// -----------------------------------------------------------
// FILE: Timer.h
// Description: Head file for timer driver.
//
// -----------------------------------------------------------
// Release Date: 2018-08-30;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __Timer_H
#define __Timer_H
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"
// 1.TIM1 I/O ports
// ...........................................................
   # define RCC_TIM1_CH1  RCC_AHBPeriph_GPIOA
//	 # define RCC_TIM1_CH2  RCC_AHBPeriph_GPIOx
//	 # define RCC_TIM1_CH3  RCC_AHBPeriph_GPIOx
//	 # define RCC_TIM1_CH4  RCC_AHBPeriph_GPIOx
//	 # define RCC_TIM1_CH1N RCC_AHBPeriph_GPIOx
//	 # define RCC_TIM1_CH2N RCC_AHBPeriph_GPIOx
//	 # define RCC_TIM1_CH3N RCC_AHBPeriph_GPIOx

   # define Pin_TIM1_CH1  GPIO_Pin_8  // TIM8_CH1
//   # define Pin_TIM1_CH2  GPIO_Pin_x  // TIM8_CH2
//   # define Pin_TIM1_CH3  GPIO_Pin_x  // TIM8_CH3
//   # define Pin_TIM1_CH4  GPIO_Pin_x  // TIM8_CH4
//   # define Pin_TIM1_CH1N GPIO_Pin_x  // TIM8_CH1N
//   # define Pin_TIM1_CH2N GPIO_Pin_x  // TIM8_CH2N
//   # define Pin_TIM1_CH3N GPIO_Pin_x  // TIM8_CH3N
                                      
   # define Port_TIM1_CH1  GPIOA  // TIM8_CH1
//   # define Port_TIM1_CH2  GPIOx  // TIM8_CH2
//   # define Port_TIM1_CH3  GPIOx  // TIM8_CH3
//	 # define Port_TIM1_CH4  GPIOx  // TIM8_CH4
//   # define Port_TIM1_CH1N GPIOx  // TIM8_CH1N
//   # define Port_TIM1_CH2N GPIOx  // TIM8_CH2N
//   # define Port_TIM1_CH3N GPIOx  // TIM8_CH3N
  
   # define AF_PinSource_TIM1_CH1  GPIO_PinSource8  // TIM8_CH1
//   # define AF_PinSource_TIM1_CH2  GPIO_PinSourcex  // TIM8_CH2
//   # define AF_PinSource_TIM1_CH3  GPIO_PinSourcex  // TIM8_CH3
//	 # define AF_PinSource_TIM1_CH4  GPIO_PinSourcex  // TIM8_CH4
//   # define AF_PinSource_TIM1_CH1N GPIO_PinSourcex  // TIM8_CH1N
//   # define AF_PinSource_TIM1_CH2N GPIO_PinSourcex  // TIM8_CH2N
//   # define AF_PinSource_TIM1_CH3N GPIO_PinSourcex  // TIM8_CH3N
  
   # define AF_TIM1_CH1  GPIO_AF_6   // TIM8_CH1
//   # define AF_TIM1_CH2  GPIO_AF_x  // TIM8_CH2
//   # define AF_TIM1_CH3  GPIO_AF_x  // TIM8_CH3
//	 # define AF_TIM1_CH4  GPIO_AF_x  // TIM8_CH4
//   # define AF_TIM1_CH1N GPIO_AF_x   // TIM8_CH1N
//   # define AF_TIM1_CH2N GPIO_AF_x   // TIM8_CH2N
//   # define AF_TIM1_CH3N GPIO_AF_x   // TIM8_CH3N 

// 2.TIM8 I/O ports
// ...........................................................
   # define Pin_TIM8_CH1  GPIO_Pin_6  // TIM8_CH1
   # define Pin_TIM8_CH2  GPIO_Pin_8  // TIM8_CH2
   # define Pin_TIM8_CH3  GPIO_Pin_9  // TIM8_CH3
   # define Pin_TIM8_CH1N GPIO_Pin_3  // TIM8_CH1N
   # define Pin_TIM8_CH2N GPIO_Pin_4  // TIM8_CH2N
   # define Pin_TIM8_CH3N GPIO_Pin_5  // TIM8_CH3N
                                      
   # define Port_TIM8_CH1  GPIOB  // TIM8_CH1
   # define Port_TIM8_CH2  GPIOB  // TIM8_CH2
   # define Port_TIM8_CH3  GPIOB  // TIM8_CH3
   # define Port_TIM8_CH1N GPIOB  // TIM8_CH1N
   # define Port_TIM8_CH2N GPIOB  // TIM8_CH2N
   # define Port_TIM8_CH3N GPIOB  // TIM8_CH3N
  
   # define AF_PinSource_TIM8_CH1  GPIO_PinSource6  // TIM8_CH1
   # define AF_PinSource_TIM8_CH2  GPIO_PinSource8  // TIM8_CH2
   # define AF_PinSource_TIM8_CH3  GPIO_PinSource9  // TIM8_CH3
   # define AF_PinSource_TIM8_CH1N GPIO_PinSource3  // TIM8_CH1N
   # define AF_PinSource_TIM8_CH2N GPIO_PinSource4  // TIM8_CH2N
   # define AF_PinSource_TIM8_CH3N GPIO_PinSource5  // TIM8_CH3N
  
   # define AF_TIM8_CH1  GPIO_AF_5   // TIM8_CH1
   # define AF_TIM8_CH2  GPIO_AF_10  // TIM8_CH2
   # define AF_TIM8_CH3  GPIO_AF_10  // TIM8_CH3
   # define AF_TIM8_CH1N GPIO_AF_4   // TIM8_CH1N
   # define AF_TIM8_CH2N GPIO_AF_4   // TIM8_CH2N
   # define AF_TIM8_CH3N GPIO_AF_3   // TIM8_CH3N

// 3.TIM2 I/O ports
// ...........................................................
   # define Pin_TIM2_CH1  GPIO_Pin_15  // TIM2_CH1
// # define Pin_TIM2_CH2  GPIO_Pin_?   // TIM2_CH2
   # define Pin_TIM2_CH3  GPIO_Pin_10  // TIM2_CH3
   # define Pin_TIM2_CH4  GPIO_Pin_3   // TIM2_CH4
                                      
   # define Port_TIM2_CH1  GPIOA  // TIM2_CH1
// # define Port_TIM2_CH2  GPIO?  // TIM2_CH2
   # define Port_TIM2_CH3  GPIOB  // TIM2_CH3
   # define Port_TIM2_CH4  GPIOA  // TIM2_CH4
  
   # define AF_PinSource_TIM2_CH1  GPIO_PinSource15  // TIM2_CH1
// # define AF_PinSource_TIM2_CH2  GPIO_PinSource?   // TIM2_CH2
   # define AF_PinSource_TIM2_CH3  GPIO_PinSource10  // TIM2_CH3
   # define AF_PinSource_TIM2_CH4  GPIO_PinSource3   // TIM2_CH4
  
   # define AF_TIM2_CH1  GPIO_AF_1   // TIM8_CH1
// # define AF_TIM2_CH2  GPIO_AF_1   // TIM8_CH2
   # define AF_TIM2_CH3  GPIO_AF_1   // TIM8_CH3
   # define AF_TIM2_CH4  GPIO_AF_1   // TIM8_CH4

// 2nd.function prototypes
// -----------------------------------------------------------
   void Timer1_PWM_Drive_Init(u16 arr, u16 psc, u16 mode_counter, \
                              u16 polarity_P, u16 polarity_N,     \
                              u16 deadtime);
	 
   void Timer8_PWM_Drive_Init(u16 arr, u16 psc, u16 mode_counter, \
                              u16 polarity_P, u16 polarity_N,     \
                              u16 deadtime);
	 
   void Timer2_PWM_Drive_Init(u16 arr, u16 psc, u16 mode_counter, \
                              u16 polarity);
	 
   void Timer3_PWM_Drive_Init(u16 arr, u16 psc);

   void Timer1_CAP_Sink_Init(u16 arr, u16 psc, u16 mode_counter, \
		                         u16 ic_polarity);

   void Timer2_CAP_Sink_Init(u32 arr, u16 psc, u16 mode_counter, \
		                         u16 ic_polarity);
#endif
// no more.
// -----------------------------------------------------------

