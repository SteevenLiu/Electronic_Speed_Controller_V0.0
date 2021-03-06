
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
#include "ESC_BLDCM_Hall.h"
//#include "hall.h"

# define Phs_Z   0
# define Phs_I   1
# define Phs_II  2
# define Phs_III 3
# define Phs_IV  4
# define Phs_V   5
# define Phs_VI  6
# define Phs_VII 7

// Copy "Hall to Mos Array" number that display on GUI here
//const uint8_t hall_to_mos_state[] = {0,6,4,5,2,1,3,7};
//const uint8_t next_mos_state[] = {0,2,3,4,5,6,1,7};
//const uint8_t prev_mos_state[] = {0,6,1,2,3,4,5,7};
//
   const u8 hall_to_mos_state[] = { Phs_Z,   \
                                    Phs_VI,  \
                                    Phs_IV,  \
                                    Phs_V,   \
                                    Phs_II,  \
                                    Phs_I,   \
                                    Phs_III, \
                                    Phs_VII  };

   const u8 next_mos_state[] =  { Phs_Z,   \
                                  Phs_II,  \
                                  Phs_III, \
                                  Phs_IV,  \
                                  Phs_V,   \
                                  Phs_VI,  \
                                  Phs_I,   \
                                  Phs_VII  };

   const u8 prev_mos_state[] =  { Phs_Z,   \
                                  Phs_VI,  \
                                  Phs_I,   \
                                  Phs_II,  \
                                  Phs_III, \
                                  Phs_IV,  \
                                  Phs_V,   \
                                  Phs_VII  };
//void pwm_disable(void);

//Hall_Sensor bldcm_hall_sensor_m1;

// Hall detect in CL
uint32_t debug_Array_1[8] = {9,9,9,9,9,9,9,9};

//=============================================================================
/// @brief  This function store Hall value,in order to display on GUI
/// @param  None
/// @return None
//=============================================================================
//#if defined(Hall_MODE_ENABLE)||defined(Hall_Detect_IN_BEMF_MODE)
//PAC5XXX_RAMFUNC void hall_detect_array_display_on_gui(void)
//{
//	Hall_Sensor* hall_ptr;
//	hall_ptr = &bldcm_hall_sensor_m1;

//	hall_ptr->hall_to_mos_state_detect =
//								10000000 * debug_Array_1[0] +
//								1000000 * debug_Array_1[1] +
//								100000 * debug_Array_1[2] +
//								10000 * debug_Array_1[3] +
//								1000 * debug_Array_1[4] +
//								100 * debug_Array_1[5] +
//								10 * debug_Array_1[6] +
//								1 * debug_Array_1[7];
//}
//#endif

//=============================================================================
/// @brief  This function study hall,and store
/// @param  None
/// @return None
//=============================================================================
//#if defined(Hall_MODE_ENABLE)||defined(Hall_Detect_IN_BEMF_MODE)
//PAC5XXX_RAMFUNC void hall_detect_in_bemf_mode(void)
//{
//	BLDC_Controller* motor_ptr;
//	motor_ptr = &bldc_m1;
//	Hall_Sensor* hall_ptr;
//	hall_ptr = &bldc_hall_sensor_m1;

//	hall_ptr->hall_value = HALL_VALUE_GPIO;

//	debug_Array_1[hall_ptr->hall_value] = motor_ptr->sl_current_state;
//	hall_detect_array_display_on_gui();
//}
//#endif

