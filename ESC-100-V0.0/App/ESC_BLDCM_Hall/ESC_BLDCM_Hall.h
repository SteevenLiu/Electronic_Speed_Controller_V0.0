
//=============================================================================
// Copyright (C) 2017, Active-Semi International
//
// THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES,
// AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S
// APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL;
// (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT
// ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
// DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
// ONLY BY CERTAIN AUTHORIZED PERSONS.
//
//=============================================================================

#ifndef __ESC_BLDCM_Hall_H
#define __ESC_BLDCM_Hall_H

# include "hall.h"
# include "ESC_BLDCM_Config.h"
# include "ESC_BLDCM_BASIC.h"
# include "ESC_Chopper.h"
# include "ESC_StandardSCI_Protocal.h"
 
#define HALL_START_COMMUTATE_VECTER_MUN             12
#define HALL_START_TO_BEMF_ONE_VECTER_DELAY_TIME    100
#define BEMF_TO_HALL_START_ONE_VECTER_DELAY_TIME    150
#define HALL_BEMF_SWISH_SPEED_OFFSET                100
#define ERRO_HALL_VALUE_0                             0
#define ERRO_HALL_VALUE_7                             7

 # define STATUS_HALL_A (GPIOA->IDR & GPIO_Pin_15)
 # define STATUS_HALL_B (GPIOB->IDR & GPIO_Pin_10)
 # define STATUS_HALL_C (GPIOA->IDR & GPIO_Pin_3)

 # if ORNT_CLOCKWISE
   # define BOOLE_HALL_U_SET (STATUS_HALL_A != 0)
   # define BOOLE_HALL_V_SET (STATUS_HALL_B != 0)
   # define BOOLE_HALL_W_SET (STATUS_HALL_C != 0)
   # define BOOLE_HALL_U_RESET (STATUS_HALL_A == 0)
   # define BOOLE_HALL_V_RESET (STATUS_HALL_B == 0)
   # define BOOLE_HALL_W_RESET (STATUS_HALL_C == 0)

	 # define DMA_HALL_U_INIT DMA_Config_DMA1_Ch5((u32)(&TIM2->CCR1),(u32)(&hall_ptr_o->t_commutate_m_Hall_U))
   # define DMA_HALL_V_INIT DMA_Config_DMA1_Ch1((u32)(&TIM2->CCR3),(u32)(&hall_ptr_o->t_commutate_m_Hall_V))
   # define DMA_HALL_W_INIT DMA_Config_DMA1_Ch7((u32)(&TIM2->CCR4),(u32)(&hall_ptr_o->t_commutate_m_Hall_W))
 
//   # define BOOLE_DMA_RENEWED_HALL_U (DMA_GetFlagStatus(DMA1_FLAG_TC5))
//   # define BOOLE_DMA_RENEWED_HALL_V (DMA_GetFlagStatus(DMA1_FLAG_TC1))
//   # define BOOLE_DMA_RENEWED_HALL_W (DMA_GetFlagStatus(DMA1_FLAG_TC7))

   # define CLEAR_DMA_FLAG_HALL_U (DMA_ClearFlag(DMA1_FLAG_TC5))
   # define CLEAR_DMA_FLAG_HALL_V (DMA_ClearFlag(DMA1_FLAG_TC1))
   # define CLEAR_DMA_FLAG_HALL_W (DMA_ClearFlag(DMA1_FLAG_TC7))
 # else
   # define BOOLE_HALL_U_SET (STATUS_HALL_C != 0)
   # define BOOLE_HALL_V_SET (STATUS_HALL_B != 0)
   # define BOOLE_HALL_W_SET (STATUS_HALL_A != 0)
   # define BOOLE_HALL_U_RESET (STATUS_HALL_C == 0)
   # define BOOLE_HALL_V_RESET (STATUS_HALL_B == 0)
   # define BOOLE_HALL_W_RESET (STATUS_HALL_A == 0)

   # define DMA_HALL_U_INIT DMA_Config_DMA1_Ch7((u32)(&TIM2->CCR4),(u32)(&hall_ptr_o->t_commutate_m_Hall_U))
   # define DMA_HALL_V_INIT DMA_Config_DMA1_Ch1((u32)(&TIM2->CCR3),(u32)(&hall_ptr_o->t_commutate_m_Hall_V))
	 # define DMA_HALL_W_INIT DMA_Config_DMA1_Ch5((u32)(&TIM2->CCR1),(u32)(&hall_ptr_o->t_commutate_m_Hall_W))

