// -----------------------------------------------------------
// FILE: dma.h
//
// Description: This is a template for newly created .h files.
//
// -----------------------------------------------------------
// Release Date: 2018-mm-dd;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __DMA_H
#define __DMA_H
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"
//
// 2nd.datatypes
// -----------------------------------------------------------
   /**
   @brief
   */
   /* define types here */

//
// 3rd. variables
// -----------------------------------------------------------
   /* define variables here */

//
// 4th.function prototypes
// -----------------------------------------------------------
   //void DMA_Config_DMA1_Ch1(void);
   void DMA_Config_DMA1_Ch1(u32 DMA_PeripheralBaseAddr, u32 DMA_MemoryBaseAddr);
   void DMA_Config_DMA1_Ch5(u32 DMA_PeripheralBaseAddr, u32 DMA_MemoryBaseAddr);
   void DMA_Config_DMA1_Ch7(u32 DMA_PeripheralBaseAddr, u32 DMA_MemoryBaseAddr);
#endif/*#ifndef __DMA_H*/
// no more.
// ----------------------------------------------------------- 

