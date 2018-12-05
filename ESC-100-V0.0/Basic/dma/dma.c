// -----------------------------------------------------------
// FILE: dma.c
//
// Description: This is a template for newly created .c files.
//
// -----------------------------------------------------------
// Release Date: 2018-mm-dd;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "dma.h"

//
// 2nd. variables
// -----------------------------------------------------------
//   u32 ccr1_TIM2;
//	 u32 ccr3_TIM2;
//	 u32 ccr4_TIM2;
//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
// 1.DMA1 Channel1 Configurations
// ...........................................................
   /**
   @brief ...
   @param ...
   */
   void DMA_Config_DMA1_Ch1(u32 DMA_PeripheralBaseAddr, u32 DMA_MemoryBaseAddr)
   {
//   Parameter Declarations
//   .........................................................
		 DMA_InitTypeDef DMA_InitStruct;
//
//   Peripharel Clock
//   .........................................................
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//   Initialize DMA
//   .........................................................
//   peripharels connected to DMA channels must be enabled before
//
//   peripheral & memory base address
     DMA_InitStruct.DMA_PeripheralBaseAddr = DMA_PeripheralBaseAddr;//(u32)(&TIM2->CCR3);
     DMA_InitStruct.DMA_MemoryBaseAddr = DMA_MemoryBaseAddr;//(u32)&ccr3_TIM2;
//
//   data transfer deriction
     DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
//
//   number of transfers
     DMA_InitStruct.DMA_BufferSize = 1;
//
//   pointer incrementation
     DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
     DMA_InitStruct.DMA_MemoryInc = DMA_M2M_Disable;
//
//   data size
     DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
     DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
//
//   priority
     DMA_InitStruct.DMA_Priority = DMA_Priority_High;
//
//   circular mode
     DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
//
//   memory to memory
     DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
		 
     DMA_Init(DMA1_Channel1, &DMA_InitStruct);
//
//   Enable DMA
//   .........................................................
		 DMA_Cmd(DMA1_Channel1, ENABLE);
   }
//
// 2.DMA1 Channel2 Configurations
// ...........................................................
   /**
   @brief ...
   @param ...
   */
   void DMA_Config_DMA1_Ch2(void) {;}
//
// 3.DMA1 Channel3 Configurations
// ...........................................................
   /**
   @brief ...
   @param ...
   */
   void DMA_Config_DMA1_Ch3(void) {;}
//
// 4.DMA1 Channel4 Configurations
// ...........................................................
   /**
   @brief ...
   @param ...
   */
   void DMA_Config_DMA1_Ch4(void) {;}
//
// 5.DMA1 Channel5 Configurations
// ...........................................................
   /**
   @brief ...
   @param ...
   */
   void DMA_Config_DMA1_Ch5(u32 DMA_PeripheralBaseAddr, u32 DMA_MemoryBaseAddr)
   {
//   Parameter Declarations
//   .........................................................
		 DMA_InitTypeDef DMA_InitStruct;
//
//   Peripharel Clock
//   .........................................................
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//   Initialize DMA
//   .........................................................
//   peripharels connected to DMA channels must be enabled before
//
//   peripheral & memory base address
     DMA_InitStruct.DMA_PeripheralBaseAddr = DMA_PeripheralBaseAddr;//(u32)(&TIM2->CCR1);
     DMA_InitStruct.DMA_MemoryBaseAddr = DMA_MemoryBaseAddr;//(u32)&ccr1_TIM2;
//
//   data transfer deriction
     DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
//
//   number of transfers
     DMA_InitStruct.DMA_BufferSize = 1;
//
//   pointer incrementation
     DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
     DMA_InitStruct.DMA_MemoryInc = DMA_M2M_Disable;
//
//   data size
     DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
     DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
//
//   priority
     DMA_InitStruct.DMA_Priority = DMA_Priority_High;
//
//   circular mode
     DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
//
//   memory to memory
     DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
		 
     DMA_Init(DMA1_Channel5, &DMA_InitStruct);
//
//   Enable DMA
//   .........................................................
		 DMA_Cmd(DMA1_Channel5, ENABLE);
   }
//
// 6.DMA1 Channel6 Configurations
// ...........................................................
   /**
   @brief ...
   @param ...
   */
   void DMA_Config_DMA1_Ch6(void) {;}
//
// 7.DMA1 Channel7 Configurations
// ...........................................................
   /**
   @brief ...
   @param ...
   */
   void DMA_Config_DMA1_Ch7(u32 DMA_PeripheralBaseAddr, u32 DMA_MemoryBaseAddr)
   {
//   Parameter Declarations
//   .........................................................
		 DMA_InitTypeDef DMA_InitStruct;
//
//   Peripharel Clock
//   .........................................................
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//   Initialize DMA
//   .........................................................
//   peripharels connected to DMA channels must be enabled before
//
//   peripheral & memory base address
     DMA_InitStruct.DMA_PeripheralBaseAddr = DMA_PeripheralBaseAddr;//(u32)(&TIM2->CCR4);
     DMA_InitStruct.DMA_MemoryBaseAddr = DMA_MemoryBaseAddr;//(u32)&ccr4_TIM2;
//
//   data transfer deriction
     DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
//
//   number of transfers
     DMA_InitStruct.DMA_BufferSize = 1;
//
//   pointer incrementation
     DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
     DMA_InitStruct.DMA_MemoryInc = DMA_M2M_Disable;
//
//   data size
     DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
     DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
//
//   priority
     DMA_InitStruct.DMA_Priority = DMA_Priority_High;
//
//   circular mode
     DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
//
//   memory to memory
     DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
		 
     DMA_Init(DMA1_Channel7, &DMA_InitStruct);
//
//   Enable DMA
//   .........................................................
		 DMA_Cmd(DMA1_Channel7, ENABLE);
   }

// no more.
// -----------------------------------------------------------

