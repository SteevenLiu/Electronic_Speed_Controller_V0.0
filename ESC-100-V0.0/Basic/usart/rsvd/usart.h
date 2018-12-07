#ifndef __USART_H
#define __USART_H
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"	
//#include "sys.h"

# include "sys.h"

#define USART_n		USART1  //����ʹ��printf�����Ĵ��ڣ���������Ҫʹ��USART_printfר�ú�������

#define USART1_REC_LEN  			200  	//����USART1�������ֽ���
#define USART2_REC_LEN  			200  	//����USART2�������ֽ���
#define USART3_REC_LEN  			200  	//����USART3�������ֽ���

//��ʹ��ĳ������ʱҪ��ֹ�˴��ڣ��Լ��ٱ�����
#define EN_USART1 			1		//ʹ�ܣ�1��/��ֹ��0������1
#define EN_USART2 			0		//ʹ�ܣ�1��/��ֹ��0������2
#define EN_USART3 			0		//ʹ�ܣ�1��/��ֹ��0������3

//# define USART1_RCC_GpioPort RCC_AHBPeriph_GPIOA
//# define USART1_Af_PinSource_TX GPIO_PinSource9
//# define USART1_Af_PinSource_RX GPIO_PinSource10

//# define USART1_TX_GpioPort  GPIOA
//# define USART1_RX_GpioPort  GPIOA
//# define USART1_TX_GpioPin   GPIO_Pin_9
//# define USART1_RX_GpioPin   GPIO_Pin_10

# define USART2_TX_GpioPort
# define USART2_RX_GpioPort
# define USART2_TX_GpioPin 
# define USART2_RX_GpioPin 

# define USART3_TX_GpioPort 
# define USART3_RX_GpioPort 
# define USART3_TX_GpioPin 
# define USART3_RX_GpioPin 

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
 
extern u16 USART1_RX_STA;         		//����״̬���	
extern u16 USART2_RX_STA;         		//����״̬���	
extern u16 USART3_RX_STA;         		//����״̬���	

//��������
void USART1_Init(u32 baud);//����1��ʼ��������
void USART2_Init(u32 bound);//����2��ʼ��������
void USART3_Init(u32 bound);//����3��ʼ��������
void USART1_printf(char* fmt,...); //����1��ר��printf����
void USART2_printf(char* fmt,...); //����2��ר��printf����
void USART3_printf(char* fmt,...); //����3��ר��printf����

#endif

