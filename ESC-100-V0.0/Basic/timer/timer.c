// -----------------------------------------------------------
// FILE: timer.c
// Description: Timer driver.
//
// -----------------------------------------------------------
// Release Date: 2018-08-30;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "timer.h"

// 2nd.functions
// -----------------------------------------------------------
// 1.Timer 1 PWM output configuration
// ...........................................................
   /**
   @brief configure Timer 1 to generate PWM uotputs. 
   @param arr: Auto-reload timer period (ARR_CNT). The PWM
          frequency is calculated as:
          frq_PWM = frq_CK_CNT/(ARR_CNT+1).

   @param psc: Prescaler used to divide timer clock (PSC_CNT).
          The timer counting frequency is calculated as:
          frq_CK_CNT = frq_CK_PSC/(PSC_CNT+1). 72MHz system clock
          with arr = 1799 and psc = 1 result in ?kHz PWM
          (20kHz=72MHz/(1+1)/(1799+1)).

   @param mode_counter: Timer counting mode.
   @param polarity_P: Output polarity.
   @param polarity_N: Complementary output polarity.
   @param deadtime: Length of dead zone.
   @retval None. 
	 */
   void Timer1_PWM_Drive_Init(u16 arr, u16 psc, u16 mode_counter, \
                              u16 polarity_P, u16 polarity_N,     \
                              u16 deadtime)
   {
//   Parameter Declarations
//   .........................................................
//   GPIO_InitTypeDef          GPIO_InitStrue;
     TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStrue;
     TIM_OCInitTypeDef         TIM_OCInitStrue;
     TIM_BDTRInitTypeDef       TIM_BDTRInitStruct;
         	
//   Peripharel Clock
//   .........................................................
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
 
//   IO Port configuration
//   .........................................................
   # if 0 //TIM1_No_Remap  // no remapping
//   enable clock for GPIO portA, GPIO portB, AFIO
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
   
//   configure pin mode as AF Push-Pull
     GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
//   configure pin speed as 50MHz
     GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
   
     GPIO_InitStrue.GPIO_Pin  = GPIO_Pin_8;  // TIM1_CH1
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_9;  // TIM1_CH2
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_10; // TIM1_CH3
///  GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_11; // TIM1_CH4
     GPIO_Init(GPIOA,&GPIO_InitStrue);
 
     GPIO_InitStrue.GPIO_Pin  = GPIO_Pin_13; // TIM1_CH1N
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_14; // TIM1_CH2N
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_15; // TIM1_CH3N
     GPIO_Init(GPIOB,&GPIO_InitStrue);
   # endif /*# if TIM1_No_Remap*/
 
//   Time base initialize
//   .........................................................
     TIM_TimeBaseInitStrue.TIM_Period        = arr;
     TIM_TimeBaseInitStrue.TIM_Prescaler     = psc;
     TIM_TimeBaseInitStrue.TIM_CounterMode   = mode_counter;
     TIM_TimeBaseInitStrue.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrue);
 
//   Output controller initialize
//   .........................................................
//   output validate voltage (defined by "OCPoarity" and "OCNPolarity")
//   when cnt<CCR
     TIM_OCInitStrue.TIM_OCMode       = TIM_OCMode_PWM1;

//   output enable
     TIM_OCInitStrue.TIM_OutputState  = TIM_OutputState_Enable;
     TIM_OCInitStrue.TIM_OutputNState = TIM_OutputNState_Enable;

//   output voltage polarity
     TIM_OCInitStrue.TIM_OCPolarity   = polarity_P;
     TIM_OCInitStrue.TIM_OCNPolarity  = polarity_N;

     TIM_OCInitStrue.TIM_OCIdleState  = TIM_OCIdleState_Set;
     TIM_OCInitStrue.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
     TIM_OC1Init(TIM1,&TIM_OCInitStrue);  // channel 1
     TIM_OC2Init(TIM1,&TIM_OCInitStrue);  // channel 2
     TIM_OC3Init(TIM1,&TIM_OCInitStrue);  // channel 3
 
     TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
     TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
     TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
 
