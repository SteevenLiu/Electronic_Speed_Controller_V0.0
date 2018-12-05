// -----------------------------------------------------------
// FILE: ESC_BLDCM_Config.h
//
// Description: This is a template for newly created .h files.
//
// -----------------------------------------------------------
// Release Date: 2018-09-12;
// Authour: Steven Liu;
// -----------------------------------------------------------
#ifndef __ESC_BLDCM_Config_H
#define __ESC_BLDCM_Config_H
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_Device.h"
// # include "ESC_StandardSCI_Protocal.h"
 
 # define LS_MotorSpeed_Cntr          12
 # define RS_Average_Speed            3
 # define NUM_SPEED_SAMPLES           8// How many samples needed to accumulate for speed calculation
 # define NUM_SPEED_SAMPLES_BLANKING  2// Array length to hold motor speed used for automatic delay calculation
 # define MIN_SPEED 0x1FFF0000
 # define MIN_SPEED_CNTR 0x1FFF0
 # define MIN_SPEED_SUM 0xFFF80000

 # define OVER_CURRENT_FLAG 0x02

 # define DELAY_SWITCH_TO_SPEED_LOOP_COUNTS  6000  //100ms

 # define Motor_Enable  0x5555
 # define Motor_Disable 0x6666

//
// 2nd.datatypes
// -----------------------------------------------------------
// 1.servo status
// ...........................................................
   /**
   @brief Servo status bits.
   */
  typedef volatile enum
  {
    status_motor_enabled      = 0x0001,//1,
    status_over_current       = 0x0002,//2,
    status_closed_loop        = 0x0004,//4,
    status_lose_angle         = 0x0008,//8,
    status_motor_stall        = 0x0010,//16,
    status_Vbus_overvoltage   = 0x0020,//32,
    status_Vbus_undervoltage  = 0x0040,//64,
    status_open_phase         = 0x0080,//128,
    status_hall_error         = 0x0100,//256,
    status_open_loop          = 0x0200,//512,
    status_pwm_duty_loop      = 0x0400,//1024,
		status_starup_fail        = 0x0800,//2048,
		status_TX_overrun         = 0x1000//4096
  } StatusStateBits;
//
// 2.BLDCM Main State Machine
// ...........................................................
  /**
  @brief States for Main State Machine.
  */
  typedef volatile enum
  {
    STATE_MAIN_STOP_STANDBY        = 0,
    STATE_MAIN_OL                  = 1,
    STATE_MAIN_OL_SWITCH_CL_WAIT   = 2,
    STATE_MAIN_CL_SPEED            = 3,
    STATE_MAIN_CL_CURRENT          = 4,
    STATE_MAIN_CL_PWM_DUTY         = 5,
    STATE_MAIN_SIM_DETECT          = 6,
    STATE_MAIN_STOP_BRAKING        = 7,
    STATE_MAIN_COASTING            = 8,
    STATE_MAIN_FAULT               = 9,
  }eBLDCM_Main_Machine_State;
//
// 3.BLDCM Control State Machine
// ...........................................................
  /**
  @brief States for Control State Machine.
  */
  typedef volatile enum
  {
    STATE_CONTROL_IDLE                 = 0,
    STATE_CONTROL_OL                   = 1,
    STATE_CONTROL_OL_SWITCH_CL_WAIT    = 2,
    STATE_CONTROL_CL_SPEED             = 3,
    STATE_CONTROL_CL_CURRENT           = 4,
    STATE_CONTROL_CL_PWM_DUTY          = 5,
    STATE_CONTROL_SIM_DETECT           = 6,
    STATE_CONTROL_BRAKING_PWM_CONTROL  = 7,
    STATE_CONTROL_COASTING             = 8
  }eSub_Control_Machine_State;
//
// 4.BLDCM Controller
// ...........................................................
  /**
  @brief Data structure for PID.
  */
  typedef struct
  {
    // Operational variables - updated controller
    s32 aw_prev;  // Anti-windup from the previous PID calculation
    s32 I_prev;   // I term from the previous PID calculation
    s32 PI;       // Current value of PID controller output before saturation check
    s32 PI_sat;   // Current value of PID controller output after saturation check
  
    // Configuration variables - specified by user. Controller does not change
  
    s32 Kp;         // Proportional gain term * 2^8 (scaling for integer math)
    s32 Ki;         // Integral gain term * 2^8 (scaling for integer math)
    s32 Ks;         // Saturation gain term * 2^8 (scaling for integer math)
    s32 min_value;  // Saturation filter minimum output value
    s32 max_value;  // Saturation filter maximum output value
    s32 Td;         // Td for d/dt calculation (scaled by 2^10)
  } PID_Data_Type;

  /**
  @brief Value for motor enable command.
  */