//   # define BOOLE_DMA_RENEWED_HALL_U (DMA_GetFlagStatus(DMA1_FLAG_TC7))
//   # define BOOLE_DMA_RENEWED_HALL_V (DMA_GetFlagStatus(DMA1_FLAG_TC1))
//   # define BOOLE_DMA_RENEWED_HALL_W (DMA_GetFlagStatus(DMA1_FLAG_TC5))

   # define CLEAR_DMA_FLAG_HALL_U (DMA_ClearFlag(DMA1_FLAG_TC7))
   # define CLEAR_DMA_FLAG_HALL_V (DMA_ClearFlag(DMA1_FLAG_TC1))
   # define CLEAR_DMA_FLAG_HALL_W (DMA_ClearFlag(DMA1_FLAG_TC5))
 # endif /*# if ORNT_CLOCKWISE*/

 # define BIT_HALL_U 0x04
 # define BIT_HALL_V 0x02
 # define BIT_HALL_W 0x01

 # define BOOLE_HALL_STATE_CHANGE (hall_ptr->sensored_current_state_pre != hall_ptr->sensored_current_state)
 # define REFRESH_CURRENT_HALL_STATE (hall_ptr->sensored_current_state = hall_to_mos_state[hall_ptr->hall_value])
 # define REFRESH_PREVIOUS_HALL_STATE (hall_ptr->sensored_current_state_pre = hall_ptr->sensored_current_state)
 
 # define BOOLE_DMA_RENEWED (DMA_GetFlagStatus(DMA1_FLAG_TC5) || \
                             DMA_GetFlagStatus(DMA1_FLAG_TC1) || \
                             DMA_GetFlagStatus(DMA1_FLAG_TC7))
 
 # define NUM_DT_SAMPLES 8
 # define RS_DT_AVERAGE 3

 # define MAX_S_E_DT_COMMUTATE ARR_HALL_CAP

