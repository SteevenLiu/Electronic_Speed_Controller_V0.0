// -----------------------------------------------------------
// FILE: ESC_StandardSCI_Communication.h
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
   # include "ESC_TypeDef.h"
//
// 2nd.datatypes
// -----------------------------------------------------------
// # ifndef _MACRONAME_DATATYPES
// # define _MACRONAME_DATATYPES
   /* define types here */
// # endif

//
// 3rd. variables
// -----------------------------------------------------------
// # ifndef _MACRONAME_VARIABLES
// # define _MACRONAME_VARIABLES
   /* define variables here */
// # endif

//
// 4th.function prototypes
// -----------------------------------------------------------
   Uint16 ESC_StdSci_Receive(Uint16 frame_DataType);
   void ESC_StdSci_Send(Uint16 frame_DataType, Uint16 frame_Data);
// no more.
// -----------------------------------------------------------/