//=============================================================================
/// @brief  This function get hall value,then commutate
/// @param  None
/// @return None
//=============================================================================

   void ESC_Commutate(u8 phs)
   {
     switch(phs)
     {
       case Phs_I:
          Chopper_Phase_I();
          break;
       case Phs_II:
          Chopper_Phase_II();
          break;
       case Phs_III:
          Chopper_Phase_III();
          break;
       case Phs_IV:
          Chopper_Phase_IV();
          break;
       case Phs_V:
          Chopper_Phase_V();
          break;
       case Phs_VI:
          Chopper_Phase_VI();
          break;
       default:
         Chopper_Phase_ZRO(); 
     }
   }
	 
  void hall_sensor_init(void)
  {
    BLDCM_Controller* motor_ptr;
    motor_ptr = &bldcm_m1;
    Hall_Sensor* hall_ptr;
    hall_ptr = &bldcm_hall_sensor_m1;
    hall_ptr->hall_value = Get_Hall();
//		hall_ptr->state_hall_err = STATE_HALL_OK;
		
    if((hall_ptr->hall_value == 0)||(hall_ptr->hall_value == 7))
    {
      motor_ptr->app_status |= status_hall_error;
    }

    hall_ptr->sensored_current_state = hall_to_mos_state[hall_ptr->hall_value];
    hall_ptr->sensored_current_state_pre = hall_ptr->sensored_current_state;
		
//    motor_ptr->test_0 = hall_ptr->sensored_current_state_pre;
//    motor_ptr->test_1 = hall_ptr->sensored_current_state;
  }	

  void Get_Hall_2_UC(void) /*2018.10.19*/
  {
    BLDCM_Controller* motor_ptr;
    motor_ptr = &bldcm_m1;		
		
    Hall_Sensor* hall_ptr;
    hall_ptr = &bldcm_hall_sensor_m1;

    u32 lgth_phs;
    lgth_phs = (motor_ptr->average_speed) >> LS_MotorSpeed_Cntr;
		
//  hall_ptr->hall_value  = ((GPIO_ReadInputDataBit(Port_Hall_A, Pin_Hall_C))<<2);
//  hall_ptr->hall_value |= ((GPIO_ReadInputDataBit(Port_Hall_B, Pin_Hall_B))<<1);

    if(control_machine_state == STATE_CONTROL_IDLE)
    {
      hall_ptr->hall_value  = ((GPIO_ReadInputDataBit(Port_Hall_A, Pin_Hall_C))<<2);
      hall_ptr->hall_value |= ((GPIO_ReadInputDataBit(Port_Hall_B, Pin_Hall_B))<<1);
      hall_ptr->hall_value |= ((GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_A)));
		}
    else
    {
			switch (hall_ptr->sensored_current_state)
			{
				case Phs_I: //phase I
			 // Hall_A: always high
					hall_ptr->hall_value  = 4; // 1<<2;
			 // Hall_B: always low
					hall_ptr->hall_value |= 0; // 0<<1;
			 // Hall_C: commute, high -> low
//          hall_ptr->hall_value |= ((GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_A)));
					if(motor_ptr->average_speed > 0x53200) // <515rpm
					{
						hall_ptr->hall_value |= GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_A);
					}
					else if ((motor_ptr->motorspeed_cntr > lgth_phs) || \
									 (lgth_phs == motor_ptr->motorspeed_cntr))
					{
						hall_ptr->hall_value |= 0;
					}
					else
					{
						hall_ptr->hall_value |= 1;
					}
				break;
				case Phs_II: //phase II
			 // Hall_A: always high
					hall_ptr->hall_value  = 4; // 1<<2;
			 // Hall_B: commute, low -> high
					hall_ptr->hall_value |= ((GPIO_ReadInputDataBit(Port_Hall_B, Pin_Hall_B))<<1);
			 // Hall_C: always low
					hall_ptr->hall_value |= 0; // 0;
				break;
				case Phs_III: //phase III
			 // Hall_A: commute, high -> low
					hall_ptr->hall_value  = ((GPIO_ReadInputDataBit(Port_Hall_A, Pin_Hall_C))<<2);
			 // Hall_B: always high
					hall_ptr->hall_value |= 2; // 1<<1;
			 // Hall_C: always low
					hall_ptr->hall_value |= 0; // 0;
				break;
				case Phs_IV: //phase IV
			 // Hall_A: always low
					hall_ptr->hall_value  = 0; // 0<<2;
			 // Hall_B: always high
					hall_ptr->hall_value |= 2; // 1<<1;
			 // Hall_C: commute, low -> high
//          hall_ptr->hall_value |= ((GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_A)));
					if(motor_ptr->average_speed > 0x53200) // <515rpm
					{
						hall_ptr->hall_value |= GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_A);
					}
					else if ((motor_ptr->motorspeed_cntr > lgth_phs) || \
									 (lgth_phs == motor_ptr->motorspeed_cntr))
					{
						hall_ptr->hall_value |= 1;
					}
					else
					{
						hall_ptr->hall_value |= 0;
					}
				break;
				case Phs_V: //phase V
			 // Hall_A: always low
					hall_ptr->hall_value  = 0; // 0<<2;
			 // Hall_B: commute, high -> low
					hall_ptr->hall_value |= ((GPIO_ReadInputDataBit(Port_Hall_B, Pin_Hall_B))<<1);
			 // Hall_C: always high
					hall_ptr->hall_value |= 1;
				break;
				case Phs_VI: //phase VI
			 // Hall_A: commute, low -> high
					hall_ptr->hall_value  = ((GPIO_ReadInputDataBit(Port_Hall_A, Pin_Hall_C))<<2);
			 // Hall_B: always low
					hall_ptr->hall_value |= 0; // 0<<1;
			 // Hall_C: always high
					hall_ptr->hall_value |= 1;
				break;
				default:
				break;		
			} /*switch (hall_ptr->sensored_current_state)*/
    } /*if(control_machine_state == STATE_CONTROL_IDLE)*/
	}

  void ESC_PWM_Counter(void)
  {
    BLDCM_Controller* motor_ptr;
    motor_ptr = &bldcm_m1;

    Hall_Sensor* hall_ptr;
    hall_ptr = &bldcm_hall_sensor_m1;

    if(hall_ptr->sensored_current_state_pre != hall_ptr->sensored_current_state)
    {
//    Do calculation for 8 sample moving average filter used for speed PI			
//      if((hall_ptr->sensored_current_state != Phs_II) || \
//				 (hall_ptr->sensored_current_state != Phs_V))
//			{
//				motor_ptr->motorspeed = motor_ptr->motorspeed_cntr << LS_MotorSpeed_Cntr ;
//			}
//      else
//      {
//				motor_ptr->motorspeed = motor_ptr->average_speed;
//			}

      motor_ptr->motorspeed = motor_ptr->motorspeed_cntr << LS_MotorSpeed_Cntr ;			
			motor_ptr->motorspeed_cntr = 0;
			motor_ptr->motorspeed_sum -= motor_ptr->motorspeed_buffer[motor_ptr->speed_sample_index];
			motor_ptr->motorspeed_buffer[motor_ptr->speed_sample_index] = motor_ptr->motorspeed;
			motor_ptr->motorspeed_sum += motor_ptr->motorspeed;
			motor_ptr->average_speed = motor_ptr->motorspeed_sum >> RS_Average_Speed;
			motor_ptr->app_measured_speed = motor_ptr->average_speed;

//    If we max out array index reset it to 0
			if (++(motor_ptr->speed_sample_index) >= NUM_SPEED_SAMPLES)
			motor_ptr->speed_sample_index = 0;
    }
    else
    {
      if(motor_ptr->motorspeed_cntr < MIN_SPEED_CNTR)
      {
        motor_ptr->motorspeed_cntr ++;
      }
			else
      {;}
    }
	}		
	
  void ESC_PWM_Counter_2_UC(void)
  {
    BLDCM_Controller* motor_ptr;
    motor_ptr = &bldcm_m1;
    Hall_Sensor* hall_ptr;
    hall_ptr = &bldcm_hall_sensor_m1;
		
 // validate PWMs counts and calculate average speed
    if(hall_ptr->sensored_current_state_pre != hall_ptr->sensored_current_state)
		{
      switch(hall_ptr->sensored_current_state)
      {
        case Phs_I:
       // validate
      	  if(motor_ptr->motorspeed_cntr_commute_Phs_V == 1)
          {
            motor_ptr->motorspeed = motor_ptr->motorspeed_cntr_Phs_V \
						<< LS_MotorSpeed_Cntr;
					}
          else
          {
            motor_ptr->motorspeed = motor_ptr->average_speed;
          }

       // initialize
          motor_ptr->motorspeed_cntr_commute_Phs_V = 0;
          motor_ptr->motorspeed_cntr_Phs_V = 0;
        break;
        case Phs_II:
       // validate
      	  if(motor_ptr->motorspeed_cntr_commute_Phs_VI == 1)
          {
            motor_ptr->motorspeed = motor_ptr->motorspeed_cntr_Phs_VI \
						<< LS_MotorSpeed_Cntr;
					}
          else
          {
            motor_ptr->motorspeed = motor_ptr->average_speed;
          }

       // initialize
          motor_ptr->motorspeed_cntr_commute_Phs_VI = 0;
          motor_ptr->motorspeed_cntr_Phs_VI = 0;
        break;
        case Phs_III:
       // validate
      	  if(motor_ptr->motorspeed_cntr_commute_Phs_I == 1)
          {
            motor_ptr->motorspeed = motor_ptr->motorspeed_cntr_Phs_I \
						<< LS_MotorSpeed_Cntr;
					}
          else
          {
            motor_ptr->motorspeed = motor_ptr->average_speed;
          }

       // initialize
//          motor_ptr->motorspeed_flag_commute_1st_Phs_I = 0;
          motor_ptr->motorspeed_cntr_commute_Phs_I = 0;
          motor_ptr->motorspeed_cntr_Phs_I = 0;
        break;
        case Phs_IV:
       // validate
      	  if(motor_ptr->motorspeed_cntr_commute_Phs_II == 1)
          {
            motor_ptr->motorspeed = motor_ptr->motorspeed_cntr_Phs_II \
						<< LS_MotorSpeed_Cntr;
					}
          else
          {
            motor_ptr->motorspeed = motor_ptr->average_speed;
          }

       // initialize
//          motor_ptr->motorspeed_flag_commute_1st_Phs_II = 0;
          motor_ptr->motorspeed_cntr_commute_Phs_II = 0;
          motor_ptr->motorspeed_cntr_Phs_II = 0;
        break;
        case Phs_V:
       // validate
      	  if(motor_ptr->motorspeed_cntr_commute_Phs_III == 1)
          {
            motor_ptr->motorspeed = motor_ptr->motorspeed_cntr_Phs_III \
						<< LS_MotorSpeed_Cntr;
					}
          else
          {
            motor_ptr->motorspeed = motor_ptr->average_speed;
          }

       // initialize
//          motor_ptr->motorspeed_flag_commute_1st_Phs_III = 0;
          motor_ptr->motorspeed_cntr_commute_Phs_III = 0;
          motor_ptr->motorspeed_cntr_Phs_III = 0;
        break;
        case Phs_VI:
       // validate
      	  if(motor_ptr->motorspeed_cntr_commute_Phs_IV == 1)
          {
            motor_ptr->motorspeed = motor_ptr->motorspeed_cntr_Phs_IV \
						<< LS_MotorSpeed_Cntr;
					}
          else
          {
            motor_ptr->motorspeed = motor_ptr->average_speed;
          }

       // initialize
//          motor_ptr->motorspeed_flag_commute_1st_Phs_IV = 0;
          motor_ptr->motorspeed_cntr_commute_Phs_IV = 0;
          motor_ptr->motorspeed_cntr_Phs_IV = 0;
        break;
				default:
        break;
      } /*switch(hall_ptr->sensored_current_state)*/

   // calculate
			motor_ptr->motorspeed_sum -= motor_ptr->motorspeed_buffer[motor_ptr->speed_sample_index];
			motor_ptr->motorspeed_buffer[motor_ptr->speed_sample_index] = motor_ptr->motorspeed;
			motor_ptr->motorspeed_sum += motor_ptr->motorspeed;
			motor_ptr->average_speed = motor_ptr->motorspeed_sum >> RS_Average_Speed;
			motor_ptr->app_measured_speed = motor_ptr->average_speed;

//    If we max out array index reset it to 0
			if (++(motor_ptr->speed_sample_index) >= NUM_SPEED_SAMPLES)
			motor_ptr->speed_sample_index = 0;
		} /*if(hall_ptr->sensored_current_state_pre != ...*/

 // refresh hall value
    motor_ptr->motorspeed_hall_A_current  = GPIO_ReadInputDataBit(Port_Hall_A, Pin_Hall_C);
    motor_ptr->motorspeed_hall_B_current  = GPIO_ReadInputDataBit(Port_Hall_B, Pin_Hall_B);
    motor_ptr->motorspeed_hall_C_current  = GPIO_ReadInputDataBit(Port_Hall_C, Pin_Hall_A);

 // counting PWMs in Phs_I
    if((hall_ptr->sensored_current_state == Phs_I) || \
       (hall_ptr->sensored_current_state == Phs_II))
    {
   // counting commutes and capture the 1st commute
      if(motor_ptr->motorspeed_hall_C_current != \
				 motor_ptr->motorspeed_hall_C_pre)
      {
        motor_ptr->motorspeed_cntr_commute_Phs_I ++;
      } /*if(motor_ptr->motorspeed_hall_A_current != \ ...*/

   // counting PWMs before the 1st commute occurs
      if((motor_ptr->motorspeed_cntr_commute_Phs_I == 0) &&  \
         (motor_ptr->motorspeed_cntr_Phs_I < MIN_SPEED_CNTR))
      {
        motor_ptr->motorspeed_cntr_Phs_I ++;
      }
      else
      {;} /*if(motor_ptr->motorspeed_flag_commute_1st_Phs_I != 1) ... */
    } /*if((hall_ptr->sensored_current_state == Phs_I) || \*/

 // counting PWMs in Phs_II
    if((hall_ptr->sensored_current_state == Phs_II) || \
       (hall_ptr->sensored_current_state == Phs_III))
    {
   // counting commutes and capture the 1st commute
      if(motor_ptr->motorspeed_hall_B_current != \
				 motor_ptr->motorspeed_hall_B_pre)
      {
        motor_ptr->motorspeed_cntr_commute_Phs_II ++;
      } /*if(motor_ptr->motorspeed_hall_B_current != \ ...*/

   // counting PWMs before the 1st commute occurs
      if((motor_ptr->motorspeed_cntr_commute_Phs_II == 0) && \
         (motor_ptr->motorspeed_cntr_Phs_II < MIN_SPEED_CNTR))
      {
        motor_ptr->motorspeed_cntr_Phs_II ++;
      }
      else
      {;} /*if(motor_ptr->motorspeed_flag_commute_1st_Phs_II != 1) ... */
    } /*if((hall_ptr->sensored_current_state == Phs_II) || \ ...*/

 // counting PWMs in Phs_III
    if((hall_ptr->sensored_current_state == Phs_III) || \
       (hall_ptr->sensored_current_state == Phs_IV))
    {
   // counting commutes and capture the 1st commute
      if(motor_ptr->motorspeed_hall_A_current != \
				 motor_ptr->motorspeed_hall_A_pre)
      {
        motor_ptr->motorspeed_cntr_commute_Phs_III ++;
      } /*if(motor_ptr->motorspeed_hall_A_current != \ ...*/

   // counting PWMs before the 1st commute occurs
      if((motor_ptr->motorspeed_cntr_commute_Phs_III == 0) &&     \
         (motor_ptr->motorspeed_cntr_Phs_III < MIN_SPEED_CNTR))
      {
        motor_ptr->motorspeed_cntr_Phs_III ++;
      }
      else
      {;} /*if(motor_ptr->motorspeed_flag_commute_1st_Phs_III != 1) ... */
    } /*if((hall_ptr->sensored_current_state == Phs_III) || \ ...*/

 // counting PWMs in Phs_IV
    if((hall_ptr->sensored_current_state == Phs_IV) || \
       (hall_ptr->sensored_current_state == Phs_V))
    {
   // counting commutes and capture the 1st commute
      if(motor_ptr->motorspeed_hall_C_current != \
				 motor_ptr->motorspeed_hall_C_pre)
      {
        motor_ptr->motorspeed_cntr_commute_Phs_IV ++;
      } /*if(motor_ptr->motorspeed_hall_C_current != \ ...*/

   // counting PWMs before the 1st commute occurs
      if((motor_ptr->motorspeed_cntr_commute_Phs_IV == 0) &&     \
         (motor_ptr->motorspeed_cntr_Phs_IV < MIN_SPEED_CNTR))
      {
        motor_ptr->motorspeed_cntr_Phs_IV ++;
      }
      else
      {;} /*if(motor_ptr->motorspeed_flag_commute_1st_Phs_IV != 1) ... */
    } /*if((hall_ptr->sensored_current_state == Phs_IV) || \ ...*/

 // counting PWMs in Phs_V
    if((hall_ptr->sensored_current_state == Phs_V) || \
       (hall_ptr->sensored_current_state == Phs_VI))
    {
   // counting commutes and capture the 1st commute
      if(motor_ptr->motorspeed_hall_B_current != \
				 motor_ptr->motorspeed_hall_B_pre)
      {
        motor_ptr->motorspeed_cntr_commute_Phs_V ++;
      } /*if(motor_ptr->motorspeed_hall_B_current != \ ...*/

   // counting PWMs before the 1st commute occurs
      if((motor_ptr->motorspeed_cntr_commute_Phs_V == 0) && \
         (motor_ptr->motorspeed_cntr_Phs_V < MIN_SPEED_CNTR))
      {
        motor_ptr->motorspeed_cntr_Phs_V ++;
      }
      else
      {;} /*if(motor_ptr->motorspeed_flag_commute_1st_Phs_V != 1) ... */
    } /*if((hall_ptr->sensored_current_state == Phs_V) || \ ...*/		

 // counting PWMs in Phs_VI
    if((hall_ptr->sensored_current_state == Phs_VI) || \
       (hall_ptr->sensored_current_state == Phs_I))
    {
   // counting commutes and capture the 1st commute
      if(motor_ptr->motorspeed_hall_A_current != \
				 motor_ptr->motorspeed_hall_A_pre)
      {
        motor_ptr->motorspeed_cntr_commute_Phs_VI ++;
      } /*if(motor_ptr->motorspeed_hall_A_current != \ ...*/

   // counting PWMs before the 1st commute occurs
      if((motor_ptr->motorspeed_cntr_commute_Phs_VI == 0) &&  \
         (motor_ptr->motorspeed_cntr_Phs_VI < MIN_SPEED_CNTR))
      {
        motor_ptr->motorspeed_cntr_Phs_VI ++;
      }
      else
      {;} /*if(motor_ptr->motorspeed_flag_commute_1st_Phs_VI != 1) ... */
    } /*if((hall_ptr->sensored_current_state == Phs_V) || \ ...*/

		motor_ptr->motorspeed_hall_A_pre = motor_ptr->motorspeed_hall_A_current;
    motor_ptr->motorspeed_hall_B_pre = motor_ptr->motorspeed_hall_B_current;
    motor_ptr->motorspeed_hall_C_pre = motor_ptr->motorspeed_hall_C_current;
	}		

