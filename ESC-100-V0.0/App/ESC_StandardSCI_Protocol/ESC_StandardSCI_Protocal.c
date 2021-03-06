// -----------------------------------------------------------
// File: ESC_StandardSCI_Protocal.c
// Description: Defines mathods for standard package receiving
// and sending.
// -----------------------------------------------------------
// Release Date: 2018-08-24;
// Authour: Liu Shiwei;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
// # include "stm32f10x_usart.h"
 # include "ESC_BLDCM_Config.h"
 # include "ESC_StandardSCI_Protocal.h"

//   extern STDSCI_PACK_TX pck_STD_TX_0xA0; //2018.11.16 temp
//   extern STDSCI_PACK_TX pck_STD_TX_0xA1; //2018.11.16 temp
// 2nd.variables
// -----------------------------------------------------------
	 STDSCI_BLOCK_TX block_tx;
   STDSCI_PACK_BUFF pack_rx_buff;

//
// 3rd.functions
// -----------------------------------------------------------
// 1.CRC residue generator
// ...........................................................
   /**
   @brief Generate CRC residue.
          Crc_Rsd = MOD[(frame[0]<<32+frame[1]<<24+
                        frame[2]<<16+frame[3]<<8),CRC]
    
   @param pck: SCI data pack which the generator is applied to
   @retval CRC residue.
   */
   u16 StdSci_CrcRsdGnrtr(STDSCI_PACK pck)
   { 
     u32 tmp_rsd = 0;

     tmp_rsd += (u32)(pck.buffer[0]);
     if(tmp_rsd & 0x0100) tmp_rsd ^= (StdSci_CRC<<1);
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,0
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,1
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,2
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,3
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,4
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,5
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,6
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //0,7
     tmp_rsd <<= 1;

     tmp_rsd += (u32)(pck.buffer[1]);
     if(tmp_rsd & 0x0100) tmp_rsd ^= (StdSci_CRC<<1);
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,0
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,1
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,2
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,3
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,4
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,5
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,6
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //1,7
     tmp_rsd <<= 1;

     tmp_rsd += (u32)(pck.buffer[2]);
     if(tmp_rsd & 0x0100) tmp_rsd ^= (StdSci_CRC<<1);
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,0
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,1
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,2
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,3
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,4
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,5
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,6
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //2,7
     tmp_rsd <<= 1;

     tmp_rsd += (u32)(pck.buffer[3]);
     if(tmp_rsd & 0x0100) tmp_rsd ^= (StdSci_CRC<<1);
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,0
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,1
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,2
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,3
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,4
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,5
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,6
     tmp_rsd <<= 1;
     if(tmp_rsd & 0x0080) tmp_rsd ^= StdSci_CRC; //3,7
     tmp_rsd <<= 1;
		 
     return (u16)tmp_rsd;
   }/*u16 StdSci_CrcRsdGnrtr(union STDSCI_PACK pck)*/
