// -----------------------------------------------------------
// File: ESC_StandardSCI_Protocal.c
//
// -----------------------------------------------------------
// Release Date: 2018-08-24;
// Authour: Liu Shiwei;
// -----------------------------------------------------------
 # include "stm32f10x_usart.h"
 
 # include "ESC_TypeDef.h"
 # include "ESC_StandardSCI_Protocal.h"

// 4. local variables
// -----------------------------------------------------------
// A.local variable definition
//   .........................................................
//   Uint16 bff_StdSciRx[StdSci_RxBuffLength] = {0};

     struct STDSCI_PACK_RX pck_StdSciRx;
     struct STDSCI_PACK_BUFF buffer_pck_StdSciRx;

//   struct STDSCI_RX_MEM
//   {
//     Uint16 *pHead;
//     Uint16 offset;
//     Uint16 length;
//   } sMemStdSciRx;
//
     enum StdSci_RX_State {Idle, Receiving};
     enum StdSci_RX_State stt_StdSciRx;
		 
// B. local variable initialization
//   .........................................................
     void InitVrbls_StdSci (void)
     {
//     sMemStdSciRx.pHead  = bff_StdSciRx;
//     sMemStdSciRx.offset = 0;
//     sMemStdSciRx.length = StdSci_RxBuffLength;
			 
       pck_StdSciRx.validity = False;
       buffer_pck_StdSciRx.cntr = 0;
       stt_StdSciRx = Idle;
     }
		 
     struct STDSCI_PACK_RX StdSci_Read(void){return pck_StdSciRx;}

// x.read received package
// -----------------------------------------------------------


// 5.CRC residue generator
// -----------------------------------------------------------
// Crc_Rsd = MOD[(frame[0]<<32+frame[1]<<24+frame[2]<<16+
//                frame[3]<<8),CRC]
//
// pck ---- data package, of which the CRC residue need to
//          be calculated;
//
// this function returns the CRC residue calculation result.
   Uint16 StdSci_CrcRsdGnrtr(union STDSCI_PACK pck)
   {
     Uint16 i = 0;
     Uint16 j = 0;
     Uint32 tmp_rsd = 0;

     for (i=0; i<(StdSci_FrameBytes-1); i++)
     {
       tmp_rsd += (Uint32)(pck.buffer[i]);
     
       if (tmp_rsd & 0x0100)
       {
         tmp_rsd ^= (StdSci_CRC<<1);
       }
       else
       {;}
     
       for(j=0; j<StdSci_CharBits; j++)
       {
         if(tmp_rsd & 0x0080)
         {
           tmp_rsd ^= StdSci_CRC;
         }
         else
         {;}
     
         tmp_rsd <<= 1;
       }
     } /*for (i=0; i<(StdSci_FrameBytes-1); i++)*/

     return (Uint16)tmp_rsd;

   }/*Uint16 StdSci_CrcRsdGnrtr(union STDSCI_PACK pck)*/

// 7.package transmit function
// -----------------------------------------------------------
// this function is called to transmit packed data through
// a certain SCI TX channel;
   void StdSci_Send(USART_TypeDef* USARTx, Uint16 frm_DataType, Uint16 frm_Data)
   {
     Uint16 i = 0;
     union STDSCI_PACK pck;

     pck.frame.PackHead = StdSci_PackHead;
     pck.frame.DataLwr  = frm_Data & 0xFF;
     pck.frame.DataHghr = frm_Data >> StdSci_CharBits;
     pck.frame.DataType = frm_DataType & 0xFF;
     pck.frame.CrcRsd   = StdSci_CrcRsdGnrtr(pck);

     for(i=0; i<StdSci_FrameBytes; i++)
     {
       USART_SendData(USARTx, pck.buffer[i]);
       while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
     }
   }

// 10.SCI RX interrupt server
// -----------------------------------------------------------

   void StdSci_Receive(USART_TypeDef* USARTx)
   {
     Uint16 frame;
     union STDSCI_PACK pck = buffer_pck_StdSciRx.pck;
     Uint16 offset = buffer_pck_StdSciRx.cntr;
		 
     if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET) //has RX INT flag been set?
     {
       frame = USART_ReceiveData(USART1);    // read RX data register

//       USART_SendData(USARTx,frame);
//       while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);

       switch (stt_StdSciRx)
       {
         case Idle:
           if(frame == StdSci_PackHead)
           {
             pck.frame.PackHead = frame;
             offset++;
             stt_StdSciRx = Receiving;
           }
           break;
         case Receiving:
           pck.buffer[offset] = frame;
      
           if((offset == (StdSci_FrameBytes-1))||((StdSci_FrameBytes-1)<offset))
           {
             offset = 0;
             stt_StdSciRx = Idle;
             
             if (frame == StdSci_CrcRsdGnrtr(pck))
             {
               pck_StdSciRx.pck = pck;
               pck_StdSciRx.validity = True;

             # if 0 /*only for test*/
               /*for test*/
               USART_SendData(USARTx,pck_StdSciRx.pck.buffer[0]);
               while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
               
               USART_SendData(USARTx,pck_StdSciRx.pck.buffer[1]);
               while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
               
               USART_SendData(USARTx,pck_StdSciRx.pck.buffer[2]);
               while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
               
               USART_SendData(USARTx,pck_StdSciRx.pck.buffer[3]);
               while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
               
               USART_SendData(USARTx,pck_StdSciRx.pck.buffer[4]);
               while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
               
               USART_SendData(USARTx,pck_StdSciRx.validity);
               while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
               /*for test*/
             # endif
             }
             else
             {
               pck_StdSciRx.validity = False;
             } /*if (frame == StdSci_CrcRsdGnrtr(pck))*/
           }
           else
           {
             offset++;
             stt_StdSciRx = Receiving;
           } /*if((offset == (StdSci_FrameBytes-1))||((StdSci_FrameBytes-1)<offset))*/

           break;
         default:;
       }/*switch (stt_StdSciRx)*/
     }/*if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)*/ 

     buffer_pck_StdSciRx.pck   =  pck;
     buffer_pck_StdSciRx.cntr  =  offset;
   }

// no more.
// -----------------------------------------------------------

