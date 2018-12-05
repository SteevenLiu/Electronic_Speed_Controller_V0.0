
//=============================================================================
// Copyright (C) 2017, Active-Semi International
//
// THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES,
// AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S
// APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL;
// (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT
// ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
// DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
// ONLY BY CERTAIN AUTHORIZED PERSONS.
//
//=============================================================================

#include "ESC_Parameter.h"

//#ifdef  ENABLE_USER_PARAMETER
//==================================================================================================
// @brief  This function initial auto run parameter for GUI
// @param  None
// @return None
//==================================================================================================
void ESC_Param_fill(void)
{
	BLDCM_Controller* motor_ptr;
//	u32 temp1;
	motor_ptr = &bldcm_m1;

//// The Para can be copied here start
//	//Please Copy the paras to user_parameter.c in FW.

//	//Advance setting
//	motor_ptr->commutation_advanced_rise = 1835008 ;
//	motor_ptr->commutation_advanced_fall = 1835008 ;


//	//Freq Setting
//	motor_ptr->app_pwm_freq_khz = 2097152 ;
//	motor_ptr->app_control_freq_khz = 2097152 ;
//	motor_ptr->main_machine_control_counts = 1 ;

//	motor_ptr->pwm_timer_ticks = 781 ;
////	pac5xxx_timer_base_config(TimerA, motor_ptr->pwm_timer_ticks, 0, TxCTL_MODE_UPDOWN, 0) ; // Configure Timer
////	pac5xxx_timer_cctrl_config(TimerA, 1, (motor_ptr->pwm_timer_ticks - 60), 1) ;

//	motor_ptr->one_div_pwm_timer_ticks_fix16 = fix16_div(65536,(motor_ptr->pwm_timer_ticks<<16));

//	motor_ptr->ratio_bw_pwmFreq_timerDFreq = 0x8312>>1 ; //100KHz


//	//Current Sensing Setting
//	motor_ptr->I_total_factor = 4003 ;
//	motor_ptr->app_over_current_resistor = 655360 ;
//	motor_ptr->app_amplifier_gain = 4 ;
//	motor_ptr->Iq_filter_gain = 10756 ;
//	motor_ptr->app_over_current_limit = 818 ;


//	//Current Limit Setting
//	if(motor_ptr->app_over_current_limit >= 1023)
//	{
//	   motor_ptr->app_over_current_limit = 1023;
//	}

//	init_over_current_limit(motor_ptr->app_over_current_limit);



//	//Speed PID Settings
//	motor_ptr->speed_pid.Kp = 131072 ;
//	motor_ptr->speed_pid.Ki = 65536 ;
//	motor_ptr->speed_pid.Ks = 131072 ;
//	motor_ptr->speed_pid.min_value = 0 ;
//	motor_ptr->speed_pid.max_value = 327680 ;
//	motor_ptr->speed_pid.Td = 2097 ;


//	//Current PID Settings
//	motor_ptr->Iq_pid.Kp = 327680 ;
//	motor_ptr->Iq_pid.Ki = 3276800 ;
//	motor_ptr->Iq_pid.Ks = 65536 ;
//	motor_ptr->Iq_pid.min_value = 0 ;
//	motor_ptr->Iq_pid.max_value = 65536000 ;
//	motor_ptr->Iq_pid.max_value = motor_ptr->pwm_timer_ticks << 16 ;

//	motor_ptr->Iq_pid.Td = 2097 ;


//	//Motor Control Settings
//	//Auto CloseLoop
//	bldc_align_go.auto_acceleration_mode	= 1 ;
//	//Reverse
//	motor_ptr->reverse_tune_flag = 0 ;

//	//OC Reset
//	motor_ptr->oc_reset_flag = 1 ;

//	motor_ptr->motor_auto_blank_percent = 19660 ;
//	motor_ptr->num_of_good_zc_samples = 1 ;


//	//Motor OL Speed Setting
//	bldc_align_go.align_ticks = 20 ;
//	bldc_align_go.start_speed_hz = 65536 ;
//	bldc_align_go.accel_rate_time_base = 32768 ;
//	bldc_align_go.switch_speed_hz = 1310720 ;

//	motor_ptr->Iq_ref_sp = 196608 ;
//	motor_ptr->Iq_ramp_rate = 65536000 ;
//	motor_ptr->align_pwm_duty_max = 13107 ;

//	//Motor CL Speed Setting
//	motor_ptr->motor_close_loop_speed = 13107200 ;
//	motor_ptr->motor_close_loop_speed_ramp = 13107200 ;

//	//Motor CL Current Setting
//	motor_ptr->motor_close_loop_current = 65536 ;

//	//Motor CL PWM Setting
	  motor_ptr->pwm_control_duty_cycle = 0;//19660 ;
    motor_ptr->pwm_control_duty_change_delay_counts = PWM_Control_Duty_Change_Delay;


//	//PPD Settings
//	motor_control_ppd.ppd_detect_rising_tick = 117 ;
//	motor_control_ppd.ppd_detect_falling_tick = 35 ;
//	motor_control_ppd.ppd_detect_count = 5 ;
//	motor_control_ppd.ppd_smooth_count_target = 3 ;
//	motor_control_ppd.ppd_tune_duty_ramp = 250 ;
//	motor_control_ppd.ppd_tuning_last_count = 177 ;


//	motor_ptr->app_speed_command = 3255 ;
//	app_amplifier_gain_init(motor_ptr->app_amplifier_gain);
//	bldc_align_go.align_go_duty_cycle = 156 ;
//	bldc_align_go.align_go_duty_cycle_store = bldc_align_go.align_go_duty_cycle;
//	bldc_align_go.align_ticks_store = bldc_align_go.align_ticks;
////motor_ptr->pwm_control_duty_cycle = 0;//234 ;
//	motor_ptr->coasting_timeout = 0 ;

//	motor_ptr->control_mode_select_number = 2 ;

}

//#endif