#if 1 //defined(Hall_MODE_ENABLE)||defined(Hall_BEMF_SWITCH_MODE_ENABLE)
/*PAC5XXX_RAMFUNC*/ void get_hall_value_and_change_mos_state(void)
{
  BLDCM_Controller* motor_ptr;
  motor_ptr = &bldcm_m1;
  Hall_Sensor* hall_ptr;
  hall_ptr = &bldcm_hall_sensor_m1;

//  hall_ptr->hall_value = Get_Hall();
// hall_ptr->hall_value = HALL_VALUE_GPIO;

  if((hall_ptr->hall_value == 0)||(hall_ptr->hall_value == 7))
  {
    pwm_disable();
    main_machine_state = STATE_MAIN_FAULT;
    control_machine_state = STATE_CONTROL_IDLE;
    motor_ptr->app_status |= status_hall_error;
  }

//	hall_ptr->sensored_current_state = hall_to_mos_state[hall_ptr->hall_value];

//  if(!motor_ptr->reverse_tune_flag)
//  {
//    hall_ptr->sensored_current_state = hall_to_mos_state[hall_ptr->hall_value];
//  }
//  else
//  {
//    hall_ptr->sensored_current_state = hall_to_mos_state[7-hall_ptr->hall_value];
//  }

//	if(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT)
//	{
//		commutate(hall_ptr->sensored_current_state);
//	}

//  switch (hall_ptr->state_hall_err)
//  {
//	  case STATE_HALL_OK:
//			if(/*(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT) || */                        \
//				 (hall_ptr->sensored_current_state_pre == hall_ptr->sensored_current_state) ||             \
//				 (next_mos_state[hall_ptr->sensored_current_state_pre] == hall_ptr->sensored_current_state))
//			{

//				if(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT)
//				{
//					motor_ptr->call_speed_loop_delay_count++;
//				}

//				ESC_Commutate(hall_ptr->sensored_current_state);
//			}
//			else
//			{
//				hall_ptr->sensored_current_state = hall_ptr->sensored_current_state_pre;

//			  if(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT)
//				{
//					motor_ptr->call_speed_loop_delay_count++;
//				}

//				ESC_Commutate(hall_ptr->sensored_current_state);
//				
//				hall_ptr->state_hall_err = STATE_HALL_ERR_I;
//			}			
//    break;
//		case STATE_HALL_ERR_I:
//			if(/*(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT) || */                        \
//				 (hall_ptr->sensored_current_state_pre == hall_ptr->sensored_current_state) ||             \
//				 (next_mos_state[hall_ptr->sensored_current_state_pre] == hall_ptr->sensored_current_state))
//			{

//				if(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT)
//				{
//					motor_ptr->call_speed_loop_delay_count++;
//				}

//				ESC_Commutate(hall_ptr->sensored_current_state);
//				
//				hall_ptr->state_hall_err = STATE_HALL_OK;
//			}
//			else
//			{
//				pwm_disable();
//				main_machine_state = STATE_MAIN_FAULT;
//				control_machine_state = STATE_CONTROL_IDLE;
//				motor_ptr->app_status |= status_hall_error;
//				
//				feedback_Test0 = motor_ptr->temp_pwm_duty;
//				feedback_Test1 = hall_ptr->sensored_current_state_pre;		
//				feedback_Test2 = next_mos_state[hall_ptr->sensored_current_state_pre];
//				feedback_Test3 = hall_ptr->sensored_current_state;
//			}
//    break;
//		case STATE_HALL_ERR_II:
//    break;
//		default:
//    break;
//	}		
	
  if(/*(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT) || */                        \
		 (hall_ptr->sensored_current_state_pre == hall_ptr->sensored_current_state) ||             \
     (next_mos_state[hall_ptr->sensored_current_state_pre] == hall_ptr->sensored_current_state))
  {

    if(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT)
    {
      motor_ptr->call_speed_loop_delay_count++;
    }

    ESC_Commutate(hall_ptr->sensored_current_state);

//  ESC_PWM_Counter();
		
//    if(hall_ptr->sensored_current_state_pre != hall_ptr->sensored_current_state)
//    {			
////    Do calculation for 8 sample moving average filter used for speed PI
//      motor_ptr->motorspeed = motor_ptr->motorspeed_cntr << LS_MotorSpeed_Cntr ;
//      motor_ptr->motorspeed_cntr = 0;
//      motor_ptr->motorspeed_sum -= motor_ptr->motorspeed_buffer[motor_ptr->speed_sample_index];
//      motor_ptr->motorspeed_buffer[motor_ptr->speed_sample_index] = motor_ptr->motorspeed;
//      motor_ptr->motorspeed_sum += motor_ptr->motorspeed;
//      motor_ptr->average_speed = motor_ptr->motorspeed_sum >> RS_Average_Speed;
//      motor_ptr->app_measured_speed = motor_ptr->average_speed;

////    If we max out array index reset it to 0
//      if (++(motor_ptr->speed_sample_index) >= NUM_SPEED_SAMPLES)
//      motor_ptr->speed_sample_index = 0;
//    }
//    else
//    {
//      motor_ptr->motorspeed_cntr++;
//    } /*if(hall_ptr->sensored_current_state_pre != hall_ptr->sensored_current_state)*/	
  }
  else
  {
    pwm_disable();
    main_machine_state = STATE_MAIN_FAULT;
    control_machine_state = STATE_CONTROL_IDLE;
    motor_ptr->app_status |= status_hall_error;
		
//		feedback_Test0 = motor_ptr->temp_pwm_duty;
//		feedback_Test1 = hall_ptr->sensored_current_state_pre;
//		feedback_Test2 = next_mos_state[hall_ptr->sensored_current_state_pre];
//		feedback_Test3 = hall_ptr->sensored_current_state;
  }/*if((hall_ptr->sensored_current_state_pre == hall_ptr->sensored_current_state) || ...*/
	
//  hall_ptr->sensored_current_state_pre = hall_ptr->sensored_current_state;
}
#endif

  void ESC_Commutator_on_Hall_Observer(void)
  {
    Hall_Observer* hall_ptr;
    hall_ptr = &bldcm_hall_observer_m1;

    BLDCM_Controller* motor_ptr;
    motor_ptr = &bldcm_m1;

//    if BOOLE_HALL_STATE_ILLEGAL
//    {
//      pwm_disable();
//      main_machine_state = STATE_MAIN_FAULT;
//      control_machine_state = STATE_CONTROL_IDLE;
//      motor_ptr->app_status |= status_hall_error;
//    }		
	
    if BOOLE_HALL_STATE_LEGAL
    {
      if(control_machine_state == STATE_CONTROL_OL_SWITCH_CL_WAIT)
      {
        motor_ptr->call_speed_loop_delay_count++;
      }

      switch(hall_ptr->sensored_current_state)
      {
        case Phs_I: Chopper_Phase_I();
        break;
        case Phs_II: Chopper_Phase_II();
        break;
        case Phs_III: Chopper_Phase_III();
        break;
        case Phs_IV: Chopper_Phase_IV();
        break;
        case Phs_V: Chopper_Phase_V();
        break;
        case Phs_VI: Chopper_Phase_VI();
        break;
        default: Chopper_Phase_ZRO();
      }
    }
    else
    {
      pwm_disable();
      main_machine_state = STATE_MAIN_FAULT;
//    control_machine_state = STATE_CONTROL_IDLE;
      motor_ptr->app_status |= status_hall_error;
		
//      feedback_Test0 = motor_ptr->temp_pwm_duty;
//      feedback_Test1 = hall_ptr->sensored_current_state_pre;
//      feedback_Test2 = next_mos_state[hall_ptr->sensored_current_state_pre];
//      feedback_Test3 = hall_ptr->sensored_current_state;

//     feedback_Test_0 = hall_ptr->sensored_current_state_pre;
//     feedback_Test_1 = next_mos_state[hall_ptr->sensored_current_state_pre];
//     feedback_Test_2 = hall_ptr->sensored_current_state;
//     feedback_Test_3 = hall_ptr->num_pwm_60d_m;
//     feedback_Test_4 = hall_ptr->num_pwm_60d_p;
//     feedback_Test_0_Long = hall_ptr->dt_commutate_p;
    } /*if(BOOLE_HALL_STATE_LEGAL)*/
  }