//   Dead zone and brake initialize
//   .........................................................
     TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Enable;     // 运行模式下输出选择
     TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Enable;     // 空闲模式下输出选择
     TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;        // 锁定设置
     TIM_BDTRInitStruct.TIM_DeadTime  = deadtime;                     // 死区时间(us)
     TIM_BDTRInitStruct.TIM_Break     = TIM_Break_Disable;            // 刹车功能禁止
     TIM_BDTRInitStruct.TIM_BreakPolarity   = TIM_BreakPolarity_Low;  //刹车输入极性
     TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable; // 自动输出禁止
     TIM_BDTRConfig(TIM1,&TIM_BDTRInitStruct);
 
//   Enable
//   .........................................................

     TIM_Cmd(TIM1,ENABLE);                                        // 使能TIM1		 
     TIM_CtrlPWMOutputs(TIM1, ENABLE);
   }
//
// 2.Timer 8 PWM output configuration
// ...........................................................
   /**
   @brief configure Timer 8 to generate PWM uotputs.
   @param arr: Auto-reload timer period (ARR_CNT). The PWM
          frequency is calculated as:
          frq_PWM = frq_CK_CNT/(ARR_CNT+1).
  
   @param psc: Prescaler used to divide timer clock (PSC_CNT).
          The timer counting frequency is calculated as:
          frq_CK_CNT = frq_CK_PSC/(PSC_CNT+1). 72MHz system clock
          with arr = 1799 and psc = 1 result in ?kHz PWM
          (20kHz=72MHz/(1+1)/(1799+1)).
  
   @param mode_counter: Timer counting mode.
   @param polarity_P: Output polarity.
   @param polarity_N: Complementary output polarity.
   @param deadtime: Length of dead zone.
   @retval None.
   */
   void Timer8_PWM_Drive_Init(u16 arr, u16 psc, u16 mode_counter, \
                              u16 polarity_P, u16 polarity_N,     \
                              u16 deadtime)
   {
//   Parameter Declarations
//   .........................................................
     GPIO_InitTypeDef          GPIO_InitStructure;
     TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStrue;
     TIM_OCInitTypeDef         TIM_OCInitStrue;
     TIM_BDTRInitTypeDef       TIM_BDTRInitStruct;
         	
//   Peripharel Clock
//   .........................................................
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
 
//   IO Port configuration
//   .........................................................
//   enable clock for GPIO portB
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
   
     GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

     GPIO_InitStructure.GPIO_Pin = Pin_TIM8_CH1;
     GPIO_Init(Port_TIM8_CH1,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM8_CH2;
     GPIO_Init(Port_TIM8_CH2,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM8_CH3;
     GPIO_Init(Port_TIM8_CH3,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM8_CH1N;
     GPIO_Init(Port_TIM8_CH1N,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM8_CH2N;
     GPIO_Init(Port_TIM8_CH2N,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM8_CH3N;
     GPIO_Init(Port_TIM8_CH3N,&GPIO_InitStructure);

     GPIO_PinAFConfig(Port_TIM8_CH1, AF_PinSource_TIM8_CH1, AF_TIM8_CH1);
     GPIO_PinAFConfig(Port_TIM8_CH2, AF_PinSource_TIM8_CH2, AF_TIM8_CH2);
     GPIO_PinAFConfig(Port_TIM8_CH3, AF_PinSource_TIM8_CH3, AF_TIM8_CH3);
     GPIO_PinAFConfig(Port_TIM8_CH1N, AF_PinSource_TIM8_CH1N, AF_TIM8_CH1N);
     GPIO_PinAFConfig(Port_TIM8_CH2N, AF_PinSource_TIM8_CH2N, AF_TIM8_CH2N);
     GPIO_PinAFConfig(Port_TIM8_CH3N, AF_PinSource_TIM8_CH3N, AF_TIM8_CH3N);

//   Time base initialize
//   .........................................................
     TIM_TimeBaseInitStrue.TIM_Period        = arr;
     TIM_TimeBaseInitStrue.TIM_Prescaler     = psc;
     TIM_TimeBaseInitStrue.TIM_CounterMode   = mode_counter;
     TIM_TimeBaseInitStrue.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseInitStrue.TIM_RepetitionCounter = 0x01;
     TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStrue);

//   Output controller initialize
//   .........................................................
//   output validate voltage (defined by "OCPoarity" and "OCNPolarity")
//   when cnt<CCR
     TIM_OCInitStrue.TIM_OCMode       = TIM_OCMode_PWM1;

//   output enable
     TIM_OCInitStrue.TIM_OutputState  = TIM_OutputState_Enable;
     TIM_OCInitStrue.TIM_OutputNState = TIM_OutputNState_Enable;

//   output voltage polarity
     TIM_OCInitStrue.TIM_OCPolarity   = polarity_P;
     TIM_OCInitStrue.TIM_OCNPolarity  = polarity_N;

     TIM_OCInitStrue.TIM_OCIdleState  = TIM_OCIdleState_Set;
     TIM_OCInitStrue.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
     TIM_OC1Init(TIM8,&TIM_OCInitStrue);  // channel 1
     TIM_OC2Init(TIM8,&TIM_OCInitStrue);  // channel 2
     TIM_OC3Init(TIM8,&TIM_OCInitStrue);  // channel 3

     TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);
     TIM_OC2PreloadConfig(TIM8,TIM_OCPreload_Enable);
     TIM_OC3PreloadConfig(TIM8,TIM_OCPreload_Enable);
 
//   Dead zone and brake initialize
//   .........................................................
     TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Enable;
     TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Enable;
     TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
     TIM_BDTRInitStruct.TIM_DeadTime  = deadtime;
     TIM_BDTRInitStruct.TIM_Break     = TIM_Break_Disable;
     TIM_BDTRInitStruct.TIM_BreakPolarity   = TIM_BreakPolarity_Low;
     TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
     TIM_BDTRConfig(TIM8,&TIM_BDTRInitStruct);

//   Turn off all PWM outputs
//   .........................................................
     TIM8->CCER &= 0xFAAA;

//   trigger output
//   .........................................................
//   TIM_SelectOutputTrigger2(TIM8, TIM_TRGO2Source_Update);
//   TIM_SelectOutputTrigger2(TIM8, TIM_TRGO2Source_OC5RefRising_OC6RefFalling);
//   TIM_SelectOutputTrigger2(TIM8, TIM_TRGO2Source_OC4RefRising_OC6RefRising);
//   TIM_SelectOutputTrigger2(TIM8, TIM_TRGO2Source_OC1Ref);

     TIM_OC6Init(TIM8,&TIM_OCInitStrue);  // channel 6
     TIM_OC6PreloadConfig(TIM8,TIM_OCPreload_Enable);
     TIM_SelectOutputTrigger2(TIM8, TIM_TRGO2Source_OC5RefRising_OC6RefFalling);

//   Enable
//   .........................................................

     TIM_Cmd(TIM8,ENABLE);
     TIM_CtrlPWMOutputs(TIM8, ENABLE);
   }

//
// 3.Timer 2 PWM output configuration
// ...........................................................
   /**
   @brief configure Timer 2 to generate PWM uotputs.
   @param arr: Auto-reload timer period (ARR_CNT). The PWM
          frequency is calculated as:
          frq_PWM = frq_CK_CNT/(ARR_CNT+1).

   @param psc: Prescaler used to divide timer clock (PSC_CNT).
          The timer counting frequency is calculated as:
          frq_CK_CNT = frq_CK_PSC/(PSC_CNT+1). 72MHz system clock
          with arr = 1799 and psc = 1 result in ?kHz PWM
          (20kHz=72MHz/(1+1)/(1799+1)).
   @param mode_counter: Timer counting mode.
   @param polarity: Output polarity.
   @retval None.
   */
   void Timer2_PWM_Drive_Init(u16 arr, u16 psc, u16 mode_counter, \
		 u16 polarity)
   {
//   Parameter declarations
//   .........................................................
     GPIO_InitTypeDef          GPIO_InitStructure;
     TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStrue;
     TIM_OCInitTypeDef         TIM_OCInitStrue;
   
//   Peripharel clock
//   .........................................................
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

//   IO port
//   .........................................................
//   Enable clock for GPIO portA, GPIO portB.
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
   
//   Configure pin mode as Alternate Function.
     GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
		 
//   Configure output speed as 50MHz.
     GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

//   Configure output mode as Push-Pull.
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

     GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH1;
     GPIO_Init(Port_TIM2_CH1,&GPIO_InitStructure);

//   GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH2;
//   GPIO_Init(Port_TIM2_CH2,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH3;
     GPIO_Init(Port_TIM2_CH3,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH4;
     GPIO_Init(Port_TIM2_CH4,&GPIO_InitStructure);

     GPIO_PinAFConfig(Port_TIM2_CH1, AF_PinSource_TIM2_CH1, AF_TIM2_CH1);
//   GPIO_PinAFConfig(Port_TIM2_CH2, AF_PinSource_TIM2_CH2, AF_TIM2_CH2);
     GPIO_PinAFConfig(Port_TIM2_CH3, AF_PinSource_TIM2_CH3, AF_TIM2_CH3);
     GPIO_PinAFConfig(Port_TIM2_CH4, AF_PinSource_TIM2_CH4, AF_TIM2_CH4);

//   Time base
//   .........................................................
     TIM_TimeBaseInitStrue.TIM_Period = arr;                        //设置自动重装载值
     TIM_TimeBaseInitStrue.TIM_Prescaler = psc;                     //预分频系数
     TIM_TimeBaseInitStrue.TIM_CounterMode= mode_counter;    //计数器向上溢出
     TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
     TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);               //TIM2初始化设置(设置PWM的周期)
 
//   Output controller
//   .........................................................
     TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;  // output high when CNT < CCR
     TIM_OCInitStrue.TIM_OCPolarity= polarity;    // set high as active level
     TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;
     
     TIM_OC1Init(TIM2,&TIM_OCInitStrue);
//   TIM_OC2Init(TIM2,&TIM_OCInitStrue);
     TIM_OC3Init(TIM2,&TIM_OCInitStrue);
     TIM_OC4Init(TIM2,&TIM_OCInitStrue);
 
     TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
//   TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
     TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
     TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);

//   Enable
//   .........................................................
     TIM_Cmd(TIM2,ENABLE);
   }
//
// 4.Timer 3 PWM output configuration
// ...........................................................
   /**
   @brief configure Timer 3 to generate PWM uotputs.
   @param arr: Auto-reload timer period.
   @param psc: Prescaler used to divide timer 3 clock. 
   @retval None.
   */
   void Timer3_PWM_Drive_Init(u16 arr, u16 psc)
   {
//   Parameter declarations
//   .........................................................
//   GPIO_InitTypeDef          GPIO_InitStrue;
     TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStrue;
     TIM_OCInitTypeDef         TIM_OCInitStrue;
   
//   Peripharel clock
//   .........................................................
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

//   IO port
//   .........................................................
   # if 0 //TIM3_No_Remap  // no remapping
//   enable clock for GPIO portA, GPIO portB, AFIO
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
   
//   configure pin mode as AF Push-Pull
     GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
//   configure pin speed as 50MHz
     GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
   
     GPIO_InitStrue.GPIO_Pin  = GPIO_Pin_6; // TIM3_CH1
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_7; // TIM3_CH2
     GPIO_Init(GPIOA,&GPIO_InitStrue);
   
     GPIO_InitStrue.GPIO_Pin  = GPIO_Pin_0; // TIM3_CH3
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_1; // TIM3_CH4
     GPIO_Init(GPIOB,&GPIO_InitStrue);
   # endif /*# if TIM3_No_Remap*/

   # if TIM3_Partial_Remap  // partial remapping
//   enable clock for GPIO portB, AFIO
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
//   configure pin mode as AF Push-Pull
     GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
//   configure pin speed as 50MHz
     GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
    
     GPIO_InitStrue.GPIO_Pin  = GPIO_Pin_4; // TIM3_CH1
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_5; // TIM3_CH2
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_0; // TIM3_CH3
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_1; // TIM3_CH4
     GPIO_Init(GPIOB,&GPIO_InitStrue);
    
     GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
   # endif /*# if TIM3_Partial_Remap*/

   # if TIM3_Full_Remap  // full remapping
//   enable clock for GPIO portC, AFIO
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
//   configure pin mode as AF Push-Pull
     GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
//   configure pin speed as 50MHz
     GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
    
     GPIO_InitStrue.GPIO_Pin  = GPIO_Pin_6;  // TIM3_CH1
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_7;  // TIM3_CH2
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_8;  // TIM3_CH3
     GPIO_InitStrue.GPIO_Pin |= GPIO_Pin_9;  // TIM3_CH4
     GPIO_Init(GPIOC,&GPIO_InitStrue);
    
     GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
   # endif /*# if TIM3_Full_Remap*/
 
//   Time base
//   .........................................................
     TIM_TimeBaseInitStrue.TIM_Period=arr;                        //设置自动重装载值
     TIM_TimeBaseInitStrue.TIM_Prescaler=psc;                     //预分频系数
     TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //计数器向上溢出
     TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
     TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);               //TIM3初始化设置(设置PWM的周期)
 
//   Output controller
//   .........................................................
     TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;                  // PWM模式1:CNT < CCR时输出有效电平
     TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;          // 设置极性-有效电平为：高电平
     TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;      // 输出使能
     
     TIM_OC1Init(TIM3,&TIM_OCInitStrue);  
     TIM_OC2Init(TIM3,&TIM_OCInitStrue);  
     TIM_OC3Init(TIM3,&TIM_OCInitStrue);                          // TIM3的通道3 PWM 模式设置
     TIM_OC3Init(TIM3,&TIM_OCInitStrue);                          // TIM3的通道3 PWM 模式设置
 
     TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
     TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
     TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);             // 使能预装载寄存器
     TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);             // 使能预装载寄存器

