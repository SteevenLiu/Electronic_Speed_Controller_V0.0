// -----------------------------------------------------------
// FILE: adc.c
//
// Description: ...
//
// -----------------------------------------------------------
// Release Date: 2018-11-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
   # include "adc.h"

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
   void ADC_DMA_Init(void){}
 
// 2.function 2
// ...........................................................
   /**
   @brief This is the discription of function 1.
   @param argument1: This is the discription of argument 1.
   @param argument2: This is the discription of argument 2.
   @param argument3: This is the discription of argument 3.
   @retval This is the discription of the return value.
   */
   void ADC_GPIO_Init(void)
   {
     ADC_CommonInitTypeDef* ADC_CommonInitStruct;

     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12,ENABLE);
		 ADC_CommonInitStruct->ADC_Clock = ADC_Clock_SynClkModeDiv1;
     ADC_CommonInit(ADC1, ADC_CommonInitStruct);
   }

// 2.function 3
// ...........................................................
   /**
   @brief This is the discription of function 1.
   @param argument1: This is the discription of argument 1.
   @param argument2: This is the discription of argument 2.
   @param argument3: This is the discription of argument 3.
   @retval This is the discription of the return value.
   */
   void ADC_WatchDog_Configuration_ADC1(void)
   {
		 ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_SingleRegEnable);
		 ADC_AnalogWatchdog1ThresholdsConfig(ADC1, 0x700, 0x5FF);
		 ADC_AnalogWatchdog1SingleChannelConfig(ADC1, ADC_Channel_16);
   }

   void ADC_WatchDog_Configuration_ADC2(void)
   {
		 ADC_AnalogWatchdogCmd(ADC2, ADC_AnalogWatchdog_SingleRegEnable);
		 ADC_AnalogWatchdog1ThresholdsConfig(ADC2, 0x700, 0x5FF);
		 ADC_AnalogWatchdog1SingleChannelConfig(ADC2, ADC_Channel_16);
   }	 
	 
// ...

// 2.function 4
// ...........................................................
   /**
   @brief This is the discription of function 1.
   @param argument1: This is the discription of argument 1.
   @param argument2: This is the discription of argument 2.
   @param argument3: This is the discription of argument 3.
   @retval This is the discription of the return value.
   */
   void ADC_Configuration_ADC1(void)
   {
     ADC_InitTypeDef ADC_InitStruct;
//   ADC_InjectedInitTypeDef* ADC_InjectedInitStruct;
     GPIO_InitTypeDef GPIO_InitStructure;
		 
     ADC_Cmd(ADC1, DISABLE);

     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12,ENABLE);

  // CKMODE[1:0] = 0x01, HCLK/1
     ADC1_2->CCR |= 0x00010000;

  // enable Voltage Regulator
     ADC_VoltageRegulatorCmd(ADC1, ENABLE);
		 delay_us(20);

  // start calibration
     ADC_SelectCalibrationMode (ADC1, ADC_CalibrationMode_Differential);
     ADC_StartCalibration(ADC1);
		 while(ADC_GetCalibrationStatus(ADC1)){;}

//   GPIO config
//   .........................................................
//   ADC1_IN1
//     GPIO_InitStructure->GPIO_Pin   = GPIO_Pin_0;
//     GPIO_InitStructure->GPIO_Mode  = GPIO_Mode_AN;
//     GPIO_Init(GPIOA, GPIO_InitStructure);
//		 GPIOA->MODER |= 0x3;
//
//   ADC1_IN2
//     GPIO_InitStructure->GPIO_Pin   = GPIO_Pin_1;
//     GPIO_InitStructure->GPIO_Mode  = GPIO_Mode_AN;
//     GPIO_Init(GPIOA, GPIO_InitStructure);
//		 GPIOA->MODER |= (0x3<<2);

//   Configure pin mode as Alternate Function.
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
     GPIO_Init(GPIOA,&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
     GPIO_Init(GPIOA,&GPIO_InitStructure);

//   regular conversion
//   .........................................................		 
     ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b; //12-bit resolution
		 ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; //right alignment
     ADC_InitStruct.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable; //continuous conversion
//     ADC_InitStruct->ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None; // conversion is triggered by software
     ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;
     ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_8;
		 ADC_InitStruct.ADC_NbrOfRegChannel = 1; //1 channel in regular group
     ADC_InitStruct.ADC_OverrunMode = ADC_OverrunMode_Enable; //enable Overrun Mode?
		 ADC_InitStruct.ADC_AutoInjMode = ADC_AutoInjec_Disable;
//
//   initialize		 
     ADC_Init(ADC1, &ADC_InitStruct);
//
//   channel config
//     ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_181Cycles5);
//     ADC1->DIFSEL |=(0x1<<1); //configure ADC channel 1 as differential
     ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_181Cycles5);
     ADC_SelectDifferentialMode(ADC1, ADC_Channel_1, ENABLE);