//
   u8 Get_Hall_Init(void)
   {
		 u8 hall_value = 0;

     if(BOOLE_HALL_U_SET) hall_value |= BIT_HALL_U;
		 else hall_value &= ~BIT_HALL_U;

     if(BOOLE_HALL_V_SET) hall_value |= BIT_HALL_V;
		 else hall_value &= ~BIT_HALL_V;

     if(BOOLE_HALL_W_SET) hall_value |= BIT_HALL_W;
		 else hall_value &= ~BIT_HALL_W;
	 
     return hall_value;
   }
//
   void ESC_Observer_Hall(void)
   {
     Hall_Observer* hall_ptr;
		 hall_ptr = &bldcm_hall_observer_m1;

     BLDCM_Controller* motor_ptr;
     motor_ptr = &bldcm_m1;

     STDSCI_BLOCK_TX* btx_ptr;
     btx_ptr = &block_tx;

//	   BLDCM_Controller* motor_ptr;
//	   motor_ptr = &bldcm_m1;
//
//     determine current hall value - bldcm_hall_observer_m1.hall_value
//     and hall state - bldcm_hall_observer_m1.sensored_current_state
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//
//   vary hall observer state
     switch (hall_ptr->observer_state)
     {
       case STATE_HALL_OBSERVER_LS:
         if(hall_ptr->dt_commutate_m_average <  0xA769) // >1200rpm // 0xC8E5) // >1000rpm
         {
					 hall_ptr->observer_state = STATE_HALL_OBSERVER_HS;
           SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0x82), hall_ptr->observer_state);
         }
       break;
			 case STATE_HALL_OBSERVER_HS:
         if(hall_ptr->dt_commutate_m_average > 0xC8E5) // <1000rpm // 0xFB1E) // <800rpm
         {
           hall_ptr->observer_state = STATE_HALL_OBSERVER_LS;
           SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0x82), hall_ptr->observer_state);
         }
       break;
       default:;
     }
