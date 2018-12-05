// -----------------------------------------------------------
// FILE: ESC_StandardSCI_DataTypeDef.h
//
// Description: 
//
// -----------------------------------------------------------
// Release Date: 2018-08-0828;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
// 1.from Host to Slave
// ...........................................................
 # define CMD_MotorEnable 0x01
 # define CMD_TargetSpeed 0x02
 # define CMD_TargetDuty  0x03
 # define CMD_TargetCurrent  0x04

 # define Config_SpeedPid_Ki 0x10
 # define Config_SpeedPid_Kp 0x11

// 2.from Slave to Host
// ...........................................................
 # define State_MainStateMachine 0x80
 # define State_ControlStateMachine 0x81

 # define FeedBack_AppStatus 0x90
 # define FeedBack_iBus 0x91
 # define FeedBack_PwmDuty 0x98

 # define FeedBack_SpeedAverage_L16 0xA0
 # define FeedBack_SpeedAverage_H16 0xA1
 # define FeedBack_SpeedReference_L16 0xA2
 # define FeedBack_SpeedReference_H16 0xA3
 # define FeedBack_ReferenceError_L16 0xA4
 # define FeedBack_ReferenceError_H16 0xA5

 # define FeedBack_HallState 0xB0

 # define FeedBack_CDE_SMC 0xC0
 # define FeedBack_CDE_SMM 0xC1

 # define FeedBack_Test0 0xF0
 # define FeedBack_Test1 0xF1
 # define FeedBack_Test2 0xF2
 # define FeedBack_Test3 0xF3
//
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

// no more.
// -----------------------------------------------------------/