//  typedef enum
//  {
//    Motor_Disable = 0x0000,
//    Motor_Enable  = 0x5555,
//  } Motor_Enable_CMD_Data_Type;	
	
  /**
  @brief BLDCM cotroller.
  */
  typedef struct
  {
    volatile s32 Iq_ref;                            // Iq_ref
    volatile s32 Iq_ref_sp;                         // Iq_ref setpoint
    volatile s32 Iq_ref_cl;                         // Iq_ref for close loop
    volatile s32 Iq_fb;                             // Iq_fb
    volatile s32 Iq_previous;                       // Iq previous value use for digital filtering
    volatile s32 Iq_prev_non_filtered;              // Iq previous value use for backup as good last non filtered value
    volatile s32 Iq_filter_gain;                     
    volatile PID_Data_Type Iq_pid;	                 // PID controller for Iq
    volatile PID_Data_Type speed_pid;
    volatile s32 duty_percent_fix16;
                                                
    volatile s16 Ibus_ADC;                          // Stored Iu ADC value
    volatile s32 Iq_ramp_rate;	                     // Iq ref Ramp Rate
    volatile u8  speed_pid_skips;                    // Number of times speed PID has been skipped
    volatile u8  enable_current_control;             // Current control enable disable flag
    volatile u8  num_of_good_zc_samples;             // Number of good zero cross samples, need to validate good zero crossing
    volatile u16 blanking_sample_counts;            // Number of PWM cycles we blank out zero cross sensing after commutation
    volatile s32 motor_close_loop_speed;            // Motor close loop speed in int format, 1HZ - 1 count
    volatile s32 motor_close_loop_current;
    volatile s32 motor_close_loop_speed_temp;       // Motor close loop speed temp variable use for speed ramp
    volatile s32 motor_close_loop_speed_ramp;       // Motor close loop speed ramp rate variable
    volatile s32 adc_zero_cross_offset_percentage;  // Used in ADC zero cross detection as an offset to move center tap point
    volatile u8  auto_open_to_close_loop_sw_count;   // Use to check open loop speed number if cycles before switch over           /*!< Value comes from GUI as an percentage */
    volatile s32 motor_auto_blank_percent;          // Blanking time comes in percentage from GUI
    volatile s32 ratio_bw_pwmFreq_timerDFreq;
    volatile s32 vbus_voltage_value;
  
    volatile u8  motor_enabled;
    volatile u8  debug_buffer_command;
  
    volatile u8  control_mode_select_number;
    volatile s32 closed_loop_current_command;
  
    volatile u32 coasting_timeout_counts;
    volatile u32 coasting_timeout;
  
    // configuration
    volatile u32 app_status;
    volatile u32 app_measured_speed;
    volatile u32 app_speed_ref;
    volatile u32 app_pwm_freq_khz;
    volatile s32 app_control_freq_khz;
    volatile s32 app_speed_command;
    volatile u32 app_over_current_limit;
    volatile u32 app_over_current_resistor;
    volatile u32 app_amplifier_gain;
    volatile u32 app_amplifier_gain_register;
  
    // Global Variables
    volatile u16 motor_enable_cmd;
    volatile s32 I_total_factor;
    volatile u8  oc_reset_flag;
    volatile u8  reverse_tune_flag;
    volatile s32 main_machine_control_counts;
    volatile u16 motor_lose_angle_count;
  
    // PWM duty cycle
    volatile s32 align_pwm_duty_max;
    volatile u16 pwm_control_duty_cycle;
    volatile u16 pwm_control_duty_change_delay_counts;
    volatile u16 final_pwm_duty;
    volatile u16 pwm_duty_command;
    volatile u16 pwm_duty_Fall_buf;
    volatile u16 temp_pwm_duty;
    volatile u16 temp_pwm_duty_pre;
    volatile u16 temp_pwm_duty_u;
    volatile u16 temp_pwm_duty_v;
    volatile u16 temp_pwm_duty_w;
    volatile u16 pwm_timer_ticks;                // Number of timer A ticks for PWM period
    volatile s32 one_div_pwm_timer_ticks_fix16;
  
    volatile u8  sample;
    volatile u8  samplecounter;
    volatile u8  target_sample;                  // Last good commutation state sample store
    volatile u16 speed_sample_index;
    volatile u16 speed_sample_index_blanking;
    volatile u8  wait_30degree_enable;           // Force to invalid value to force commutation on startup
    volatile u8  sl_current_state;               // Force to invalid value to force commutation on startup
    volatile u8  sl_next_state;                  // Force to invalid value to force commutation on startup
    volatile s32 commutation_advanced_rise;
    volatile s32 commutation_advanced_fall;
  
    // Array to store speed for one electrical cycle
    volatile u16 call_speed_loop_delay_count;
    volatile u32 motorspeed_cntr;
    volatile u8 motorspeed_hall_A_current;
		volatile u8 motorspeed_hall_B_current;
		volatile u8 motorspeed_hall_C_current;
    volatile u8 motorspeed_hall_A_pre;
		volatile u8 motorspeed_hall_B_pre;
		volatile u8 motorspeed_hall_C_pre;
    volatile u16 motorspeed_cntr_commute_Phs_I;
    volatile u16 motorspeed_cntr_commute_Phs_II;
    volatile u16 motorspeed_cntr_commute_Phs_III;
    volatile u16 motorspeed_cntr_commute_Phs_IV;
    volatile u16 motorspeed_cntr_commute_Phs_V;
    volatile u16 motorspeed_cntr_commute_Phs_VI;
    volatile u32 motorspeed_cntr_Phs_I;
    volatile u32 motorspeed_cntr_Phs_II;
    volatile u32 motorspeed_cntr_Phs_III;
    volatile u32 motorspeed_cntr_Phs_IV;
    volatile u32 motorspeed_cntr_Phs_V;
    volatile u32 motorspeed_cntr_Phs_VI;
    volatile u32 motorspeed;
    volatile u32 motorspeed_sum;
    volatile s32 motor_speed_sum_fix16;
    volatile s32 motorspeed_sum_blanking_fix16;
    volatile u32 motorspeed_sum_blanking;
    volatile u32 motorspeed_buffer[NUM_SPEED_SAMPLES];
    volatile u16 motorspeed_buffer_blanking[NUM_SPEED_SAMPLES_BLANKING];
    volatile u16 timer_d_base_timer_first;
    volatile u16 timer_d_base_timer_second;
    volatile u16 timer_d_base_timer_offset;
    volatile u32 average_speed;
    volatile u16 commutation_blanking_time;
    volatile s32 comm_advanced_delay_temp;
    volatile u16 comm_1advanced_delay;
  
    volatile u8  timerA_isr_counts;
  
    volatile u16 charge_delay_count;
    volatile u16 charge_done_flag;

    volatile s32 w_FeedBack;
    volatile s32 w_Target;
    volatile s32 error_w;
    volatile s32 s_error_w;
		volatile s32 max_s_error_w;
    volatile s32 p_dt;
    volatile s32 i_dt;

//  u16 test_0;
//  u16 test_1;
//  u16 test_2;	
  } BLDCM_Controller;