//
     hall_ptr->t_base_temp = TIM_GetCounter(TIM2);

     if (hall_ptr->observer_state == STATE_HALL_OBSERVER_HS)
     {
       switch(hall_ptr->sensored_current_state)
       {
         case Phs_I:
           hall_ptr->hall_value &= BOOLE_HALL_W_RESET? ~BIT_HALL_W:0xFF;
         break;
         case Phs_II:
           hall_ptr->hall_value |= BOOLE_HALL_V_SET? BIT_HALL_V:0x00;
         break;
         case Phs_III:
           hall_ptr->hall_value &= BOOLE_HALL_U_RESET? ~BIT_HALL_U:0xFF;
         break;
         case Phs_IV:
           hall_ptr->hall_value |= BOOLE_HALL_W_SET? BIT_HALL_W:0x00;
         break;
         case Phs_V:
           hall_ptr->hall_value &= BOOLE_HALL_V_RESET? ~BIT_HALL_V:0xFF;
         break;
         case Phs_VI:
           hall_ptr->hall_value |= BOOLE_HALL_U_SET? BIT_HALL_U:0x00;
         break;
         default:
//             hall_ptr->hall_value &= BOOLE_HALL_W_RESET? ~BIT_HALL_W:0xFF;
//             hall_ptr->hall_value |= BOOLE_HALL_V_SET? BIT_HALL_V:0x00;
//             hall_ptr->hall_value &= BOOLE_HALL_U_RESET? ~BIT_HALL_U:0xFF;
//             hall_ptr->hall_value |= BOOLE_HALL_W_SET? BIT_HALL_W:0x00;
//             hall_ptr->hall_value &= BOOLE_HALL_V_RESET? ~BIT_HALL_V:0xFF;
//             hall_ptr->hall_value |= BOOLE_HALL_U_SET? BIT_HALL_U:0x00;
         break;
       } /*switch(hall_ptr->sensored_current_state)*/
     } /*if (hall_ptr->observer_state == STATE_HALL_OBSERVER_HS)*/
     else
     {
       hall_ptr->hall_value &= BOOLE_HALL_W_RESET? ~BIT_HALL_W:0xFF;
       hall_ptr->hall_value |= BOOLE_HALL_V_SET? BIT_HALL_V:0x00;
       hall_ptr->hall_value &= BOOLE_HALL_U_RESET? ~BIT_HALL_U:0xFF;
       hall_ptr->hall_value |= BOOLE_HALL_W_SET? BIT_HALL_W:0x00;
       hall_ptr->hall_value &= BOOLE_HALL_V_RESET? ~BIT_HALL_V:0xFF;
       hall_ptr->hall_value |= BOOLE_HALL_U_SET? BIT_HALL_U:0x00;      
     }
//
//   measure pwm number in 60 degree
     if BOOLE_HALL_STATE_CHANGE
     {
       hall_ptr->num_pwm_60d_m = hall_ptr->cntr_pwm_60d;
       hall_ptr->cntr_pwm_60d = 1;
//       SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB1), hall_ptr->num_pwm_60d_m);
//       SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB2), hall_ptr->num_pwm_60d_p);
//       SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB1), hall_ptr->min_d_num_pwm_60d);
//       SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB2), hall_ptr->max_d_num_pwm_60d);
     }
		 else if(main_machine_state != STATE_MAIN_STOP_STANDBY) hall_ptr->cntr_pwm_60d++;
		 else hall_ptr->cntr_pwm_60d = 0;

     hall_ptr->dt_base_temp = (hall_ptr->t_base_temp > hall_ptr->t_base_commutate)? \
                              (hall_ptr->t_base_temp - hall_ptr->t_base_commutate): \
                              (hall_ptr->t_base_temp + ARR_HALL_CAP - hall_ptr->t_base_commutate);

     if BOOLE_HALL_STATE_CHANGE
     {
       hall_ptr->t_base_commutate = hall_ptr->t_base_temp;
       hall_ptr->dt_base_commutate = hall_ptr->dt_base_temp;
     }