//   injected conversion
//   .........................................................
//     ADC_InjectedInitStruct->ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;
//     ADC_InjectedInitStruct->ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigConvEvent_8;
//     ADC_InjectedInitStruct->ADC_InjecSequence1 = ADC_InjectedChannel_1;
//     ADC_InjectedInitStruct->ADC_InjecSequence2 = ADC_InjectedChannel_1;
//     ADC_InjectedInitStruct->ADC_InjecSequence3 = ADC_InjectedChannel_1;
//		 ADC_InjectedInitStruct->ADC_InjecSequence4 = ADC_InjectedChannel_1;
//     ADC_InjectedInitStruct->ADC_NbrOfInjecChannel = 1;
////
////   initialize
//     ADC_InjectedInit (ADC1,ADC_InjectedInitStruct);

//     ADC1->JSQR = ( 0x1 |      /*JL[1:0], 1 conversion*/           \
//		               (0x8<<2)|   /*JEXTSEL[3:0], external event 8*/  \
//                   (0x1<<6)|   /*JEXTEN[1:0], triggered at external rising edge*/  \
//									 (0x10<<8)|  /*JSQ1[4:0], channel 16*/  \
//									 (0x01<<14)| /*JSQ2[4:0], channel 1*/  \
//									 (0x01<<20)| /*JSQ3[4:0], channel 1*/  \
//									 (0x01<<26)  /*JSQ4[4:0], channel 1*/  \
//									);
//   initialize temperature sensor
//   .........................................................
//   ADC_TempSensorCmd(ADC1,ENABLE);
//
//   configure interrupt
//   .........................................................
//   ADC_ITConfig(ADC1, ADC_IT_AWD1, ENABLE);
     ADC_ITConfig(ADC1, ADC_IT_EOS, ENABLE);
//   ADC_ITConfig(ADC1, ADC_IT_JEOS, ENABLE);

//   enable ADC
//   .........................................................
		 ADC_Cmd(ADC1, ENABLE); //enable ADC1

//   start conversion
//   .........................................................
     ADC_StartConversion(ADC1);
//		 ADC_StartInjectedConversion(ADC1);
		 delay_us(20);

//   enable watch-dog
//   .........................................................
     ADC_WatchDog_Configuration_ADC1(); //configure Analog WatchDog
   }

   void ADC_Configuration_ADC2(void)
   {		 
     ADC_InitTypeDef ADC_InitStruct;
     GPIO_InitTypeDef GPIO_InitStructure;

     ADC_Cmd(ADC2, DISABLE);

     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12,ENABLE);

  // CKMODE[1:0] = 0x01, HCLK/1
     ADC1_2->CCR |= 0x00010000;

  // enable Voltage Regulator
     ADC_VoltageRegulatorCmd(ADC2, ENABLE);
		 delay_us(20);

  // start calibration
     ADC_StartCalibration(ADC2);
		 while(ADC_GetCalibrationStatus(ADC2)){;}
//
//   GPIO config
//   .........................................................
//   Configure pin mode as Alternate Function.
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
     GPIO_Init(GPIOA,&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
     GPIO_Init(GPIOA,&GPIO_InitStructure);
		 

//   regular conversion
//   .........................................................		 
     ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b; //12-bit resolution
		 ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; //right alignment
     ADC_InitStruct.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable; //continuous conversion
//   ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None; // conversion is triggered by software
     ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;
     ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_8;
		 ADC_InitStruct.ADC_NbrOfRegChannel = 1; //1 channel in regular group
     ADC_InitStruct.ADC_OverrunMode = ADC_OverrunMode_Enable; //enable Overrun Mode?
		 ADC_InitStruct.ADC_AutoInjMode = ADC_AutoInjec_Disable;
//
     ADC_Init(ADC2, &ADC_InitStruct);
//
//   channel config
     ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 1, ADC_SampleTime_181Cycles5);
     ADC_SelectDifferentialMode(ADC2, ADC_Channel_1, ENABLE);
//
//   initialize temperature sensor
//   .........................................................
//   ADC_TempSensorCmd(ADC2,ENABLE);
//
//   configure interrupt
//   .........................................................
     ADC_ITConfig(ADC2, ADC_IT_EOS, ENABLE);
//     ADC_ITConfig(ADC2, ADC_IT_AWD1, ENABLE);
//
//   enable ADC2
//   .........................................................
		 ADC_Cmd(ADC2, ENABLE);
//
//   start conversion
//   .........................................................
     ADC_StartConversion(ADC2);
		 delay_us(20);
//
//   enable watch-dog
//   .........................................................
     ADC_WatchDog_Configuration_ADC2(); //configure Analog WatchDog
   }
// ...

// no more.
// -----------------------------------------------------------

