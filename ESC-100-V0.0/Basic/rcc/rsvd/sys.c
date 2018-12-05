

/*
//杜洋工作室出品
//洋桃系列开发板应用程序
//关注微信公众号：洋桃电子
//洋桃开发板资料下载 www.DoYoung.net/YT 
//即可免费看所有教学视频，下载技术资料，技术疑难提问
//更多内容尽在 杜洋工作室主页 www.doyoung.net
*/

/*
《修改日志》
1-201708221422 加入RCC时钟的设置函数。


*/


 # include "sys.h"
   void NVIC_Configuration(void) //嵌套中断向量控制器 的设置
   {
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
   }

   void RCC_Configuration(void)  //RCC时钟的设置  
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
    // SYSCLK 0—24MHz:  Latency_0
    // SYSCLK 24—48MHz: Latency_1
    // SYSCLK 48—72MHz: Latency_2
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

	/*开始使能程序中需要使用的外设时钟*/   
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |   
//	RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); //APB2外设时钟使能      
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //APB1外设时钟使能  
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);   
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);   	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    
   }/*void RCC_Configuration(void)*/

/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/