//
//   hall state varification
     if (hall_ptr->observer_state == STATE_HALL_OBSERVER_HS)
     {
       if BOOLE_HALL_STATE_CHANGE
       {
         hall_ptr->d_num_pwm_60d = (hall_ptr->num_pwm_60d_m > hall_ptr->num_pwm_60d_p)? \
                                   (hall_ptr->num_pwm_60d_m - hall_ptr->num_pwm_60d_p): \
                                   (hall_ptr->num_pwm_60d_p - hall_ptr->num_pwm_60d_m);
				 
				 if((hall_ptr->d_num_pwm_60d > 1) &&                        \
            (hall_ptr->d_num_pwm_60d > (hall_ptr->num_pwm_60d_p>>2)))
//         if(hall_ptr->d_num_pwm_60d > 1)
         {
           BOOLE_HALL_STATE_LEGAL = False;
           motor_ptr->app_status |= status_hall_error;
         }
       }
		 }
     else
     {
       BOOLE_HALL_STATE_LEGAL = BOOLE_HALL_LEGAL? True:False;
       motor_ptr->app_status |= BOOLE_HALL_STATE_LEGAL? 0:status_hall_error;
     } /*if (hall_ptr->observer_state == STATE_HALL_OBSERVER_HS)*/
     
     if((!BOOLE_HALL_STATE_LEGAL)&& BOOLE_HALL_STATE_LEGAL_PRE)
     {
       feedback_Test_0 = hall_ptr->sensored_current_state_pre;
       feedback_Test_1 = next_mos_state[hall_ptr->sensored_current_state_pre];
       feedback_Test_2 = hall_ptr->sensored_current_state;
       feedback_Test_3 = hall_ptr->num_pwm_60d_m;
       feedback_Test_4 = hall_ptr->num_pwm_60d_p;
       feedback_Test_0_Long = hall_ptr->dt_commutate_p;
     }
//
////
//     if (hall_ptr->observer_state == STATE_HALL_OBSERVER_HS)
//     {
//       hall_ptr->d_num_pwm_60d = hall_ptr->num_pwm_60d_m - hall_ptr->num_pwm_60d_p;

//			 hall_ptr->min_d_num_pwm_60d = (hall_ptr->d_num_pwm_60d < hall_ptr->min_d_num_pwm_60d)? \
//       hall_ptr->d_num_pwm_60d : hall_ptr->min_d_num_pwm_60d;

//       hall_ptr->max_d_num_pwm_60d = (hall_ptr->d_num_pwm_60d > hall_ptr->max_d_num_pwm_60d)? \
//       hall_ptr->d_num_pwm_60d : hall_ptr->max_d_num_pwm_60d;
//			 
//       if((hall_ptr->num_pwm_60d_m < (hall_ptr->num_pwm_60d_p-2)) || \
//          ((hall_ptr->num_pwm_60d_p+2)< hall_ptr->num_pwm_60d_m))
//       {
//         hall_ptr->cntr_over_d_num_60d++;
//			 }
//     }
//		 else if (hall_ptr->observer_state == STATE_HALL_OBSERVER_LS)
//     {
//			 if (hall_ptr->observer_state_pre == STATE_HALL_OBSERVER_HS)
//       {
////         SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB1), hall_ptr->min_d_num_pwm_60d);
////         SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB2), hall_ptr->max_d_num_pwm_60d);
////         SET_STDSCI_PACK_32_TX_OVERRUN(&(btx_ptr->pck_0xA4), &(btx_ptr->pck_0xA5), hall_ptr->cntr_over_d_num_60d);         
//       }

//       hall_ptr->max_d_num_pwm_60d = 0;
//       hall_ptr->min_d_num_pwm_60d = 0;
//			 hall_ptr->cntr_over_d_num_60d = 0;
//     } /*if (hall_ptr->observer_state == STATE_HALL_OBSERVER_HS)*/
////
//     hall_ptr->observer_state_pre = hall_ptr->observer_state;
////

		 REFRESH_PREVIOUS_HALL_STATE_LEGAL;
     REFRESH_PREVIOUS_HALL_STATE;
     REFRESH_CURRENT_HALL_STATE;
