// -----------------------------------------------------------
// FILE: Filename.h
//
// Description: 
//
// -----------------------------------------------------------
// Release Date: yyyy-mm-dd;
// Authour: Steven Liu;
// -----------------------------------------------------------
 # ifndef  __ESC_CHOPPER_H
 # define  __ESC_CHOPPER_H
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"

 # define ENB_CC1E  0x0001
 # define ENB_CC1NE 0x0004
 # define ENB_CC2E  0x0010
 # define ENB_CC2NE 0x0040
 # define ENB_CC3E  0x0100
 # define ENB_CC3NE 0x0400

 # define DIS_CC1E  0xFFFE
 # define DIS_CC1NE 0xFFFB
 # define DIS_CC2E  0xFFEF
 # define DIS_CC2NE 0xFFBF
 # define DIS_CC3E  0xFEFF
 # define DIS_CC3NE 0xFBFF

 # define U_Forced_Active TIM_ForcedOC1Config(TIM8,TIM_ForcedAction_Active)
 # define V_Forced_Active TIM_ForcedOC2Config(TIM8,TIM_ForcedAction_Active)
 # define W_Forced_Active TIM_ForcedOC3Config(TIM8,TIM_ForcedAction_Active)

 # define U_Forced_InActive TIM_ForcedOC1Config(TIM8,TIM_ForcedAction_InActive)
 # define V_Forced_InActive TIM_ForcedOC2Config(TIM8,TIM_ForcedAction_InActive)
 # define W_Forced_InActive TIM_ForcedOC3Config(TIM8,TIM_ForcedAction_InActive)

 # define TIM_ForcedAction_PwmMode1          ((uint16_t)0x0060)
 # define TIM_ForcedAction_PwmMode2          ((uint16_t)0x0070)

 # define U_Forced_PWM_MODE1 TIM_ForcedOC1Config(TIM8,TIM_ForcedAction_PwmMode1)
 # define V_Forced_PWM_MODE1 TIM_ForcedOC2Config(TIM8,TIM_ForcedAction_PwmMode1)
 # define W_Forced_PWM_MODE1 TIM_ForcedOC3Config(TIM8,TIM_ForcedAction_PwmMode1)

 # define U_Forced_PWM_MODE2 TIM_ForcedOC1Config(TIM8,TIM_ForcedAction_PwmMode2)
 # define V_Forced_PWM_MODE2 TIM_ForcedOC2Config(TIM8,TIM_ForcedAction_PwmMode2)
 # define W_Forced_PWM_MODE2 TIM_ForcedOC3Config(TIM8,TIM_ForcedAction_PwmMode2)

 # define UH_Turn_On  TIM8->CCER |= ENB_CC1E
 # define UL_Turn_On  TIM8->CCER |= ENB_CC1NE
 # define VH_Turn_On  TIM8->CCER |= ENB_CC2E
 # define VL_Turn_On  TIM8->CCER |= ENB_CC2NE
 # define WH_Turn_On  TIM8->CCER |= ENB_CC3E
 # define WL_Turn_On  TIM8->CCER |= ENB_CC3NE

 # define UH_Turn_Off  TIM8->CCER &= DIS_CC1E
 # define UL_Turn_Off  TIM8->CCER &= DIS_CC1NE
 # define VH_Turn_Off  TIM8->CCER &= DIS_CC2E
 # define VL_Turn_Off  TIM8->CCER &= DIS_CC2NE
 # define WH_Turn_Off  TIM8->CCER &= DIS_CC3E
 # define WL_Turn_Off  TIM8->CCER &= DIS_CC3NE

// 2nd.datatypes
// -----------------------------------------------------------
// # ifndef _MACRONAME_DATATYPES
// # define _MACRONAME_DATATYPES
//   /* define types here */
// # endif

//
// 3rd. variables
// -----------------------------------------------------------
// # ifndef _MACRONAME_VARIABLES
// # define _MACRONAME_VARIABLES
//   /* define variables here */
// # endif

//
// 4th.function prototypes
// -----------------------------------------------------------
   void Chopper_Phase_I(void);
   void Chopper_Phase_II(void);
   void Chopper_Phase_III(void);
   void Chopper_Phase_IV(void);
   void Chopper_Phase_V(void);
   void Chopper_Phase_VI(void);
   void Chopper_Phase_ZRO(void);

 # endif/*# ifndef  __ESC_CHOPPER_H*/
// no more.
// -----------------------------------------------------------/
