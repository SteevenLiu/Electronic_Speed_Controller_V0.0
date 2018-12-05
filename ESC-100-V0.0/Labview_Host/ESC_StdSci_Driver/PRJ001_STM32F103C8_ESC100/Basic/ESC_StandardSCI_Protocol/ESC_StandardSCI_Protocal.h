// -----------------------------------------------------------
// File: ESC_StandardSCI_Protocal.h
//
// Discription: SCI communication format supportive macros,
// types and declarations.
//
// -----------------------------------------------------------
// Release Date: 2018-08-24;
// Authour: Steven Liu;
// -----------------------------------------------------------
 # include "ESC_Device.h"
 # include "ESC_TypeDef.h"
// 1st.protocol 
//   .........................................................
//   a.frame:
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//     stop bits -- CONFIG_STOPBIT
//     parity    -- CONFIG_PARITY
//     char-bits -- CONFIG_CHRBITS
//
//   b.package:
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//     frame-bytes -- FRM_BYTS
//
//     lowest address ¡ý
//     1st-frame ---- PCK_HEAD (package head) 
//     2nd-frame ---- lower 8 bits of data (0x00 to 0xFF)
//     3rd-frame ---- higher 8 bits of data (0x00 to 0xFF)
//     4th-frame ---- data type (TBD)
//     5th-frame ---- CRC residue (0x00 to 0xFF)
//     highest address ¡ý
//
//   c.CRC residue generating mathod
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//     G(7) = 2^7+2^6+2^1+1
//          = STDSCI_CRC
//
//   d.data type -- the 4th-fram
//
//   e.baud rate -- 115200
//
// 2nd.frames
//   .........................................................
//   # define CONFIG_STOPBIT
//   # define CONFIG_PARITY
     # define StdSci_CharBits 8
//   a.1st frame:
     # define StdSci_PackHead 0xAA
//
//   b.2nd to 4th frame:
//     defined by user
//
//   c.5th frame: 
     # define StdSci_CRC 0x00C3
//
//   b.others
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//     the number of frame in a package:
     # define StdSci_FrameBytes 5
		 
		 # define StdSci_RxBuffLength 32
//
// 3rd.supportive data structure
//   .........................................................
//   a package structure defines each frame:
     struct STDSCI_FRAME
     {
       Uint16 PackHead; // head
       Uint16 DataLwr;  // lower 8 bits of data
       Uint16 DataHghr; // higher 8 bits of data
       Uint16 DataType; // data type
       Uint16 CrcRsd;   // CRC residue
     };
//
//   a union combines the package frames with a indexed
//   array:
     union STDSCI_PACK
     {
       Uint16 buffer[StdSci_FrameBytes];    // indexed array
       struct STDSCI_FRAME frame; // structured frames
     };

		 struct STDSCI_PACK_RX
     {
       union STDSCI_PACK pck;
       enum Boole validity;
     };
		 
		 struct STDSCI_PACK_BUFF
     {
       union STDSCI_PACK pck;
       Uint16 cntr;
     };
//
// 4th.externs and function prototypes
//   .........................................................
//   package put to the SCI transmitter
//   extern union FHDAT_PCK_0v0 PckTx_FH_0v0;
//
//   package get from the SCI receiver
//   extern union FHDAT_PCK_0v0 PckRx_FH_0v0;
//
//   data pack up function
//   union FHDAT_PCK_0v0 tx_pack(Uint16 datatype, Uint16 data);
//
//   data transmit function
     void StdSci_Send(USART_TypeDef* USARTx, Uint16 frm_DataType, Uint16 frm_Data);
		 void StdSci_Receive(USART_TypeDef* USARTx);
		 struct STDSCI_PACK_RX StdSci_Read(void);
     void InitVrbls_StdSci (void);

// no more.
// ...........................................................

