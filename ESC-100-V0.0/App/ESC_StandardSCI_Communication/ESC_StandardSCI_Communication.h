// -----------------------------------------------------------
// FILE: ESC_StandardSCI_Communication.h
//
// Description: Head file.
//
// -----------------------------------------------------------
// Release Date: 2018-08-27;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"
 # include "ESC_StandardSCI_Protocal.h"
//
// 2nd.function prototypes
// -----------------------------------------------------------
   Boole ESC_StdSci_Receive(u16 frame_DataType, volatile u16* frame_Data);
   void ESC_StdSci_Send(u16 frame_DataType, u16 frame_Data);
// no more.   
// -----------------------------------------------------------
