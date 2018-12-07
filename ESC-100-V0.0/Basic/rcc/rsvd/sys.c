

/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
���޸���־��
1-201708221422 ����RCCʱ�ӵ����ú�����


*/


 # include "sys.h"
   void NVIC_Configuration(void) //Ƕ���ж����������� ������
   {
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
   }

   void RCC_Configuration(void)  //RCCʱ�ӵ�����  
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
    // SYSCLK 0��24MHz:  Latency_0
    // SYSCLK 24��48MHz: Latency_1
    // SYSCLK 48��72MHz: Latency_2
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

	/*��ʼʹ�ܳ�������Ҫʹ�õ�����ʱ��*/   
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |   
//	RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); //APB2����ʱ��ʹ��      
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //APB1����ʱ��ʹ��  
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);   
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);   	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    
   }/*void RCC_Configuration(void)*/

/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/
