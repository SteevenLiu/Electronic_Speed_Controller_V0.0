// -----------------------------------------------------------
// FILE: ESC_StandardSCI_Communication.c
// Description: Defines ESC data sending and receiving mathod
//              using standard SCI protocal.
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
// 2nd.functions
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

// 2.data receiving using StdSci Protocal
// ...........................................................
   /**
   @brief Read and return data frame out of standard SCI
          package buffer according to data type and data
          validity.
   @param frame_Datatype: Data type defined by users.
   @param *frame_Data: pointer of data.
   @retval data validity.
   */
   enum Boole ESC_StdSci_Receive(u16 frame_DataType, u16* frame_Data)
   {
     struct STDSCI_PACK_RX pck_rx;
     enum Boole rcvd = False;
			 
     pck_rx = StdSci_Read();
 
     if (pck_rx.pck.frame.DataType == frame_DataType)
     {
       if(pck_rx.validity)
       {
         *frame_Data = ( pck_rx.pck.frame.DataHghr << StdSci_CharBits) \
                       | pck_rx.pck.frame.DataLwr;			 
         rcvd = True;
         ESC_StdSci_Send(*frame_Data, frame_DataType);
       }
       else
       {;}
     }
     else
     {;}

     return rcvd;
   }

// no more.
// -----------------------------------------------------------