//
// 5.Hall Sensor
// ...........................................................
  /**
  @brief Data Structure for hall sensor process.
  */
//  typedef enum
//  {
//    STATE_HALL_OK     = 0,
//    STATE_HALL_ERR_I  = 1,
//    STATE_HALL_ERR_II = 2,
//  }Hall_Err_State;	
	
  typedef struct
  {
    volatile u8  hall_value;
    volatile u8  sensored_current_state;
    volatile u8  sensored_current_state_pre;
    volatile u16 hall_bemf_switch_speed;
    volatile u32 hall_to_mos_state_detect;
    volatile u8  commutate_flag;
//		Hall_Err_State state_hall_err;
  } Hall_Sensor;
//
// x.Hall Observer
// ...........................................................
  /**
  @brief Data Structure for hall sensor process.
  */
//  typedef enum
//  {
//    STATE_HALL_OK     = 0,
//    STATE_HALL_ERR_I  = 1,
//    STATE_HALL_ERR_II = 2,
//  }Hall_Err_State;	

  typedef volatile enum
  {
    STATE_HALL_OBSERVER_LS = 0,
    STATE_HALL_OBSERVER_HS = 1,
  }eSub_Hall_Observer_State;
	
  typedef struct
  {
    volatile u8  hall_value;
    volatile u8  sensored_current_state;
    volatile u8  sensored_current_state_pre;
    volatile u16 hall_bemf_switch_speed;
    volatile u32 hall_to_mos_state_detect;
    volatile u8  commutate_flag;

    volatile u32 t_commutate_m_Hall_U;
    volatile u32 t_commutate_m_Hall_V;
    volatile u32 t_commutate_m_Hall_W;

//    volatile u32 t_commutate_m_Hall_U_temp;
//    volatile u32 t_commutate_m_Hall_V_temp;
//    volatile u32 t_commutate_m_Hall_W_temp;
		
    volatile u32 t_commutate_m_I;
    volatile u32 t_commutate_m_II;
    volatile u32 t_commutate_m_III;
    volatile u32 t_commutate_m_IV;
    volatile u32 t_commutate_m_V;
    volatile u32 t_commutate_m_VI;

    volatile u32 t_commutate_m;
    volatile u32 t_commutate_m_pre;

    volatile u32 dt_commutate_m;
    volatile u32 dt_commutate_m_sum;
    volatile u32 dt_commutate_m_buffer[8];
    volatile u32 dt_commutate_m_average;
		volatile u32 dt_commutate_m_sample_index;

    volatile s32 dt_commutate_p;
    volatile s32 dt_commutate_p_pre;
    volatile s32 dt_commutate_p_pre_pre;
		
    volatile s32 e_dt_commutate;
    volatile s32 s_e_dt_commutate;
    volatile s32 d_e_dt_commutate;

//    volatile u32 dt_commutate_phs_I;
//    volatile u32 dt_commutate_phs_II;
//    volatile u32 dt_commutate_phs_III;
//    volatile u32 dt_commutate_phs_IV;
//    volatile u32 dt_commutate_phs_V;
//    volatile u32 dt_commutate_phs_VI;
//		volatile u8  dma_ready;
//		Hall_Err_State state_hall_err;

    volatile Boole watchdog;
		volatile u32 watchdog_cntr;
		volatile u16 cntr_dt_reset;

    volatile u32 t_base_temp;
		volatile u32 t_base_commutate;
		volatile u32 dt_base_temp;
		volatile u32 dt_base_commutate;

    volatile Boole hall_state_legal;
    volatile Boole hall_state_legal_pre;

    eSub_Hall_Observer_State observer_state_pre;
    eSub_Hall_Observer_State observer_state;

    volatile u16 cntr_pwm_60d;
		volatile s16 num_pwm_60d_m;
		volatile s16 num_pwm_60d_p;
		volatile s16 max_d_num_pwm_60d;
		volatile s16 min_d_num_pwm_60d;
		volatile s16 d_num_pwm_60d;
    volatile u32 dt_m_max_d_num_pwm_60d;
		volatile u32 cntr_over_d_num_60d;
  } Hall_Observer;

