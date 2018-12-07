// -----------------------------------------------------------
// FILE: usart.c
//
// Description: Usart drivers.
//
// -----------------------------------------------------------
// Release Date: 2018-09-06;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "usart.h"
//
// 2nd.funcions
// -----------------------------------------------------------
// 1.USART1 configuration
// ...........................................................
   /**
   @brief Configure USART1.
   @param baud: Baud rate.
   @retval None.
   */
   void USART1_Init(u32 baud)
   { 
//   Parameter Declarations
//   ............................................................................
     GPIO_InitTypeDef  GPIO_InitStructure;      //GPIO
     USART_InitTypeDef USART_InitStructure;    //USART
//   NVIC_InitTypeDef  NVIC_InitStructure;      //NVIC

//   Peripharel Clock
//   ............................................................................
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

//   IO port configuration
//   ............................................................................
//   USART1_TX
     GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
     GPIO_Init(GPIOA, &GPIO_InitStructure);  
		 
//   USART1_RX
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
     GPIO_Init(GPIOA, &GPIO_InitStructure);

     GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
     GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);

//   USART configuration
//   ............................................................................
     USART_InitStructure.USART_BaudRate = baud;                  // baud rate
     USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 8 word-bit
     USART_InitStructure.USART_StopBits = USART_StopBits_1;      // 1 stop-bit
     USART_InitStructure.USART_Parity = USART_Parity_No;         // no parity
     USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // no hardware flow control
     USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // receive and send

     USART_Init(USART1, &USART_InitStructure);

     USART_Cmd(USART1, ENABLE);  // enable usart1
   }

// no more.
// -----------------------------------------------------------

