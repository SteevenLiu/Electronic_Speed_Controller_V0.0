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

   #include "rcc.h"
   #include "nvic.h"
   #include "delay.h"
   #include "usart.h"
   #include "timer.h"
	 #include "hall.h"
	 #include "adc.h"
	 #include "dma.h"
	 
//   #include "ESC_StandardSCI_Communication.h"
   #include "ESC_StandardSCI_DataTypeDef.h"
   #include "ESC_StandardSCI_Protocal.h"

   #include "ESC_Chopper.h"
  
   #include "ESC_ISRs_TIM1.h"

   #include "ESC_BLDCM_Config.h"
	 #include "ESC_BLDCM_MISC.h"
   #include "ESC_Parameter.h"

 # include "ESC_BLDCM_Hall.h" //2018.11.14 temp

void user_param_fill(void);

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
	
//u16 phs = 1;
 u16 temp_data;

// Motor_Align_Go               bldcm_align_go;
   BLDCM_Controller             bldcm_m1;
   Hall_Sensor                  bldcm_hall_sensor_m1;
   Hall_Observer                bldcm_hall_observer_m1;
   eBLDCM_Main_Machine_State    main_machine_state;
   eBLDCM_Main_Machine_State    main_machine_state_pre;
   eSub_Control_Machine_State   control_machine_state;
   eSub_Control_Machine_State   control_machine_state_pre;
// eGet_Zero_Cross_Point_State  get_zero_cross_point_state;
// eHall_Bemf_Switch_State      hall_bemf_switch_state;

//  u16 feedback_CodeEfficiency_SMC_pre;
  u16 feedback_CodeEfficiency_SMC;
	u16 feedback_CodeEfficiency_SMM;

  volatile u32 feedback_Test_0_Long;
  volatile u32 feedback_Test_1_Long;

  volatile u16 feedback_Test_0;
	volatile u16 feedback_Test_1;
	volatile u16 feedback_Test_2;
  volatile u16 feedback_Test_3;
  volatile u16 feedback_Test_4;

//  STDSCI_PACK_TX pck_STD_TX_0xA0; //2018.11.16 temp
//  STDSCI_PACK_TX pck_STD_TX_0xA1; //2018.11.16 temp

int main(void)
{
//  BLDCM_Controller* motor_ptr;
//  motor_ptr = &bldcm_m1;
//  Hall_Sensor* hall_ptr;
//  hall_ptr = &bldcm_hall_sensor_m1;

  Hall_Observer* hall_ptr_o;
  hall_ptr_o = &bldcm_hall_observer_m1;

//  u16 i=0;
  u16 j=0;
	
  RCC_Configuration();  //时钟设置
	
  USART1_Init(115200);  //串口初始化(115200波特率，接收中断禁止)	
//  InitVrbls_StdSci();   //变量初始化StdSci
	STDSCI_BLOCK_TX_Init(); //2018.11.16
  STDSCI_BUFF_RX_Init(); //2018.11.19


  Hall_Sink_Init();
  ESC_PWM_Cntr_Init();
  ESC_Param_fill();
  ADC_Configuration_ADC1();
//	ADC_Configuration_ADC2();
	
  Timer1_CAP_Sink_Init(ARR_PWM_CAP,PSC_PWM_CAP, TIM_CounterMode_Up,TIM_ICPolarity_Falling);	
  Timer2_CAP_Sink_Init(ARR_HALL_CAP,PSC_HALL_CAP, TIM_CounterMode_Up,TIM_ICPolarity_BothEdge);
//  Timer2_PWM_Drive_Init(4095,0, TIM_CounterMode_Up, TIM_OCPolarity_High);
//  Timer2_PWM_Drive_Init(ARR_PWM_DAC,PSC_PWM_DAC, TIM_CounterMode_Up, TIM_OCPolarity_High); 2018.11.12
  Timer8_PWM_Drive_Init(ARR_PWM_DRV,PSC_PWM_DRV,TIM_CounterMode_CenterAligned1,TIM_OCPolarity_High,TIM_OCNPolarity_High,0x8F);

   TIM_SetCompare6(TIM8, 300);

// DMA
   DMA_HALL_U_INIT;
   DMA_HALL_V_INIT;
   DMA_HALL_W_INIT;

   ESC_Observer_Hall_Reset();

//   hall_ptr_o->dma_ready = 0;

// Configure NVIC priority group:	4 pre-emption priorities, 4 subpriorities.
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

// interrupt
  NVIC_Configuration_USART1();
	NVIC_Configuration_TIM8_Update();
  NVIC_Configuration_TIM1_Capture();
  NVIC_Configuration_ADC1_2();
//NVIC_Configuration_SysTick();

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // Enable USART1 RX interrupt.
  TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE); // Enable Timer 8 update interrupt.
  TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE); // 
  TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE); //

  SysTick_Config(72000);     //System tick configuration(1ms)

  while(1)
  {	
//    for(i=0;i<0xFF;i++)
//    {			
//      if(ESC_StdSci_Receive(i, &temp_data))
//      {
//        ESC_StdSci_Send(i,temp_data);
//      }
//    }

//  TIM_SetCompare1(TIM2,Get_d_Cap()*ARR_PWM_DAC/ARR_PWM_CAP); 2018.11.12
//  TIM_SetCompare3(TIM2,Get_Hall()*ARR_PWM_DAC/7); 2018.11.12
//  TIM_SetCompare4(TIM2,j); 2018.11.08

    if(++j>5999) j = 1999;
  }/*while(1)*/
}

//void SysTick_Handler(void)
//{
//  u16 i;
//	i++;
//}

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