//   Enable
//   .........................................................
     TIM_Cmd(TIM3,ENABLE);                                        // 使能TIM3
   }

//
// 5.Timer 1 CAPTURE input configuration
// ...........................................................
   /**
   @brief configure Timer 1 to capture PWM inputs.
   @param arr: Auto-reload timer period (ARR_CNT). The PWM
          frequency is calculated as:
          frq_PWM = frq_CK_CNT/(ARR_CNT+1).

   @param psc: Prescaler used to divide timer clock (PSC_CNT).
          The timer counting frequency is calculated as:
          frq_CK_CNT = frq_CK_PSC/(PSC_CNT+1). 72MHz system clock
          with arr = 1799 and psc = 1 result in ?kHz PWM
          (20kHz=72MHz/(1+1)/(1799+1)).
   @param mode_counter: Timer counting mode.
   @param ic_polarity: Input capture polarity.
   */
   void Timer1_CAP_Sink_Init(u16 arr, u16 psc, u16 mode_counter, \
		                         u16 ic_polarity)
   {
//   Parameter Declarations
//   .........................................................
     GPIO_InitTypeDef          GPIO_InitStruct;
     TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStrue;
     TIM_ICInitTypeDef         TIM_ICInitStruct;
//   Peripharel Clock
//   .........................................................
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

//   IO Port configuration
//   .........................................................
//   enable clock for GPIO portA, GPIO portB, AFIO
     RCC_AHBPeriphClockCmd(RCC_TIM1_CH1,ENABLE);
//   RCC_AHBPeriphClockCmd(RCC_TIM1_CH2,ENABLE);
//   RCC_AHBPeriphClockCmd(RCC_TIM1_CH3,ENABLE);
//   RCC_AHBPeriphClockCmd(RCC_TIM1_CH4,ENABLE);
   
//   configure pin mode as AF
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//   configure pin speed as 50MHz
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//   disable internal Pu-Pd
		 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
   
     GPIO_InitStruct.GPIO_Pin  = Pin_TIM1_CH1;  // TIM1_CH1
     GPIO_Init(Port_TIM1_CH1,&GPIO_InitStruct);

//     GPIO_InitStruct.GPIO_Pin  = Pin_TIM1_CH2;  // TIM1_CH2
//     GPIO_Init(Port_TIM1_CH2,&GPIO_InitStruct);

//     GPIO_InitStruct.GPIO_Pin  = Pin_TIM1_CH3;  // TIM1_CH3
//     GPIO_Init(Port_TIM1_CH3,&GPIO_InitStruct);
//		 
//     GPIO_InitStruct.GPIO_Pin  = Pin_TIM1_CH4;  // TIM1_CH4
//     GPIO_Init(Port_TIM1_CH4,&GPIO_InitStruct);		 

     GPIO_PinAFConfig(Port_TIM1_CH1, AF_PinSource_TIM1_CH1, AF_TIM1_CH1);
//     GPIO_PinAFConfig(Port_TIM1_CH2, AF_PinSource_TIM1_CH2, AF_TIM1_CH2);
//     GPIO_PinAFConfig(Port_TIM1_CH3, AF_PinSource_TIM1_CH3, AF_TIM1_CH3);
//     GPIO_PinAFConfig(Port_TIM1_CH4, AF_PinSource_TIM1_CH4, AF_TIM1_CH4);

//   Time base initialize
//   .........................................................
     TIM_TimeBaseInitStrue.TIM_Period        = arr;
     TIM_TimeBaseInitStrue.TIM_Prescaler     = psc;
     TIM_TimeBaseInitStrue.TIM_CounterMode   = mode_counter;
     TIM_TimeBaseInitStrue.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrue);

