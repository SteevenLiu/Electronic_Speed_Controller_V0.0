// -----------------------------------------------------------
// FILE: ESC_Device.h
//
// Description: 
//
// -----------------------------------------------------------
// Release Date: 2018-08-27;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
#ifndef __ESC_DEVICE_H
#define __ESC_DEVICE_H

// 1st.macros
// -----------------------------------------------------------
// # include "stm32f10x.h"
 # include "stm32f30x.h"

// ARR_PWM_CAP  | 6999    | 7199
// PSC_PWM_CAP  | 24      | 24
// Capture Freq | 411.4Hz | 400Hz
 # define ARR_PWM_CAP 6999
 # define PSC_PWM_CAP 24
 
 # define ARR_HALL_CAP 0x1FFFFFFF
 # define PSC_HALL_CAP 0

// ARR_PWM_DAC  | 1799    |
// PSC_PWM_DAC  | 0       |
// PWM Freq     | 20kHz   |
 # define ARR_PWM_DAC 1799
 # define PSC_PWM_DAC 0

// ARR_PWM_CHPR       |2399   | 1799   |1199   |
// PSC_PWM_CHPR       |0      | 0      |0      |
// PWM Freq (Up-Down) |15kHz  | 20kHz  |30kHz  |
// PWM Freq (Up/Down) |30kHz  | 40kHz  |60kHz  |
 # define ARR_PWM_DRV 1199
 # define PSC_PWM_DRV 0

// UBus   |50V         |75V         |100V       |
// Value  |900         |1800        |3600       |
// Period |18ms(30kHz) |32ms(30kHz) |           |
 # define PWM_Control_Duty_Change_Delay 1800

// UBus   |50V   |75V   |100V  |
// Value  |16    |8     |4     |
// # define PWM_Control_Duty_StartUp 8
# define PWM_Control_Duty_StartUp 16

//
// 2nd.datatypes
// -----------------------------------------------------------
// /* define types here */
   typedef enum {True = 0x0001, False = 0x0000}Boole;

//
// 3rd. variables
// -----------------------------------------------------------
// /* define variables here */
//
// 4th.function prototypes
// -----------------------------------------------------------
#endif /*#ifndef __ESC_DEVICE_H*/
// no more.
// -----------------------------------------------------------/