//
   u16 StdSci_CrcRsdGnrtr_Rsvd(STDSCI_PACK pck)
   {
     u16 i = 0;
     u16 j = 0;
     u32 tmp_rsd = 0;

     for (i=0; i<(StdSci_FrameBytes-1); i++)
     {
       tmp_rsd += (u32)(pck.buffer[i]);
     
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

     return (u16)tmp_rsd;

   }/*u16 StdSci_CrcRsdGnrtr(union STDSCI_PACK pck)*/
//
// 2.package initialization for transmitting
// ...........................................................
   /**
   @brief Transmitting package initialization routine.
   @param frm_DataType: Data type frame.
	 @param ptx_ptr: Pointer to SCI package.
	 @param ptx_ptr_link: Linkage Pointer to SCI package.
   @retval None.
   */		 
   void STDSCI_PACK_TX_Init(u16 frm_DataType,  \
     struct STDSCI_PACK_TX* ptx_ptr,           \
     struct STDSCI_PACK_TX* ptx_ptr_link)
   {
     ptx_ptr->pck.frame.PackHead = StdSci_PackHead;
     ptx_ptr->pck.frame.DataType = frm_DataType;
		 ptx_ptr->ptr_next_pck = ptx_ptr_link;
		 ptx_ptr->index = 0;
		 ptx_ptr->flag_pck_renewed = False;
     ptx_ptr->overrun = False;
		 ptx_ptr->tick = 0;
   }	 
//
// 3.block initialization for transmitting
// ...........................................................
   /**
   @brief Transmitting block of package initialization rutine.
   @param None.
   @retval None.
   */
   void STDSCI_BLOCK_TX_Init(void)
   {
     STDSCI_BLOCK_TX* btx_ptr;
     btx_ptr = &block_tx;

     btx_ptr->tick = 0;

     btx_ptr->thread_ptx_ptr = &(btx_ptr->pck_0x00);

     STDSCI_PACK_TX_Init(CMD_MotorEnable, btx_ptr->thread_ptx_ptr, &(btx_ptr->pck_0x01));
		 
     STDSCI_PACK_TX_Init(CMD_MotorEnable, &(btx_ptr->pck_0x01), &(btx_ptr->pck_0x02));
     STDSCI_PACK_TX_Init(CMD_TargetSpeed, &(btx_ptr->pck_0x02), &(btx_ptr->pck_0x03));
     STDSCI_PACK_TX_Init(CMD_TargetDuty, &(btx_ptr->pck_0x03), &(btx_ptr->pck_0x04));
     STDSCI_PACK_TX_Init(CMD_TargetCurrent, &(btx_ptr->pck_0x04), &(btx_ptr->pck_0x10));

     STDSCI_PACK_TX_Init(Config_SpeedPid_Ki, &(btx_ptr->pck_0x10), &(btx_ptr->pck_0x11));
     STDSCI_PACK_TX_Init(Config_SpeedPid_Kp, &(btx_ptr->pck_0x11), &(btx_ptr->pck_0x80));
	 
     STDSCI_PACK_TX_Init(State_MainStateMachine, &(btx_ptr->pck_0x80), &(btx_ptr->pck_0x81));
     STDSCI_PACK_TX_Init(State_ControlStateMachine, &(btx_ptr->pck_0x81), &(btx_ptr->pck_0x82));
     STDSCI_PACK_TX_Init(State_HallObStateMachine, &(btx_ptr->pck_0x82), &(btx_ptr->pck_0x90));

     STDSCI_PACK_TX_Init(FeedBack_AppStatus, &(btx_ptr->pck_0x90), &(btx_ptr->pck_0x91));
     STDSCI_PACK_TX_Init(FeedBack_iBus, &(btx_ptr->pck_0x91), &(btx_ptr->pck_0x98));
     STDSCI_PACK_TX_Init(FeedBack_PwmDuty, &(btx_ptr->pck_0x98), &(btx_ptr->pck_0xA0));

     STDSCI_PACK_TX_Init(FeedBack_SpeedAverage_L16, &(btx_ptr->pck_0xA0), &(btx_ptr->pck_0xA1));
     STDSCI_PACK_TX_Init(FeedBack_SpeedAverage_H16, &(btx_ptr->pck_0xA1), &(btx_ptr->pck_0xA2));
     STDSCI_PACK_TX_Init(FeedBack_SpeedReference_L16, &(btx_ptr->pck_0xA2), &(btx_ptr->pck_0xA3));
     STDSCI_PACK_TX_Init(FeedBack_SpeedReference_H16, &(btx_ptr->pck_0xA3), &(btx_ptr->pck_0xA4));
     STDSCI_PACK_TX_Init(FeedBack_ReferenceError_L16, &(btx_ptr->pck_0xA4), &(btx_ptr->pck_0xA5));
     STDSCI_PACK_TX_Init(FeedBack_ReferenceError_H16, &(btx_ptr->pck_0xA5), &(btx_ptr->pck_0xB0));

     STDSCI_PACK_TX_Init(FeedBack_HallState, &(btx_ptr->pck_0xB0), &(btx_ptr->pck_0xB1));
     STDSCI_PACK_TX_Init(FeedBack_PWM_NUM_Measured, &(btx_ptr->pck_0xB1), &(btx_ptr->pck_0xB2));
     STDSCI_PACK_TX_Init(FeedBack_PWM_NUM_Predicted, &(btx_ptr->pck_0xB2), &(btx_ptr->pck_0xB3));
     STDSCI_PACK_TX_Init(FeedBack_PWM_NUM_Difference, &(btx_ptr->pck_0xB3), &(btx_ptr->pck_0xC0));

     STDSCI_PACK_TX_Init(FeedBack_CDE_SMC, &(btx_ptr->pck_0xC0), &(btx_ptr->pck_0xC1));
     STDSCI_PACK_TX_Init(FeedBack_CDE_SMM, &(btx_ptr->pck_0xC1), &(btx_ptr->pck_0xE0));

     STDSCI_PACK_TX_Init(FeedBack_Test_0_Long_L16, &(btx_ptr->pck_0xE0), &(btx_ptr->pck_0xE1));
     STDSCI_PACK_TX_Init(FeedBack_Test_0_Long_H16, &(btx_ptr->pck_0xE1), &(btx_ptr->pck_0xE2));
     STDSCI_PACK_TX_Init(FeedBack_Test_1_Long_L16, &(btx_ptr->pck_0xE2), &(btx_ptr->pck_0xE3));
     STDSCI_PACK_TX_Init(FeedBack_Test_1_Long_H16, &(btx_ptr->pck_0xE3), &(btx_ptr->pck_0xF0));

     STDSCI_PACK_TX_Init(FeedBack_Test_0, &(btx_ptr->pck_0xF0), &(btx_ptr->pck_0xF1));
     STDSCI_PACK_TX_Init(FeedBack_Test_1, &(btx_ptr->pck_0xF1), &(btx_ptr->pck_0xF2));
     STDSCI_PACK_TX_Init(FeedBack_Test_2, &(btx_ptr->pck_0xF2), &(btx_ptr->pck_0xF3));
     STDSCI_PACK_TX_Init(FeedBack_Test_3, &(btx_ptr->pck_0xF3), &(btx_ptr->pck_0xF4));
     STDSCI_PACK_TX_Init(FeedBack_Test_4, &(btx_ptr->pck_0xF4), btx_ptr->thread_ptx_ptr);
   }
//
// 4.block initialization for receiving
// ...........................................................
   /**
   @brief Receiving block of packages initialization.
   @param None.
   @retval None.
   */		 
   void STDSCI_BUFF_RX_Init(void)
   {
     STDSCI_PACK_BUFF* prx_ptr; 
     prx_ptr = &pack_rx_buff;

     prx_ptr->pck.frame.PackHead = StdSci_PackHead;
     prx_ptr->offset = 0;
		 prx_ptr->state = Idle;
   }
//
// 5.routine setting transmitting package 
// ...........................................................
   /**
   @brief transmitting package set routine.
   @param ptx_ptr: Pointer to package for transmitting.
   @param frm_Data: Data frame.
   @retval None.
   */
   Boole SET_STDSCI_PACK_TX(struct STDSCI_PACK_TX* ptx_ptr, u16 frm_Data)
   {
     STDSCI_BLOCK_TX* btx_ptr;
     u16 frm_Data_pre = 0;
		 Boole overrun = False;
		 btx_ptr = &block_tx;

   # if StdSci_TX_OverRun
     if(btx_ptr->thread_ptx_ptr != ptx_ptr)//ptx_ptr->index == 0)
     {		 
       frm_Data_pre  = ptx_ptr->pck.frame.DataLwr;
       frm_Data_pre	|= (ptx_ptr->pck.frame.DataHghr)<<StdSci_CharBits;
			 
       if(frm_Data_pre != frm_Data)
       {
         ptx_ptr->pck.frame.DataLwr = frm_Data&0xFF;
         ptx_ptr->pck.frame.DataHghr = frm_Data>>StdSci_CharBits;
//				 ptx_ptr->pck.frame.CrcRsd = StdSci_CrcRsdGnrtr(ptx_ptr->pck);
				 if (ptx_ptr->flag_pck_renewed == True) overrun = True;
			   else ptx_ptr->flag_pck_renewed = True;
       }
     }
   # else
		 if((ptx_ptr->index == 0) && (ptx_ptr->flag_pck_renewed == 0))
     {		 
       frm_Data_pre  = ptx_ptr->pck.frame.DataLwr;
       frm_Data_pre	|= (ptx_ptr->pck.frame.DataHghr)<<StdSci_CharBits;
			 
       if(frm_Data_pre != frm_Data)
       {
         ptx_ptr->pck.frame.DataLwr = frm_Data&0xFF;
         ptx_ptr->pck.frame.DataHghr = frm_Data>>StdSci_CharBits;
//				 ptx_ptr->pck.frame.CrcRsd = StdSci_CrcRsdGnrtr(ptx_ptr->pck);
			   ptx_ptr->flag_pck_renewed = 1;
       }
     }
   # endif		 
		 return overrun;
   }
//
// t1.routine setting transmitting package 
// ...........................................................
   /**
   @brief transmitting package set routine.
   @param ptx_ptr: Pointer to package for transmitting.
   @param frm_Data: Data frame.
   @retval None.
   */
   void SET_STDSCI_PACK_TX_OVERRUN(struct STDSCI_PACK_TX* ptx_ptr, u16 frm_Data)
   {
     STDSCI_BLOCK_TX* btx_ptr;
		 btx_ptr = &block_tx;

     if(btx_ptr->thread_ptx_ptr != ptx_ptr)//ptx_ptr->index == 0)
     {
       ptx_ptr->pck.frame.DataLwr = frm_Data&0xFF;
       ptx_ptr->pck.frame.DataHghr = frm_Data>>StdSci_CharBits;
//       ptx_ptr->pck.frame.CrcRsd = StdSci_CrcRsdGnrtr(ptx_ptr->pck);
       if (ptx_ptr->flag_pck_renewed == True)
       {
         ptx_ptr->overrun = True;//overrun = True;
       }
       else
       {
         ptx_ptr->flag_pck_renewed = True;
         ptx_ptr->overrun = False;
       }
     }
   }
//
// t3.routine setting transmitting package at time interval
// ...........................................................
   /**
   @brief transmitting package set routine.
   @param ptx_ptr: Pointer to package for transmitting.
   @param frm_Data: Data frame.
   @retval None.
   */
   void SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(struct STDSCI_PACK_TX* ptx_ptr, u16 frm_Data, u32 interval)
   {
		 if(ptx_ptr->flag_pck_renewed == False)
     {
       if(ptx_ptr->tick++ >interval) ptx_ptr->tick = 0;
     }
     else
     {
       ptx_ptr->tick = 0;
     }

     if (ptx_ptr->tick == interval)
     {
       SET_STDSCI_PACK_TX_OVERRUN(ptx_ptr, frm_Data);
     }
	 }
//
// 6.routine setting transmitting package for 32-bit data
// ...........................................................
   /**
   @brief transmitting package set routine.
   @param ptx_ptr: Pointer to package for transmitting.
   @param frm_Data: Data frame.
   @retval None.
   */
   void SET_STDSCI_PACK_32_TX_OVERRUN( struct STDSCI_PACK_TX* ptx_L16_ptr, \
                                       struct STDSCI_PACK_TX* ptx_H16_ptr, \
                                       u32 frm_Data)
   {
     STDSCI_BLOCK_TX* btx_ptr;
		 btx_ptr = &block_tx;

		 u16 frm_Data_L16;
		 u16 frm_Data_H16;

//   32-bit pack not been transmitting
     if((btx_ptr->thread_ptx_ptr != ptx_L16_ptr) && \
        (btx_ptr->thread_ptx_ptr != ptx_H16_ptr))
     {
       frm_Data_L16 = (u16)(frm_Data & 0xFFFF);
       frm_Data_H16 = (u16)((frm_Data >>16) & 0xFFFF);

       ptx_L16_ptr->pck.frame.DataLwr = frm_Data_L16&0xFF;
       ptx_L16_ptr->pck.frame.DataHghr = frm_Data_L16>>StdSci_CharBits;
//       ptx_L16_ptr->pck.frame.CrcRsd = StdSci_CrcRsdGnrtr(ptx_L16_ptr->pck);
//       if (ptx_L16_ptr->flag_pck_renewed == True) overrun = True;
//       else ptx_L16_ptr->flag_pck_renewed = True;

       ptx_H16_ptr->pck.frame.DataLwr = frm_Data_H16&0xFF;
       ptx_H16_ptr->pck.frame.DataHghr = frm_Data_H16>>StdSci_CharBits;
//       ptx_H16_ptr->pck.frame.CrcRsd = StdSci_CrcRsdGnrtr(ptx_H16_ptr->pck);
//       if (ptx_H16_ptr->flag_pck_renewed == True) overrun = True;
//       else ptx_H16_ptr->flag_pck_renewed = True;

			 if (ptx_L16_ptr->flag_pck_renewed == True)
       {
         ptx_L16_ptr->overrun = True;
       }
       else
       {
         ptx_L16_ptr->flag_pck_renewed = True;
         ptx_L16_ptr->overrun = False;
       }

			 if (ptx_H16_ptr->flag_pck_renewed == True)
       {
         ptx_H16_ptr->overrun = True;
       }
       else
       {
         ptx_H16_ptr->flag_pck_renewed = True;
         ptx_H16_ptr->overrun = False;
       }
     }
   }
//
// t2.routine setting transmitting package for 32-bit data
// at time interval
// ...........................................................
   /**
   @brief transmitting package set routine.
   @param ptx_ptr: Pointer to package for transmitting.
   @param frm_Data: Data frame.
   @retval None.
   */
   void SET_STDSCI_PACK_32_TX_OVERRUN_INTERVAL( struct STDSCI_PACK_TX* ptx_L16_ptr, \
                                                struct STDSCI_PACK_TX* ptx_H16_ptr, \
                                                u32 frm_Data, u32 interval)
   {
     if (ptx_L16_ptr->tick == interval)
     {
       SET_STDSCI_PACK_32_TX_OVERRUN(ptx_L16_ptr, ptx_H16_ptr, frm_Data);
     }
		 if(ptx_L16_ptr->flag_pck_renewed == False)
     {
       if(ptx_L16_ptr->tick++ >interval) ptx_L16_ptr->tick = 0;
     }
     else
     {
       ptx_L16_ptr->tick = 0;
     }
	 }
//
// 7.routine transmitting block of data packages
// ...........................................................
   /**
   @brief ...
   @param USARTx: USART channel label.
   @retval None.
   */
   void StdSci_Send_in_ISR(USART_TypeDef* USARTx)
   {
		 STDSCI_BLOCK_TX* btx_ptr;
     struct STDSCI_PACK_TX* ptx_ptr;

		 btx_ptr = &block_tx;
		 ptx_ptr = btx_ptr->thread_ptx_ptr;

//   USART TX isn't busy
		 if(USART_GetFlagStatus(USARTx, USART_FLAG_TC))
     {
//     data hasn't been renewed yet
			 if(ptx_ptr->flag_pck_renewed == False)
       {
//       go to next pack
 		     btx_ptr->thread_ptx_ptr = ptx_ptr->ptr_next_pck;
       }
//     data transmition hasn't been completed
			 else if(ptx_ptr->index < StdSci_FrameBytes)
			 {
				 if(ptx_ptr->index == 0) ptx_ptr->pck.frame.CrcRsd = StdSci_CrcRsdGnrtr(ptx_ptr->pck);
			 
         USART_SendData(USARTx, ptx_ptr->pck.buffer[(ptx_ptr->index)++]);
				 
//       the last frame has been push into USART TX buffer
         if((ptx_ptr->index > StdSci_FrameBytes)||(StdSci_FrameBytes == ptx_ptr->index))
         {
           ptx_ptr->index = 0;
					 ptx_ptr->flag_pck_renewed = False;
 		       btx_ptr->thread_ptx_ptr = ptx_ptr->ptr_next_pck;
           btx_ptr->flag_TC = True;					 
				 }
       } /*if(ptx_ptr->flag_pck_renewed == 0)*/
     } /*if(USART_GetFlagStatus(USARTx, USART_FLAG_TC))*/
   }
//
// 8.routine for block of data package receiving
// ...........................................................
   /**
   @brief ...
   @param USARTx: USART channel label.
   @retval None.
   */
   void StdSci_Receive_in_ISR(USART_TypeDef* USARTx)
   {
     u16 frame;

     STDSCI_PACK_BUFF* prx_ptr; 
     prx_ptr = &pack_rx_buff;
		 
//   check if RX INT flag has been set?
     if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
     {
//     read RX data register
       frame = USART_ReceiveData(USARTx);

       switch (prx_ptr->state)//btx_ptr->pck_0x00.state)
       {
         case Idle:
           if(frame == StdSci_PackHead)
           {
             prx_ptr->offset ++;
             prx_ptr->state = Receiving;
           }
         break;
         case Receiving:
           prx_ptr->pck.buffer[prx_ptr->offset] = frame;

           if((prx_ptr->offset == (StdSci_FrameBytes-1)) || \
						  ((StdSci_FrameBytes-1)<prx_ptr->offset))
           {
             prx_ptr->offset = 0;
             prx_ptr->state = Idle;
           }
           else
           {
             prx_ptr->offset ++;
           } /*if((brx_ptr->buff.offset == (StdSci_FrameBytes-1)) || \
						  ((StdSci_FrameBytes-1)<brx_ptr->buff.offset))*/
         break;
         default:;
       }/*switch (stt_StdSciRx)*/

       USART_ClearITPendingBit (USARTx, USART_IT_RXNE);
     } /*if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)*/
   }
//
// no more.
// -----------------------------------------------------------