//
//   a hall signal jumping edge has been detected and a DMA
//   event occours
//   .........................................................
     if (BOOLE_DMA_RENEWED)
     {
//
//     renew t_commutate_m and t_commutate_m_I/II/.../VI according
//     to newly captured value.
//     "m": measured
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       switch(hall_ptr->sensored_current_state)
       {
         case Phs_I:
           hall_ptr->t_commutate_m = hall_ptr->t_commutate_m_Hall_U;
           hall_ptr->t_commutate_m_I = hall_ptr->t_commutate_m;
         break;
         case Phs_II:
           hall_ptr->t_commutate_m = hall_ptr->t_commutate_m_Hall_W;
           hall_ptr->t_commutate_m_II = hall_ptr->t_commutate_m;
         break;
         case Phs_III:
           hall_ptr->t_commutate_m = hall_ptr->t_commutate_m_Hall_V;
           hall_ptr->t_commutate_m_III = hall_ptr->t_commutate_m;
         break;
         case Phs_IV:
           hall_ptr->t_commutate_m = hall_ptr->t_commutate_m_Hall_U;
           hall_ptr->t_commutate_m_IV = hall_ptr->t_commutate_m;
         break;
         case Phs_V:
           hall_ptr->t_commutate_m = hall_ptr->t_commutate_m_Hall_W;
           hall_ptr->t_commutate_m_V = hall_ptr->t_commutate_m;
         break;
         case Phs_VI:
           hall_ptr->t_commutate_m = hall_ptr->t_commutate_m_Hall_V;
           hall_ptr->t_commutate_m_VI = hall_ptr->t_commutate_m;
         break;
         default:
         break;
       } /*switch(hall_ptr->sensored_current_state)*/			 
//
//     calculate dt_commutate_m
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       hall_ptr->dt_commutate_m = (hall_ptr->t_commutate_m > hall_ptr->t_commutate_m_pre)? \
                                  (hall_ptr->t_commutate_m - hall_ptr->t_commutate_m_pre): \
                                  (hall_ptr->t_commutate_m + ARR_HALL_CAP - hall_ptr->t_commutate_m_pre);

       hall_ptr->t_commutate_m_pre = hall_ptr->t_commutate_m;

//
//     filter period - dt_commutate_m
//     output - bldcm_hall_observer_m1.dt_commutate_m_average
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       hall_ptr->dt_commutate_m_sum -= hall_ptr->dt_commutate_m_buffer[hall_ptr->dt_commutate_m_sample_index];
			 hall_ptr->dt_commutate_m_buffer[hall_ptr->dt_commutate_m_sample_index] = hall_ptr->dt_commutate_m;
			 hall_ptr->dt_commutate_m_sum += hall_ptr->dt_commutate_m;
			 hall_ptr->dt_commutate_m_average = hall_ptr->dt_commutate_m_sum >> RS_DT_AVERAGE;

       if(hall_ptr->dt_commutate_m_sample_index < (NUM_DT_SAMPLES-1)) hall_ptr->dt_commutate_m_sample_index += 1;
			 else hall_ptr->dt_commutate_m_sample_index = 0;

//       if (motor_ptr->motor_enable_cmd == Motor_Enable) hall_ptr->dt_commutate_m_average = motor_ptr->pwm_duty_command;

//
//     calculate dt_commutate_p
//     "p": predicted
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       hall_ptr->dt_commutate_p_pre_pre = hall_ptr->dt_commutate_p_pre;
			 hall_ptr->dt_commutate_p_pre = hall_ptr->dt_commutate_p;
//
//     error
       hall_ptr->e_dt_commutate = hall_ptr->dt_commutate_m_average - hall_ptr->dt_commutate_p_pre;
//
//     integration
       hall_ptr->s_e_dt_commutate += hall_ptr->e_dt_commutate;

			 if(hall_ptr->s_e_dt_commutate > MAX_S_E_DT_COMMUTATE) hall_ptr->s_e_dt_commutate = MAX_S_E_DT_COMMUTATE;
			 else if (hall_ptr->s_e_dt_commutate < (-MAX_S_E_DT_COMMUTATE)) hall_ptr->s_e_dt_commutate = (-MAX_S_E_DT_COMMUTATE);
//
//     PI
       hall_ptr->dt_commutate_p += hall_ptr->e_dt_commutate>>3;
			 hall_ptr->dt_commutate_p += hall_ptr->s_e_dt_commutate>>1;

//       hall_ptr->dt_commutate_p = hall_ptr->dt_commutate_p_pre<<1;
//       hall_ptr->dt_commutate_p -= hall_ptr->dt_commutate_p_pre_pre;
//       hall_ptr->dt_commutate_p += hall_ptr->e_dt_commutate>>1;
//
//     clear DMA flags
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       CLEAR_DMA_FLAG_HALL_U;
       CLEAR_DMA_FLAG_HALL_V;
       CLEAR_DMA_FLAG_HALL_W;

//     feed watch-dog
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       hall_ptr->watchdog_cntr = 0;
       hall_ptr->watchdog = False;
       hall_ptr->cntr_dt_reset = 0;
//
//     calculate predicted PWM number
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       switch(hall_ptr->num_pwm_60d_p)
       {
         case 4:
           if PS_LOWER_THAN_4762RPM hall_ptr->num_pwm_60d_p = 5;
         break;
         case 5:
           if PS_HIGHER_THAN_4761RPM hall_ptr->num_pwm_60d_p = 4;
           if PS_LOWER_THAN_3987RPM  hall_ptr->num_pwm_60d_p = 6;
         break;
         case 6:
           if PS_HIGHER_THAN_3986RPM hall_ptr->num_pwm_60d_p = 5 ;
           if PS_LOWER_THAN_3297RPM  hall_ptr->num_pwm_60d_p = 7 ;
         break;
         case 7:
           if PS_HIGHER_THAN_3296RPM hall_ptr->num_pwm_60d_p = 6 ;
           if PS_LOWER_THAN_2858RPM  hall_ptr->num_pwm_60d_p = 8 ;
         break;
         case 8:
           if PS_HIGHER_THAN_2857RPM hall_ptr->num_pwm_60d_p = 7 ;
           if PS_LOWER_THAN_2522RPM  hall_ptr->num_pwm_60d_p = 9 ;
         break;
         case 9:
           if PS_HIGHER_THAN_2521RPM hall_ptr->num_pwm_60d_p = 8 ;
           if PS_LOWER_THAN_2256RPM  hall_ptr->num_pwm_60d_p = 10;
         break;
         case 10:
           if PS_HIGHER_THAN_2255RPM hall_ptr->num_pwm_60d_p = 9 ;
           if PS_LOWER_THAN_2041RPM  hall_ptr->num_pwm_60d_p = 11;
         break;
         case 11:
           if PS_HIGHER_THAN_2040RPM hall_ptr->num_pwm_60d_p = 10;
           if PS_LOWER_THAN_1864RPM  hall_ptr->num_pwm_60d_p = 12;
         break;
         case 12:
           if PS_HIGHER_THAN_1863RPM hall_ptr->num_pwm_60d_p = 11;
           if PS_LOWER_THAN_1715RPM  hall_ptr->num_pwm_60d_p = 13;
         break;
         case 13:
           if PS_HIGHER_THAN_1714RPM hall_ptr->num_pwm_60d_p = 12;
           if PS_LOWER_THAN_1588RPM  hall_ptr->num_pwm_60d_p = 14;
         break;
         case 14:
           if PS_HIGHER_THAN_1587RPM hall_ptr->num_pwm_60d_p = 13;
           if PS_LOWER_THAN_1478RPM  hall_ptr->num_pwm_60d_p = 15;
         break;
         case 15:
           if PS_HIGHER_THAN_1477RPM hall_ptr->num_pwm_60d_p = 14;
           if PS_LOWER_THAN_1383RPM  hall_ptr->num_pwm_60d_p = 16;
         break;
         case 16:
           if PS_HIGHER_THAN_1382RPM hall_ptr->num_pwm_60d_p = 15;
           if PS_LOWER_THAN_1299RPM  hall_ptr->num_pwm_60d_p = 17;
         break;
         case 17:
           if PS_HIGHER_THAN_1298RPM hall_ptr->num_pwm_60d_p = 16;
           if PS_LOWER_THAN_1225RPM  hall_ptr->num_pwm_60d_p = 18;
         break;
         case 18:
           if PS_HIGHER_THAN_1224RPM hall_ptr->num_pwm_60d_p = 17;
           if PS_LOWER_THAN_1159RPM  hall_ptr->num_pwm_60d_p = 19;
         break;
         case 19:
           if PS_HIGHER_THAN_1158RPM hall_ptr->num_pwm_60d_p = 18;
           if PS_LOWER_THAN_1099RPM  hall_ptr->num_pwm_60d_p = 20;
         break;
         case 20:
           if PS_HIGHER_THAN_1098RPM hall_ptr->num_pwm_60d_p = 19;
           if PS_LOWER_THAN_1046RPM  hall_ptr->num_pwm_60d_p = 21;
         break;
         case 21:
           if PS_HIGHER_THAN_1045RPM hall_ptr->num_pwm_60d_p = 20;
           if PS_LOWER_THAN__997RPM  hall_ptr->num_pwm_60d_p = 22;
         break;
         case 22:
           if PS_HIGHER_THAN__996RPM hall_ptr->num_pwm_60d_p = 21;
           if PS_LOWER_THAN__953RPM  hall_ptr->num_pwm_60d_p = 23;
         break;
         case 23:
           if PS_HIGHER_THAN__952RPM hall_ptr->num_pwm_60d_p = 22;
           if PS_LOWER_THAN__912RPM  hall_ptr->num_pwm_60d_p = 24;
         break;
         case 24:
           if PS_HIGHER_THAN__911RPM hall_ptr->num_pwm_60d_p = 23;
           if PS_LOWER_THAN__875RPM  hall_ptr->num_pwm_60d_p = 25;
         break;
         case 25:
           if PS_HIGHER_THAN__874RPM hall_ptr->num_pwm_60d_p = 24;
           if PS_LOWER_THAN__841RPM  hall_ptr->num_pwm_60d_p = 26;
         break;
         case 26:
           if PS_HIGHER_THAN__840RPM hall_ptr->num_pwm_60d_p = 25;
           if PS_LOWER_THAN__809RPM  hall_ptr->num_pwm_60d_p = 27;
         break;
         default:
           if PS_HIGHER_THAN__808RPM hall_ptr->num_pwm_60d_p = 26;
         break;
       } /*switch(hall_ptr->num_pwm_60d_p)*/
//
       SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB1), hall_ptr->num_pwm_60d_m);
       SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB2), hall_ptr->num_pwm_60d_p);
       SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB3), hall_ptr->num_pwm_60d_m - hall_ptr->num_pwm_60d_p);

       SET_STDSCI_PACK_32_TX_OVERRUN(&(btx_ptr->pck_0xA0), &(btx_ptr->pck_0xA1), hall_ptr->dt_commutate_m_average);
       SET_STDSCI_PACK_32_TX_OVERRUN(&(btx_ptr->pck_0xA2), &(btx_ptr->pck_0xA3), hall_ptr->dt_commutate_p);
//     SET_STDSCI_PACK_32_TX_OVERRUN(&(btx_ptr->pck_0xA4), &(btx_ptr->pck_0xA5), hall_ptr->e_dt_commutate);

//     SET_STDSCI_PACK_32_TX_OVERRUN(&(btx_ptr->pck_0xA4), &(btx_ptr->pck_0xA5), hall_ptr->dt_base_commutate);