// # define BOOLE_HALL_STATE_ILLEGAL ((hall_ptr->sensored_current_state == Phs_Z) || \
//                                    (hall_ptr->sensored_current_state == Phs_VII))
 # define BOOLE_HALL_LEGAL (((hall_ptr->sensored_current_state_pre ==             \
                              hall_ptr->sensored_current_state)          &&       \
                             (hall_ptr->sensored_current_state != Phs_Z) &&       \
                             (hall_ptr->sensored_current_state != Phs_VII)) ||    \
                            (next_mos_state[hall_ptr->sensored_current_state_pre] \
                             == hall_ptr->sensored_current_state))
 # define BOOLE_HALL_STATE_LEGAL (hall_ptr->hall_state_legal)
 # define BOOLE_HALL_STATE_LEGAL_PRE (hall_ptr->hall_state_legal_pre)

 # define REFRESH_PREVIOUS_HALL_STATE_LEGAL hall_ptr->hall_state_legal_pre = hall_ptr->hall_state_legal

 # define PS_LOWER_THAN_4762RPM (hall_ptr->dt_commutate_p > 0x2A30)  //5 case: 4
 
 # define PS_HIGHER_THAN_4761RPM (hall_ptr->dt_commutate_p < 0x2A31) //4 case: 5
 # define PS_LOWER_THAN_3987RPM (hall_ptr->dt_commutate_p > 0x3263)  //6
 
 # define PS_HIGHER_THAN_3986RPM (hall_ptr->dt_commutate_p < 0x3264) //5 case: 6
 # define PS_LOWER_THAN_3297RPM (hall_ptr->dt_commutate_p > 0x3CEF)  //7
 
 # define PS_HIGHER_THAN_3296RPM (hall_ptr->dt_commutate_p < 0x3CF0) //6 case: 7
 # define PS_LOWER_THAN_2858RPM (hall_ptr->dt_commutate_p > 0x464B)  //8
 
 # define PS_HIGHER_THAN_2857RPM (hall_ptr->dt_commutate_p < 0x464C) //7 case: 8
 # define PS_LOWER_THAN_2522RPM (hall_ptr->dt_commutate_p > 0x4FA8)  //9
 
 # define PS_HIGHER_THAN_2521RPM (hall_ptr->dt_commutate_p < 0x4FA9) //8 case: 9
 # define PS_LOWER_THAN_2256RPM (hall_ptr->dt_commutate_p > 0x590C)  //10
 
 # define PS_HIGHER_THAN_2255RPM (hall_ptr->dt_commutate_p < 0x590D) //9 case: 10
 # define PS_LOWER_THAN_2041RPM (hall_ptr->dt_commutate_p > 0x626E)  //11
 
 # define PS_HIGHER_THAN_2040RPM (hall_ptr->dt_commutate_p < 0x626F) //10 case: 11
 # define PS_LOWER_THAN_1864RPM (hall_ptr->dt_commutate_p > 0x6BC6)  //12
 
 # define PS_HIGHER_THAN_1863RPM (hall_ptr->dt_commutate_p < 0x6BC7) //11 case: 12
 # define PS_LOWER_THAN_1715RPM (hall_ptr->dt_commutate_p > 0x7524)  //13
 
 # define PS_HIGHER_THAN_1714RPM (hall_ptr->dt_commutate_p < 0x7525) //12 case: 13
 # define PS_LOWER_THAN_1588RPM (hall_ptr->dt_commutate_p > 0x7E82)  //14
 
 # define PS_HIGHER_THAN_1587RPM (hall_ptr->dt_commutate_p < 0x7E83) //13 case: 14
 # define PS_LOWER_THAN_1478RPM (hall_ptr->dt_commutate_p > 0x87EC)  //15
 
 # define PS_HIGHER_THAN_1477RPM (hall_ptr->dt_commutate_p < 0x87ED) //14 case: 15
 # define PS_LOWER_THAN_1383RPM (hall_ptr->dt_commutate_p > 0x9142)  //16
 
 # define PS_HIGHER_THAN_1382RPM (hall_ptr->dt_commutate_p < 0x9143) //15 case: 16
 # define PS_LOWER_THAN_1299RPM (hall_ptr->dt_commutate_p > 0x9AA7)  //17
 
 # define PS_HIGHER_THAN_1298RPM (hall_ptr->dt_commutate_p < 0x9AA8) //16 case: 17
 # define PS_LOWER_THAN_1225RPM (hall_ptr->dt_commutate_p > 0xA3FF)  //18
 
 # define PS_HIGHER_THAN_1224RPM (hall_ptr->dt_commutate_p < 0xA400) //17 case: 18
 # define PS_LOWER_THAN_1159RPM (hall_ptr->dt_commutate_p > 0xAD55)  //19
 
 # define PS_HIGHER_THAN_1158RPM (hall_ptr->dt_commutate_p < 0xAD56) //18 case: 19
 # define PS_LOWER_THAN_1099RPM (hall_ptr->dt_commutate_p > 0xB6CC)  //20
 
 # define PS_HIGHER_THAN_1098RPM (hall_ptr->dt_commutate_p < 0xB6CD) //19 case: 20
 # define PS_LOWER_THAN_1046RPM (hall_ptr->dt_commutate_p > 0xC00F)  //21
 
 # define PS_HIGHER_THAN_1045RPM (hall_ptr->dt_commutate_p < 0xC010) //20 case: 21
 # define PS_LOWER_THAN__997RPM (hall_ptr->dt_commutate_p > 0xC97F)  //22
 
 # define PS_HIGHER_THAN__996RPM (hall_ptr->dt_commutate_p < 0xC980) //21 case: 22
 # define PS_LOWER_THAN__953RPM (hall_ptr->dt_commutate_p > 0xD2CD)  //23
 
 # define PS_HIGHER_THAN__952RPM (hall_ptr->dt_commutate_p < 0xD2CE) //22 case: 23
 # define PS_LOWER_THAN__912RPM (hall_ptr->dt_commutate_p > 0xDC47)  //24
 
 # define PS_HIGHER_THAN__911RPM (hall_ptr->dt_commutate_p < 0xDC48) //23 case: 24
 # define PS_LOWER_THAN__875RPM (hall_ptr->dt_commutate_p > 0xE598)  //25
 
 # define PS_HIGHER_THAN__874RPM (hall_ptr->dt_commutate_p < 0xE599) //24 case: 25
 # define PS_LOWER_THAN__841RPM (hall_ptr->dt_commutate_p > 0xEEE0)  //26
 
 # define PS_HIGHER_THAN__840RPM (hall_ptr->dt_commutate_p < 0xEEE1) //25 case: 26
 # define PS_LOWER_THAN__809RPM (hall_ptr->dt_commutate_p > 0xF853)  //27
 
 # define PS_HIGHER_THAN__808RPM (hall_ptr->dt_commutate_p < 0xF854) //26 case: 27

extern Hall_Sensor     bldcm_hall_sensor_m1;
extern const uint8_t  hall_to_mos_state[];


//PAC5XXX_RAMFUNC void hall_detect_array_display_on_gui(void);
//PAC5XXX_RAMFUNC void hall_detect_in_bemf_mode(void);
/*PAC5XXX_RAMFUNC*/ void get_hall_value_and_change_mos_state(void);
//PAC5XXX_RAMFUNC void hall_bemf_switch_mode(void);

  void hall_sensor_init(void);
  void Get_Hall_2_UC(void);	 //2018.10.19
	void ESC_PWM_Counter(void);
  void ESC_PWM_Counter_2_UC(void);

 void ESC_Observer_Hall(void);         //2018.11.15 temp
 void ESC_Observer_Hall_Reset(void);   //2018.11.15 temp
 void ESC_Commutator_on_Hall_Observer(void);
#endif /*#ifndef __ESC_BLDCM_Hall_H*/