//   Input stage configuration
//   .........................................................
     TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
		 TIM_ICInitStruct.TIM_ICFilter = 0xF;
		 TIM_ICInitStruct.TIM_ICPolarity = ic_polarity;
		 TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		 TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
     
     TIM_PWMIConfig(TIM1, &TIM_ICInitStruct);
		 
//   Enable
//   .........................................................
     TIM_Cmd(TIM1,ENABLE);
   }
//
// 6.Timer 2 CAPTURE input configuration
// ...........................................................
   /**
   @brief configure Timer 2 to capture PWM inputs.
   @param arr: Auto-reload timer period (ARR_CNT).
   @param psc: Prescaler used to divide timer clock (PSC_CNT).
          The timer counting frequency is calculated as:
          frq_CK_CNT = frq_CK_PSC/(PSC_CNT+1).

   @param mode_counter: Timer counting mode.
   @param ic_polarity: Input capture polarity.
   */
   void Timer2_CAP_Sink_Init(u32 arr, u16 psc, u16 mode_counter, \
		                         u16 ic_polarity)
   {
//   Parameter Declarations
//   .........................................................
     GPIO_InitTypeDef          GPIO_InitStructure;
     TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStrue;
     TIM_ICInitTypeDef         TIM_ICInitStruct;
//   Peripharel Clock
//   .........................................................
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

//   IO Port configuration
//   .........................................................
//   Enable clock for GPIO portA, GPIO portB.
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);