//
// 6.Reserved others
// ...........................................................
  /**
  @brief States for ...
  */
  typedef enum
  {
    STATE_TIMERC_FIRST_SAMPLE         = 0,
    STATE_TIMERC_GOOD_SAMPLES         = 1,
    STATE_TIMERC_ZERO_CROSS_POINT     = 2,
    STATE_TIMERC_WAIT_COMMUTATE       = 3,
    STATE_TIMERC_BLANKING_CYCLE_TIME  = 4,
  }eGet_Zero_Cross_Point_State;

  /**
  @brief States for ...
  */
  typedef enum
  {
    STATE_HALL_STARTUP         = 0,
    STATE_HALL_SWITCH_TO_BEMF  = 1,
  }eHall_Bemf_Switch_State;

  /**
  @brief States for ...
  */
  typedef enum
  {
    STATE_STARTUP_INIT            = 0,
    STATE_STARTUP_ALIGN           = 1,
    STATE_STARTUP_ALIGN_DELAY     = 2,
    STATE_STARTUP_GO              = 3,
    STATE_STARTUP_SWITCH_TO_BEMF  = 4,
    STATE_STARTUP_DONE            = 5,
  }eMotor_Align_Go_State;

  typedef struct
  {
    eMotor_Align_Go_State align_and_go_state;
    u16 align_ticks;                // Number of PWM ticks to keep in align mode
    u16 align_ticks_store;
    u16 align_ticks_temp;           // Temp variable to hold Number of PWM ticks in align mode
    u16 start_speed_ticks_period;   // Variable to hold Number of PWM ticks in go mode
    u16 start_speed_ticks_temp;     // Temp variable to hold number of PWM ticks to keep in go mode
    u16 align_go_duty_cycle;        // Align and go duty cycle
    u16 align_go_duty_cycle_store;  // Align and go duty cycle
    u16 go_step;                    // Valid current go state for motor
    s32  accel_rate_time_base;      // Number of 1 ms ticks in between speed changes
    s32  start_speed_hz;
    s32  current_speed_hz;
    s32  switch_speed_hz;
    u16 switch_speed_ticks;
    u16 AccelRateTimeBaseTemp;
    s32  accel_rate_factor;
    u8  auto_acceleration_mode;
  
    u16 sine_wave_index;
    s32  wave_pwm_duty_u;
    s32  wave_pwm_duty_v;
    s32  wave_pwm_duty_w;
  }Motor_Align_Go;

  /**
  @brief States for SIM state machine.
  */
  typedef enum
  {
    STATE_SIM_INIT            = 0,
    STATE_SIM_DETECT          = 1,
    STATE_SIM_STOP            = 2,
    STATE_SIM_MOVE            = 3,
    STATE_SIM_SAME_DIRECTION  = 4,
    STATE_SIM_DIFF_DIRECTION  = 5,
    STATE_SIM_BRAKING         = 6,
  }eSIM_State;

  /**
  @brief Data Structure for SIM.
  */
  typedef struct
  {
    eSIM_State sim_process_state;
  
    s32 bemf_u ;
    s32 bemf_v ;
    s32 bemf_w ;
  
    s32 bemf_u_init;
    s32 bemf_v_init;
    s32 bemf_w_init;
    s32 bemf_uvw_init_center_tap_voltage;
  
    s32 delta_uv_bemf;
    s32 delta_uw_bemf;
    s32 delta_vw_bemf;
    s32 uvw_center_tap_voltage ;
    u8 step_state;
    u8 step_state_p;
    u8 bemf_state;
    u8 bemf_state_p;
    u8 direction_flag;
    u8 direction_flag_P;
  
    s32 bemf_voltage;
    u16 input_pwm_duty_count;
    u8 motor_stop_bemf_flag;
    u16 detect_diff_position_counts;
  
    u16 braking_vbus_voltage_ref;
    u16 braking_vbus_voltage_fdb;
    u16 braking_depth_pwm_duty_counts;
    u16 braking_bemf_u;
    u16 braking_bemf_v;
    u16 braking_bemf_w;
    u16 braking_bemf_uvw_center_tap_voltage;
    u8  braking_detect_motor_stop_flag;
    u8  braking_stop_counts;
    u8  braking_restart_disable_driver_counts;
    u8  motor_in_motion_flag;
    u32 in_braking_state_counts;
  
    s32  bemf_ratio;
    s32  bemf_adc_scal_fator;
    u16 each_phs_bemf_delta_threshold;
    u8  keep_detect_step_times;
    s32  ratio_timerc_timerd_freq;
  } Sim_Detect;

  /**
  @brief Data Structure for ...
  */
  typedef struct
  {
    s32 app_measured_speed_fix16;
    s32 app_speed_ref_fix16;
    s32 ibus_adc_fix16;
  
    s32 sl_current_hall_fix16;
    s32 sl_current_state_fix16;
    u8 sl_current_step_position;
    u8 sl_current_step_position_pre;
  
    s32 aio7_adc_value_fix16;
    s32 aio8_adc_value_fix16;
    s32 aio9_adc_value_fix16;
    s32 centre_adc_value_fix16;
    u8 phase_comparator_output;
  } Pwm_Dac_Debug;
