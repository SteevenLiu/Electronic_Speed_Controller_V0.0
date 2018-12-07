// -----------------------------------------------------------
// FILE: ESC_StandardSCI_Send.c
// 
// Description:
//
// -----------------------------------------------------------
// Release Date: 2018-08-27;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
   # include "ESC_StandardSCI_Protocal.h"
   # include "ESC_StandardSCI_Communication.h"

//
// 2nd. variables
// -----------------------------------------------------------

//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------

   void ESC_StdSci_Send(Uint16 frame_DataType, Uint16 frame_Data)
   {
     StdSci_Send(USART1, frame_DataType, frame_Data);
   }

// no more.
// -----------------------------------------------------------