//   Configure pin mode as Alternate Function.
     GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;		 
//   Configure output speed as 50MHz.
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   disable internal Pu-Pd
		 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

     GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH1;
     GPIO_Init(Port_TIM2_CH1,&GPIO_InitStructure);

//   GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH2;
//   GPIO_Init(Port_TIM2_CH2,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH3;
     GPIO_Init(Port_TIM2_CH3,&GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = Pin_TIM2_CH4;
     GPIO_Init(Port_TIM2_CH4,&GPIO_InitStructure); 

     GPIO_PinAFConfig(Port_TIM2_CH1, AF_PinSource_TIM2_CH1, AF_TIM2_CH1);
//   GPIO_PinAFConfig(Port_TIM2_CH2, AF_PinSource_TIM2_CH2, AF_TIM2_CH2);
     GPIO_PinAFConfig(Port_TIM2_CH3, AF_PinSource_TIM2_CH3, AF_TIM2_CH3);
     GPIO_PinAFConfig(Port_TIM2_CH4, AF_PinSource_TIM2_CH4, AF_TIM2_CH4);

//   Time base initialize
//   .........................................................
     TIM_TimeBaseInitStrue.TIM_Period        = arr;
     TIM_TimeBaseInitStrue.TIM_Prescaler     = psc;
     TIM_TimeBaseInitStrue.TIM_CounterMode   = mode_counter;
     TIM_TimeBaseInitStrue.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);