//
// 3rd. variables
// -----------------------------------------------------------
// structural and enumerate body
   extern Motor_Align_Go               bldcm_align_go;
   extern BLDCM_Controller             bldcm_m1;
   extern Hall_Sensor                  bldcm_hall_sensor_m1;
   extern Hall_Observer                bldcm_hall_observer_m1;	
   extern eBLDCM_Main_Machine_State    main_machine_state;
   extern eBLDCM_Main_Machine_State    main_machine_state_pre;
   extern eSub_Control_Machine_State   control_machine_state;
   extern eSub_Control_Machine_State   control_machine_state_pre;
   extern eGet_Zero_Cross_Point_State  get_zero_cross_point_state;
   extern eHall_Bemf_Switch_State      hall_bemf_switch_state;

//   extern u16 feedback_CodeEfficiency_SMC_pre;
   extern u16 feedback_CodeEfficiency_SMC;
	 extern u16 feedback_CodeEfficiency_SMM;

	 extern volatile u32 feedback_Test_0_Long;
	 extern volatile u32 feedback_Test_1_Long;
	
	 extern volatile u16 feedback_Test_0;
	 extern volatile u16 feedback_Test_1;
	 extern volatile u16 feedback_Test_2;
   extern volatile u16 feedback_Test_3;
   extern volatile u16 feedback_Test_4;

//   extern STDSCI_PACK_TX pck_STD_TX_0xA0; //2018.11.16 temp
//   extern STDSCI_PACK_TX pck_STD_TX_0xA1; //2018.11.16 temp

//
// 4th.function prototypes
// -----------------------------------------------------------

#endif /*#ifndef __ESC_BLDCM_Config_H*/
// no more.
// ----------------------------------------------------------- 

