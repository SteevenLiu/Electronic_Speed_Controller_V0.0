// -----------------------------------------------------------
// FILE: ESC_StandardSCI_Receive.c
//
// Description: ESC standard SCI receive funcion.
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
// 4th.functions
// -----------------------------------------------------------
   Uint16 ESC_StdSci_Receive(Uint16 frame_DataType)
   {
     struct STDSCI_PACK_RX pck_rx;
     Uint16 frame_Data;
		 
     pck_rx = StdSci_Read();
 
     if (pck_rx.validity == True)
     { 
       if (pck_rx.pck.frame.DataType == frame_DataType)
       {
         frame_Data = (pck_rx.pck.frame.DataHghr << StdSci_CharBits) | pck_rx.pck.frame.DataLwr;
       }
			 else
       {
			   frame_Data = 0;
			 }
     }
     else
     {
       frame_Data = 0;
     }

     return frame_Data;
   }

// no more.
// -----------------------------------------------------------

