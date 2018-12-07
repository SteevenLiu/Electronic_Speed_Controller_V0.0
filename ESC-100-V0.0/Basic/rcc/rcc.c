// -----------------------------------------------------------
// FILE: sys.c
//
// Description: System initial configuration methods.
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
   # include "rcc.h"

//
// 2nd. variables
// -----------------------------------------------------------

//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
// 1.RCC clock configuration
// ...........................................................
   /**
   @brief Configure RCC clock.
   @param None.
   @retval None.
   */
   void RCC_Configuration(void)
   {
     ErrorStatus HSEStartUpStatus;
     RCC_DeInit(); // Resets the RCC clock configuration to the default reset state.
		 
  // Configures the External High Speed oscillator (HSE):
  // HSE oscillator bypassed with external clock.
     RCC_HSEConfig(RCC_HSE_Bypass);

     HSEStartUpStatus = RCC_WaitForHSEStartUp(); // Wait till HSE is ready.
		 
     if(HSEStartUpStatus == SUCCESS)
     {
    // Configures the PLL clock source and multiplication factor.
    // PLLCLK = f_HSE * RCC_PLLMul_9 = 8MHz * 9 = 72MHz.
       RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);

    // Configures the AHB clock (HCLK).
    // HCLK = SYSCLK/1 = 72MHz.
       RCC_HCLKConfig(RCC_SYSCLK_Div1);

    // Configures the Low Speed APB clock (PCLK1).
    // PCLK1 = HCLK/2 = 36MHz.
       RCC_PCLK1Config(RCC_HCLK_Div2);

    // Configures the High Speed APB clock (PCLK2).
    // PCLK2 = HCLK/1 = 72MHz.
       RCC_PCLK2Config(RCC_HCLK_Div1);

    // specifies the FLASH Latency value.
    // SYSCLK 0MHz  ~ 24MHz: Latency_0
    // SYSCLK 24MHz ~ 48MHz: Latency_1
    // SYSCLK 48MHz ~ 72MHz: Latency_2
       FLASH_SetLatency(FLASH_Latency_2);
    
    // Enables Flash Prefetch Buffer.
       FLASH_PrefetchBufferCmd(ENABLE);

    // Enable PLL.
       RCC_PLLCmd(ENABLE);                                 	 
    // Wait untill PLL clock is ready.
       while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
			 
    // Select PLL as system clock (SYSCLK) source.
       RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // Wait untill PLL is actually used as system clock.			 
       while(RCC_GetSYSCLKSource() != 0x08);
     }/*if(HSEStartUpStatus == SUCCESS)*/
   }

// no more.
// -----------------------------------------------------------