//   Input stage configuration
//   .........................................................
		 TIM_ICInitStruct.TIM_ICFilter = 0xF;
		 TIM_ICInitStruct.TIM_ICPolarity = ic_polarity;
		 TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
     TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
//	 TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;

     TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
		 TIM_ICInit(TIM2,&TIM_ICInitStruct);
//   TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);

//     TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
//		 TIM_ICInit(TIM2,&TIM_ICInitStruct);
////   TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);

     TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;
		 TIM_ICInit(TIM2,&TIM_ICInitStruct);
//   TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);

     TIM_ICInitStruct.TIM_Channel = TIM_Channel_4;
		 TIM_ICInit(TIM2,&TIM_ICInitStruct);
//   TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);

//   DMA
//   .........................................................
//   TIM_DMAConfig(TIM2, TIM_DMABase_CCR1, TIM_DMABurstLength_4Transfers);
     TIM_DMACmd(TIM2, TIM_DMA_CC1, ENABLE);
     TIM_DMACmd(TIM2, TIM_DMA_CC3, ENABLE);
     TIM_DMACmd(TIM2, TIM_DMA_CC4, ENABLE);
		 
     TIM_SelectCCDMA(TIM2, DISABLE);
//   Enable
//   .........................................................
     TIM_Cmd(TIM2,ENABLE);
   }

// no more.
// -----------------------------------------------------------

