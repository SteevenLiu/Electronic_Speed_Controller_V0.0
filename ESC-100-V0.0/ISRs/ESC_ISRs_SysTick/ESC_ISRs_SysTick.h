// -----------------------------------------------------------
// FILE: ESC_ISRs_SysTick.h
//
// Description: This is a template for newly created .h files.
//
// -----------------------------------------------------------
// Release Date: 2018-09-11;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __ESC_ISRs_SysTick_H
#define __ESC_ISRs_SysTick_H
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"
 # include "ESC_Chopper.h"
// # include "ESC_StandardSCI_Communication.h"
 # include "ESC_StandardSCI_DataTypeDef.h"
 # include "ESC_StandardSCI_Protocal.h"
 # include "ESC_BLDCM_Config.h"
 # include "ESC_StateMachine.h"
 
 # include "hall.h"

//
// 2nd.datatypes
// -----------------------------------------------------------
   /* define types here */

//
// 3rd. variables
// -----------------------------------------------------------
   /* define variables here */

//
// 4th.function prototypes
// -----------------------------------------------------------
	 u16 Get_instr(void);

#endif /*#ifndef __ESC_ISRs_SysTick_H*/
// no more.
// ----------------------------------------------------------- 

