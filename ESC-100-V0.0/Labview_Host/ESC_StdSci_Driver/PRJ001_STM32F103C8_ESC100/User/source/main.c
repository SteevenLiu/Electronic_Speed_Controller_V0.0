/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    14-August-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
   #include "ESC_Device.h"
   #include "sys.h"
   #include "delay.h"
   #include "usart.h"
	 
   #include "ESC_StandardSCI_Protocal.h"
	 #include "ESC_StandardSCI_Communication.h"
	 
/** @addtogroup STM32F30x_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
//Uint16 cntr_temp=0;

int main(void)
{
//	u8 a;
	Uint16 i=0;
	Uint16 temp_data=0;
	
	RCC_Configuration();          //时钟设置
//  LED_Init();                   //LED初始化
//  KEY_Init();                   //按键初始化
//  BUZZER_Init();                //蜂鸣器初始化
	USART1_Init(115200,ENABLE);  //串口初始化(115200波特率，接收中断禁止)	
  InitVrbls_StdSci();
	
	while(1)
	{
		for(i=0;i<0xFF;i++)
		{
			temp_data = ESC_StdSci_Receive(i);
		  if(temp_data != 0)
			{
			  ESC_StdSci_Send(i,temp_data);
			}
		}

    delay_ms(500);
	}/*while(1)*/
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
