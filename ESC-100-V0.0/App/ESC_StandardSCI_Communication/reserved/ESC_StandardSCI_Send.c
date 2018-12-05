// -----------------------------------------------------------
// FILE: ESC_StandardSCI_Send.c
// Description: Defines ESC data sending mathod using standard
// SCI protocal.
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
// 2nd.funcions
// -----------------------------------------------------------
// 1.data Sending using StdSci Protocal
// ...........................................................
   /**
   @brief Send data and its type to Host.
   @param frame_Datatype: Data type defined by users.
   @param frame_Data: Data.
   @retval None.
   */
   void ESC_StdSci_Send(u16 frame_DataType, u16 frame_Data)
   {
     StdSci_Send(USART1, frame_DataType, frame_Data);
   }

// no more.
// -----------------------------------------------------------

