
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

#include "ESC_StateMachine.h"

//===================================================================================
/// @brief  This function is main process
/// @param  None
/// @return None
//===================================================================================
void main_state_machine(void)
{
	BLDCM_Controller* motor_ptr;
  Hall_Observer* hall_ptr;

	motor_ptr = &bldcm_m1;
  hall_ptr = &bldcm_hall_observer_m1;

  STDSCI_BLOCK_TX* btx_ptr;
  btx_ptr = &block_tx;

//  Hall_Sensor* hall_ptr;
//  hall_ptr = &bldcm_hall_sensor_m1;
//	Sim_Detect* sim_ptr;
//	sim_ptr = &bldc_sim_m1;

//	if(!motor_ptr->motor_enable_cmd)
//	{
//	#ifdef 	MOTOR_STOP_BRAKING_ENABLE
//		if((main_machine_state == STATE_MAIN_CL_SPEED)||(main_machine_state == STATE_MAIN_CL_CURRENT)\
//				||(main_machine_state == STATE_MAIN_CL_PWM_DUTY))
//		{
//			pwm_disable();
//			//Disable TimerC&TimerD interrupt
//			NVIC_DisableIRQ(TimerC_IRQn);
//			NVIC_DisableIRQ(TimerD_IRQn);
//			braking_init();
//			sim_ptr->in_braking_state_counts = 0;
//			sim_ptr->braking_depth_pwm_duty_counts = 0;
//			sim_ptr->braking_detect_motor_stop_flag = 0;
//			bldc_align_go.align_and_go_state = STATE_STARTUP_INIT;
//			control_machine_state = STATE_CONTROL_BRAKING_PWM_CONTROL;
//			main_machine_state = STATE_MAIN_STOP_BRAKING;
//		}
//		else if(main_machine_state == STATE_MAIN_OL)
//		{
//			main_machine_state = STATE_MAIN_STOP_STANDBY;
//		}
//	#else
//		if(main_machine_state != STATE_MAIN_STOP_STANDBY)
//		{
//			main_machine_state = STATE_MAIN_COASTING ;
//			control_machine_state = STATE_CONTROL_COASTING;
//		}
//	#endif
//	}

	switch(main_machine_state)
	{
    case STATE_MAIN_STOP_STANDBY :
         motor_stop_state_reset();
//         hall_sensor_init();

         if((motor_ptr->motor_enable_cmd) == Motor_Enable)
         {
//        // Enable driver manager and verify active - need to enable even in PAC5210 to get ENHS pin to work
//        // pac5xxx_tile_register_write(ADDR_ENDRV, 1);
//			   # ifdef  Hall_MODE_ENABLE
//				   if(((motor_ptr->app_status&OVER_CURRENT_FLAG)) == 0)
//				   {
//          // Enable driver manager and verify active - need to enable even in PAC5210 to get ENHS pin to work
//             pac5xxx_tile_register_write(ADDR_ENDRV, 1);
//					   NVIC_EnableIRQ(TimerC_IRQn);
//					   main_machine_state = STATE_MAIN_OL_SWITCH_CL_WAIT;
//					   control_machine_state = STATE_CONTROL_OL_SWITCH_CL_WAIT;
//				   }
//			   # else
//				   if(((motor_ptr->app_status&OVER_CURRENT_FLAG)) == 0)
//		  		 {
//				   # ifdef  SIM_ENABLE
//					   sim_ptr->sim_process_state = STATE_SIM_INIT;
//			  		 main_machine_state = STATE_MAIN_SIM_DETECT;
//			  		 control_machine_state = STATE_CONTROL_SIM_DETECT;
//			  	 # else
//				     pac5xxx_tile_register_write(ADDR_ENDRV, 1);
//				  	 main_machine_state = STATE_MAIN_OL;
//				  	 control_machine_state = STATE_CONTROL_OL;
//			     # endif
//				   }
//			   # endif

				   if(((motor_ptr->app_status & OVER_CURRENT_FLAG)) == 0)
				   {
//           motor_ptr->motorspeed_cntr = 0;
             ESC_PWM_Cntr_Init();
//           feedback_Test2 = (u16)(motor_ptr->motorspeed);//(u16)MIN_SPEED;
//           feedback_Test3 = (u16)((motor_ptr->motorspeed)>>16);//(u16)(MIN_SPEED>>16);

						 motor_ptr->temp_pwm_duty = PWM_Control_Duty_StartUp;
					   main_machine_state = STATE_MAIN_OL_SWITCH_CL_WAIT;
					   control_machine_state = STATE_CONTROL_OL_SWITCH_CL_WAIT;

						 motor_ptr->app_status = 0;
//						 hall_ptr->state_hall_err = STATE_HALL_OK;
				   }
			   } /*if(motor_ptr->motor_enable_cmd)*/
			   break;

		case STATE_MAIN_OL :
//			if(motor_ptr->charge_done_flag == 1)	// Charge complete.
//			{
//				if (bldcm_align_go.align_and_go_state != STATE_STARTUP_DONE)
//				{
//					// call Iq_ref ramp
//					bldcm_motor_iq_ref_ramp(motor_ptr);
//					#ifndef PPD_START_UP_ENABLE
//						#ifdef SINE_WAVE_START_UP_ENABLE
//							sine_wave_start_up_process();
//						#else
//							square_wave_start_up_process();
//						#endif
//					#endif
//				}
//				else
//				{
//					control_machine_state = STATE_CONTROL_OL_SWITCH_CL_WAIT;
//					main_machine_state = STATE_MAIN_OL_SWITCH_CL_WAIT;
//				}
//			}
			break;

		case STATE_MAIN_OL_SWITCH_CL_WAIT :
			// calculate speed reference ,wait several step then call speed PI
			if(motor_ptr->call_speed_loop_delay_count >= DELAY_SWITCH_TO_SPEED_LOOP_COUNTS)
			{
				// this is for SIM
//				__disable_irq();
//				pac5xxx_tile_register_write(ADDR_ENDRV, 1);
//				__enable_irq();

				motor_ptr->call_speed_loop_delay_count = 0 ;

//      feedback_Test2 = (u16)motor_ptr->motorspeed;
//      feedback_Test3 = (u16)(motor_ptr->motorspeed>>16);

//      feedback_Test1 = 0;

//      if(hall_ptr->dt_commutate_m_average>0x9CF28E)//motor speed < 5rpm //motor_ptr->motorspeed > 0x217B6DB)
//      if(hall_ptr->dt_commutate_m_average>0xA108587) // <0.3rpm
        if(hall_ptr->dt_commutate_m_average>0xF53B049) // <0.2rpm
        {
          pwm_disable();
          control_machine_state = STATE_CONTROL_IDLE;
          main_machine_state = STATE_MAIN_FAULT;
          motor_ptr->app_status |= status_starup_fail;
//          SET_STDSCI_PACK_32_TX_OVERRUN(&(btx_ptr->pck_0xA4), &(btx_ptr->pck_0xA5), hall_ptr->dt_commutate_m_average);
//					feedback_Test1 = 0x5555;
        }
        else
        {
          if(motor_ptr->control_mode_select_number == 0)
          {
	//					motor_ptr->motor_close_loop_speed_temp = motor_ptr->motor_close_loop_speed;
	//					motor_ptr->app_speed_command = HertzToTicks(motor_ptr->motor_close_loop_speed_temp, TIMER_D_FREQ_F16) ;
	//					motor_ptr->app_speed_ref = motor_ptr->app_speed_command;
	//					motor_ptr->speed_pid.aw_prev = motor_ptr->Iq_ref;
	//					motor_ptr->speed_pid.I_prev = motor_ptr->Iq_ref;
	//					motor_ptr->speed_pid.PI_sat = motor_ptr->Iq_ref;

	//					control_machine_state = STATE_CONTROL_CL_SPEED;
	//					main_machine_state = STATE_MAIN_CL_SPEED;
            ESC_SPEED_PID_Reset();
				    control_machine_state = STATE_CONTROL_CL_SPEED;
					  main_machine_state = STATE_MAIN_CL_SPEED;
					}
					else if(motor_ptr->control_mode_select_number == 1)
					{
	//					control_machine_state = STATE_CONTROL_CL_CURRENT;
	//					main_machine_state = STATE_MAIN_CL_CURRENT;
					}
					else if(motor_ptr->control_mode_select_number == 2)
					{
						control_machine_state = STATE_CONTROL_CL_PWM_DUTY;
						main_machine_state = STATE_MAIN_CL_PWM_DUTY;
					} /*if(motor_ptr->control_mode_select_number == 0)*/
					// Running speed close loop
					motor_ptr->app_status &= ~status_open_loop;
					motor_ptr->app_status |= status_closed_loop;
				} /*if(hall_ptr->dt_commutate_m_average>0x4E7974)*/
      }
			// call Iq_ref ramp
      // bldc_motor_iq_ref_ramp(motor_ptr);
    break;

		case STATE_MAIN_CL_SPEED :
//			// call speed_ref ramp
//			bldc_motor_speed_ref_ramp(motor_ptr);
      ESC_SPEED_PID();

      if((motor_ptr->motor_enable_cmd) != Motor_Enable)
      {
        motor_ptr->pwm_control_duty_cycle = 0;
        control_machine_state = STATE_CONTROL_COASTING;
        main_machine_state = STATE_MAIN_COASTING;
      }
		break;
		case STATE_MAIN_CL_CURRENT :
    break;
		case STATE_MAIN_CL_PWM_DUTY :
//			if(motor_ptr->control_mode_select_number == 0)
//			{
//				if(main_machine_state != STATE_MAIN_CL_SPEED)
//				{
//					motor_ptr->Iq_pid.aw_prev = motor_ptr->temp_pwm_duty<<16;
//					motor_ptr->Iq_pid.I_prev = motor_ptr->temp_pwm_duty<<16;
//					motor_ptr->Iq_pid.PI_sat = motor_ptr->temp_pwm_duty<<16;

//					control_machine_state = STATE_CONTROL_CL_SPEED;
//					main_machine_state = STATE_MAIN_CL_SPEED;
//				}
//			}
//			else if(motor_ptr->control_mode_select_number == 1)
//			{
//				if(main_machine_state != STATE_MAIN_CL_CURRENT)
//				{
//					motor_ptr->Iq_pid.aw_prev = motor_ptr->temp_pwm_duty<<16;
//					motor_ptr->Iq_pid.I_prev = motor_ptr->temp_pwm_duty<<16;
//					motor_ptr->Iq_pid.PI_sat = motor_ptr->temp_pwm_duty<<16;

//					control_machine_state = STATE_CONTROL_CL_CURRENT;
//					main_machine_state = STATE_MAIN_CL_CURRENT;
//				}
//			}
//			else if(motor_ptr->control_mode_select_number == 2)
//			{
//				if(main_machine_state != STATE_MAIN_CL_PWM_DUTY)
//				{
//					control_machine_state = STATE_CONTROL_CL_PWM_DUTY;
//					main_machine_state = STATE_MAIN_CL_PWM_DUTY;
//				}
//			}
        if((motor_ptr->motor_enable_cmd) != Motor_Enable)
        {
          motor_ptr->pwm_control_duty_cycle = 0;
          control_machine_state = STATE_CONTROL_COASTING;
          main_machine_state = STATE_MAIN_COASTING;
        }
			break;

		case STATE_MAIN_SIM_DETECT :
//			break;

		case STATE_MAIN_STOP_BRAKING :
//			#ifdef 	MOTOR_STOP_BRAKING_ENABLE
//			if(motor_ptr->motor_enable_cmd)
//			{
//				pwm_disable();
//				if(sim_ptr->braking_restart_disable_driver_counts++ >= BRAKING_RESTART_WAIT_TIMES)
//				{
//					#ifdef  SIM_ENABLE

//						sim_ptr->sim_process_state = STATE_SIM_INIT;
//						main_machine_state = STATE_MAIN_SIM_DETECT;
//						control_machine_state = STATE_CONTROL_SIM_DETECT;

//						// Enable driver manager and verify active - need to enable even in PAC5210 to get ENHS pin to work
//						pac5xxx_tile_register_write(ADDR_ENDRV, 1);

//						sim_ptr->braking_restart_disable_driver_counts = 0;
//					#else
//						main_machine_state = STATE_MAIN_STOP_STANDBY;
//					#endif
//				}

//			}
//			else
//			{
//				sim_ptr->braking_restart_disable_driver_counts = 0;
//				if(sim_ptr->braking_detect_motor_stop_flag)
//				{
//					main_machine_state = STATE_MAIN_STOP_STANDBY;
//				}
//			}
//			#endif
//			break;

		case STATE_MAIN_COASTING:
//			if(motor_ptr->motor_enable_cmd)
//			{
//				if(motor_ptr->control_mode_select_number == 0)
//				{
//					control_machine_state = STATE_CONTROL_CL_SPEED;
//					main_machine_state = STATE_MAIN_CL_SPEED;
//				}
//				else if(motor_ptr->control_mode_select_number == 1)
//				{
//					control_machine_state = STATE_CONTROL_CL_CURRENT;
//					main_machine_state = STATE_MAIN_CL_CURRENT;
//				}
//				else if(motor_ptr->control_mode_select_number == 2)
//				{
//					control_machine_state = STATE_CONTROL_CL_PWM_DUTY;
//					main_machine_state = STATE_MAIN_CL_PWM_DUTY;
//				}
//			}
//			else
//			{
//				bldc_align_go.switch_speed_ticks = HertzToTicks(bldc_align_go.switch_speed_hz,TIMER_D_FREQ_F16);
//				if((motor_ptr->app_measured_speed >= bldc_align_go.switch_speed_ticks)||(motor_ptr->coasting_timeout_counts++ >= motor_ptr->coasting_timeout))
//				{
//					// Disable PWM output
//					pwm_disable();
//					motor_ptr->coasting_timeout_counts = 0;
//					main_machine_state = STATE_MAIN_STOP_STANDBY ;
//				}
//				else
//				{
//					if(motor_ptr->temp_pwm_duty > COASTING_DUTY_REDUCE_RATE)
//					{
//						motor_ptr->temp_pwm_duty -= COASTING_DUTY_REDUCE_RATE;
//					}
//				}
//        if(motor_ptr->temp_pwm_duty < 32)
        motor_ptr->pwm_control_duty_cycle = 0;
        if(hall_ptr->dt_commutate_m_average >0x29DA6)// 0x4E7974)// motor speed < 150rpm //motor_ptr->average_speed > 0x11DB6D
        {
//					ESC_PWM_Cntr_Init();
          pwm_disable();
          control_machine_state = STATE_CONTROL_IDLE;
          main_machine_state = STATE_MAIN_STOP_STANDBY;
				}
      break;
    case STATE_MAIN_FAULT:
      if((motor_ptr->motor_enable_cmd) == Motor_Disable)
      {
//        ESC_PWM_Cntr_Init();
        control_machine_state = STATE_CONTROL_IDLE;
        main_machine_state = STATE_MAIN_STOP_STANDBY;
			}
			else
      {
        control_machine_state = STATE_CONTROL_IDLE;
			}
			break;
			
		default :
			main_machine_state = STATE_MAIN_STOP_STANDBY ;
			break;
	}

  if(main_machine_state_pre != main_machine_state)
  {
    SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0x80), main_machine_state);
  }

	if(motor_ptr->temp_pwm_duty_pre != motor_ptr->temp_pwm_duty)
  {
    SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0x98), motor_ptr->temp_pwm_duty);
  }

  main_machine_state_pre = main_machine_state;
  motor_ptr->temp_pwm_duty_pre = motor_ptr->temp_pwm_duty;
}

