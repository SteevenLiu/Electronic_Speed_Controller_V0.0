// -----------------------------------------------------------
// FILE: ESC_StateMchine.h
//
// Description: 
//
// -----------------------------------------------------------
// Release Date: yyyy-mm-dd;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __ESC_StateMachine_H
#define __ESC_StateMachine_H
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_BLDCM_Config.h"
 # include "ESC_BLDCM_MISC.h"
 # include "ESC_BLDCM_Hall.h"
 # include "ESC_StandardSCI_Protocal.h"
//
// 2nd.datatypes
// -----------------------------------------------------------

// 1.the machine rotor D axis phase
//   .........................................................
//   PAHSE_N == (Hall_A<<2) + (Hall_B<<1) + (Hall_C<<0)
//     enum RtrPhs { PHS_I = 0b0101,                           \
//                   PHS_II = 0b0100,                          \
//                   PHS_III = 0b0110,                         \
//                   PHS_IV = 0b0010,                          \
//                   PHS_V = 0b0011,                           \
//                   PHS_VI = 0b0001,                          \
//                   PHS_ZRO = 0b0000 };
//
//   chined rotor phase type
//     struct RotorPhaseChin_MNBRS
//                       { enum RtrPhs p0;
//                         struct RotorPhaseChin_MNBRS* pN1;
//                         struct RotorPhaseChin_MNBRS* p1; };
//
// 2.the virtual finite state machine states
//   .........................................................
//   top-level state
//     enum FsmState { SERVO_DFLT  = 0x0000,                   \
//                     SERVO_STOP  = 0x0001,                   \
//                     SERVO_LOCAT = 0x003F/*0x0003*/,         \
//                     SERVO_SYNCH = 0x007F/*0x0007*/,         \
//    	             SERVO_START = 0x0003/*0x003F*/,         \
//                     SERVO_TRANS = 0x0007/*0x007F*/,         \
//                     SERVO_STEER = 0x00FF/*0x000F*/,         \
//                     SERVO_DCDC  = 0x000F, /*only used for DCDC test*/
//                     SERVO_FAULT = 0x001F  };
//
// 3.machine working instruction from the host
//   .........................................................
//     enum InstrHost { MCH_STOP = 0x0000,                     \
//     	              MCH_RUN = 0x5555 };


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
   void main_state_machine(void);

#endif /*#ifndef __ESC_StateMachine_H*/
// no more.
// -----------------------------------------------------------/