//     SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB0), hall_ptr->hall_value);
//     SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0xB2), hall_ptr->num_pwm_60d_p);
     }
     else
     {
//     0x53B5 = 0x1885D50/(36MHz/30kHz),
//     0x34512 = 0xF53A520/(36MHz/30kHz)
//     0x1885D50 corresponds to 1rpm
//     0xF53A520 corresponds to 0.1rpm
//     30kHz is chopping frequency
//     36MHz is capture counting frequecy

       if(hall_ptr->watchdog_cntr>0x53B5)
       {
				 if(hall_ptr->watchdog == False) hall_ptr->watchdog = True;
       }
			 else hall_ptr->watchdog_cntr++;
     } /*if (BOOLE_DMA_RENEWED)*/

     if(hall_ptr->watchdog == True)
		 {
			 if(hall_ptr->cntr_dt_reset < NUM_DT_SAMPLES)
       {
			   hall_ptr->dt_commutate_m_sum -= hall_ptr->dt_commutate_m_buffer[hall_ptr->dt_commutate_m_sample_index];
			   hall_ptr->dt_commutate_m_buffer[hall_ptr->dt_commutate_m_sample_index] = ARR_HALL_CAP;
			   hall_ptr->dt_commutate_m_sum += ARR_HALL_CAP;
			   hall_ptr->dt_commutate_m_average = hall_ptr->dt_commutate_m_sum >> RS_DT_AVERAGE;

         if(hall_ptr->dt_commutate_m_sample_index < (NUM_DT_SAMPLES-1)) hall_ptr->dt_commutate_m_sample_index += 1;
			   else hall_ptr->dt_commutate_m_sample_index = 0;

         if(hall_ptr->cntr_dt_reset == (NUM_DT_SAMPLES-1))
         {
           hall_ptr->dt_commutate_p_pre_pre = hall_ptr->dt_commutate_p_pre;
           hall_ptr->dt_commutate_p_pre = hall_ptr->dt_commutate_p;
           hall_ptr->dt_commutate_p = hall_ptr->dt_commutate_m_average;
		 
           hall_ptr->e_dt_commutate = 0;
           hall_ptr->s_e_dt_commutate = 0;
           hall_ptr->d_e_dt_commutate = 0;
           hall_ptr->cntr_dt_reset++;
				 }

         hall_ptr->cntr_dt_reset++;
			 } /*if(hall_ptr->cntr_dt_reset < NUM_DT_SAMPLES)*/
		 } /*if(hall_ptr->watchdog == True)*/
   } /*void ESC_Observer_Hall(void)*/
//
   void ESC_Observer_Hall_Reset(void)
   {
     Hall_Observer* hall_ptr;
		 hall_ptr = &bldcm_hall_observer_m1;

		 u8 i=0;
		 
     hall_ptr->dt_commutate_m_sample_index = 0;
		 hall_ptr->dt_commutate_m_average = ARR_HALL_CAP;
		 
		 for (i=0;i<NUM_DT_SAMPLES;i++)
     {
       hall_ptr->dt_commutate_m_buffer[i] = ARR_HALL_CAP;
			 hall_ptr->dt_commutate_m_sum += ARR_HALL_CAP;
     }

     hall_ptr->dt_commutate_p = ARR_HALL_CAP;		 
     hall_ptr->dt_commutate_p_pre = ARR_HALL_CAP;
     hall_ptr->dt_commutate_p_pre_pre = ARR_HALL_CAP;
		 
		 hall_ptr->e_dt_commutate = 0;
		 hall_ptr->s_e_dt_commutate = 0;
		 hall_ptr->d_e_dt_commutate = 0;

     hall_ptr->watchdog_cntr = 0;
     hall_ptr->watchdog = False;
     hall_ptr->cntr_dt_reset = 0;

     hall_ptr->hall_value &= BOOLE_HALL_W_RESET? ~BIT_HALL_W:0xFF;
     hall_ptr->hall_value |= BOOLE_HALL_V_SET? BIT_HALL_V:0x00;
     hall_ptr->hall_value &= BOOLE_HALL_U_RESET? ~BIT_HALL_U:0xFF;
     hall_ptr->hall_value |= BOOLE_HALL_W_SET? BIT_HALL_W:0x00;
     hall_ptr->hall_value &= BOOLE_HALL_V_RESET? ~BIT_HALL_V:0xFF;
     hall_ptr->hall_value |= BOOLE_HALL_U_SET? BIT_HALL_U:0x00;  

     REFRESH_CURRENT_HALL_STATE;
     REFRESH_PREVIOUS_HALL_STATE;
		 
		 hall_ptr->observer_state = STATE_HALL_OBSERVER_LS;
   }

//=============================================================================
/// @brief  This function low speed use hall,high speed use bemf
/// @param  None
/// @return None
//=============================================================================
//#ifdef 	Hall_BEMF_SWITCH_MODE_ENABLE
//PAC5XXX_RAMFUNC void hall_bemf_switch_mode(void)
//{
//	BLDC_Controller* motor_ptr;
//	motor_ptr = &bldc_m1;
//	Hall_Sensor* hall_ptr;
//	hall_ptr = &bldc_hall_sensor_m1;
//	fix16_t blanking_sample_counts_temp;

//	hall_ptr->hall_bemf_switch_speed = HertzToTicks(bldc_align_go.switch_speed_hz, TIMER_D_FREQ_F16)>>1 ;
//	switch(hall_bemf_switch_state)
//	{
//		case STATE_HALL_STARTUP:
//			get_hall_value_and_change_mos_state();
//			if(motor_ptr->app_measured_speed <= (hall_ptr->hall_bemf_switch_speed - HALL_BEMF_SWISH_SPEED_OFFSET))
//			{
//				motor_ptr->sl_current_state = hall_ptr->sensored_current_state;

//				PAC5XXX_TIMERD->PRD = TIMERD_TICKS_30DEG_PLL;
//			    PAC5XXX_TIMERD->CTL.INTEN = 0;
//				NVIC_EnableIRQ(TimerC_IRQn);
//				NVIC_EnableIRQ(TimerD_IRQn);
//				pac5xxx_timer_d_clear_assert();													// Clear timer
//				pac5xxx_timer_d_clear_deassert();
//				motor_ptr->sl_next_state = motor_ptr->sl_current_state;
//				pac5xxx_tile_register_write(ADDR_CFGAIO9, slcomp_mux[motor_ptr->sl_current_state]);		// MODE9[1:0] = 01b (CT Vfilt), OPT9[1:0] = 0bxx (AIO7), POL9 = 0 (act high), MUX[2:0] = n/a
//				motor_ptr->samplecounter = 0;
//				motor_ptr->wait_30degree_enable = 1;
//				motor_ptr->motorspeed_buffer_blanking[0] = motor_ptr->app_measured_speed;
//				motor_ptr->motorspeed_buffer_blanking[1] = motor_ptr->app_measured_speed;
//				motor_ptr->speed_sample_index_blanking = 0;
//				motor_ptr->motorspeed_sum_blanking = motor_ptr->app_measured_speed << 1;
//				/* Calculate automatic blanking time using motor last two commutation times using moving average filter */
//				blanking_sample_counts_temp = fix16_mul_new_16_16(RATIO_BW_TIMERC_FREQ_TIMERD_FREQ,(motor_ptr->motorspeed_sum_blanking<<16) );
//				motor_ptr->blanking_sample_counts = fix16_mul_new_16_16(blanking_sample_counts_temp,motor_ptr->motor_auto_blank_percent ) >> 16;


//				bldc_align_go.align_and_go_state = STATE_STARTUP_DONE;
//				get_zero_cross_point_state = STATE_TIMERC_BLANKING_CYCLE_TIME;
//				hall_bemf_switch_state = STATE_HALL_SWITCH_TO_BEMF;
//			}
//			break;
//		case STATE_HALL_SWITCH_TO_BEMF:
//			get_zero_crossing_point();
//			break;
//		default:
//			break;
//	}
//}
//#endif
