
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

#ifndef BLDC_APPLICATION_H
#define BLDC_APPLICATION_H

  # include "ESC_Device.h"

#define NUM_SPEED_SAMPLES           6  // How many samples needed to accumulate for speed calculation
#define NUM_SPEED_SAMPLES_BLANKING  2  // Array length to hold motor speed used for automatic delay calculation

  typedef enum
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
  } StatusStateBits;
 
  typedef enum
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
  }eBLDC_Main_Machine_State;
  
  typedef enum
  {
    STATE_CONTROL_IDLE                 = 0,
    STATE_CONTROL_OL                   = 1,
    STATE_CONTROL_OL_SWITCH_CL_WAIT    = 2,
    STATE_CONTROL_CL_SPEED             = 3,
    STATE_CONTROL_CL_CURRENT           = 4,
    STATE_CONTROL_CL_PWM_DUTY          = 5,
    STATE_CONTROL_SIM_DETECT           = 6,
    STATE_CONTROL_BRAKING_PWM_CONTROL  = 7,
    STATE_CONTROL_COASTING             = 8,
  }eSub_Control_Machine_State;
  
  typedef enum
  {
    STATE_TIMERC_FIRST_SAMPLE         = 0,
    STATE_TIMERC_GOOD_SAMPLES         = 1,
    STATE_TIMERC_ZERO_CROSS_POINT     = 2,
    STATE_TIMERC_WAIT_COMMUTATE       = 3,
    STATE_TIMERC_BLANKING_CYCLE_TIME  = 4,
  }eGet_Zero_Cross_Point_State;
  
  typedef enum
  {
    STATE_HALL_STARTUP         = 0,
    STATE_HALL_SWITCH_TO_BEMF  = 1,
  }eHall_Bemf_Switch_State;
  
  typedef enum
  {
    STATE_STARTUP_INIT            = 0,
    STATE_STARTUP_ALIGN           = 1,
    STATE_STARTUP_ALIGN_DELAY     = 2,
    STATE_STARTUP_GO              = 3,
    STATE_STARTUP_SWITCH_TO_BEMF  = 4,
    STATE_STARTUP_DONE            = 5,
  }eMotor_Align_Go_State;
  
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

//....
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
//......  

  typedef struct
  {
    s32 Iq_ref;                            // Iq_ref
    s32 Iq_ref_sp;                         // Iq_ref setpoint
    s32 Iq_ref_cl;                         // Iq_ref for close loop
    s32 Iq_fb;                             // Iq_fb
    s32 Iq_previous;                       // Iq previous value use for digital filtering
    s32 Iq_prev_non_filtered;              // Iq previous value use for backup as good last non filtered value
    s32 Iq_filter_gain;                     
    PID_Data_Type Iq_pid;	                 // PID controller for Iq
    PID_Data_Type speed_pid;                    
    s32 duty_percent_fix16;                 
                                                
    s16 Ibus_ADC;                          // Stored Iu ADC value
    s32 Iq_ramp_rate;	                     // Iq ref Ramp Rate
    u8 speed_pid_skips;                    // Number of times speed PID has been skipped
    u8 enable_current_control;             // Current control enable disable flag
    u8 num_of_good_zc_samples;             // Number of good zero cross samples, need to validate good zero crossing
    u16 blanking_sample_counts;            // Number of PWM cycles we blank out zero cross sensing after commutation
    s32 motor_close_loop_speed;            // Motor close loop speed in int format, 1HZ - 1 count
    s32 motor_close_loop_current;
    s32 motor_close_loop_speed_temp;       // Motor close loop speed temp variable use for speed ramp
    s32 motor_close_loop_speed_ramp;       // Motor close loop speed ramp rate variable
    s32 adc_zero_cross_offset_percentage;  // Used in ADC zero cross detection as an offset to move center tap point
    u8 auto_open_to_close_loop_sw_count;   // Use to check open loop speed number if cycles before switch over           /*!< Value comes from GUI as an percentage */
    s32 motor_auto_blank_percent;          // Blanking time comes in percentage from GUI
    s32 ratio_bw_pwmFreq_timerDFreq;
    s32 vbus_voltage_value;
  
    u8 motor_enabled;
    u8 debug_buffer_command;
  
    u8 control_mode_select_number;
    s32 closed_loop_current_command;
  
    u32 coasting_timeout_counts;
    u32 coasting_timeout;
  
    // configuration
    u32 app_status;
    u32 app_measured_speed;
    u32 app_speed_ref;
    u32 app_pwm_freq_khz;
    s32  app_control_freq_khz;
    s32  app_speed_command;
    u32 app_over_current_limit;
    u32 app_over_current_resistor;
    u32 app_amplifier_gain;
    u32 app_amplifier_gain_register;
  
    // Global Variables
    u8  motor_enable_cmd;
    s32  I_total_factor;
    u8  oc_reset_flag;
    u8  reverse_tune_flag;
    s32  main_machine_control_counts;
    u16 motor_lose_angle_count;
  
    // PWM duty cycle
    s32  align_pwm_duty_max;
    s32  pwm_control_duty_cycle;
    u16 pwm_control_duty_change_delay_counts;
    u16 final_pwm_duty;
    u16 pwm_duty_Fall_buf;
    u16 temp_pwm_duty;
    u16 temp_pwm_duty_u;
    u16 temp_pwm_duty_v;
    u16 temp_pwm_duty_w;
    u16 pwm_timer_ticks;                // Number of timer A ticks for PWM period
    s32  one_div_pwm_timer_ticks_fix16;
  
    u8  sample;
    u8  samplecounter;
    u8  target_sample;                  // Last good commutation state sample store
    u16 speed_sample_index;
    u16 speed_sample_index_blanking;
    u8  wait_30degree_enable;           // Force to invalid value to force commutation on startup
    u8  sl_current_state;               // Force to invalid value to force commutation on startup
    u8  sl_next_state;                  // Force to invalid value to force commutation on startup
    s32  commutation_advanced_rise;
    s32  commutation_advanced_fall;
  
    // Array to store speed for one electrical cycle
    u16 call_speed_loop_delay_count;
    u16 motorspeed;
    u32 motorspeed_sum;
    s32  motor_speed_sum_fix16;
    s32  motorspeed_sum_blanking_fix16;
    u32 motorspeed_sum_blanking;
    u16 motorspeed_buffer[NUM_SPEED_SAMPLES];
    u16 motorspeed_buffer_blanking[NUM_SPEED_SAMPLES_BLANKING];
    u16 timer_d_base_timer_first;
    u16 timer_d_base_timer_second;
    u16 timer_d_base_timer_offset;
    u16 average_speed;
    volatile u16 commutation_blanking_time;
    s32  comm_advanced_delay_temp;
    u16 comm_1advanced_delay;
  
    u8 timerA_isr_counts;
  
    u16 charge_delay_count;
    u16 charge_done_flag;
  
  } BLDC_Controller;
  
  
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
  
  typedef struct
  {
    u8  hall_value;
    u8  sensored_current_state;
    u8  sensored_current_state_pre;
    u16 hall_bemf_switch_speed;
    u32 hall_to_mos_state_detect;
    u8  commutate_flag;
  } Hall_Sensor;
  
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
  
  
  // structural and enumerate body
  extern Motor_Align_Go          		bldc_align_go;
  extern BLDC_Controller           	bldc_m1;
  extern eBLDC_Main_Machine_State    	main_machine_state;
  extern eSub_Control_Machine_State  control_machine_state;
  extern eGet_Zero_Cross_Point_State get_zero_cross_point_state;
  extern eHall_Bemf_Switch_State     	hall_bemf_switch_state;
  
  
  //three phase sine wave table for motor start-up
  extern const s32 sine_wave_3phase[60][3];
  // Commutation state table with Analog MAUX setting
  extern const u8 slcomp_mux[7] ;
  extern const u8 slcomp_next_state[7] ;
  extern const u8 slcomp_last_state[7];
  extern const u8 slcomp_cross_polarity[7] ;					//POLx = 0,active High
  extern const u8 slcomp_next_state_rev[7] ;					//reverse
  extern const u8 slcomp_last_state_rev[7];      				//reverse
  extern const u8 slcomp_cross_polarity_rev[7] ;				//reverse
  
  
  #define ENABLE   (1)
  #define DISABLE  (0)
  
  #define DELAY_CHARGE_COUNTS                5
  #define DELAY_SWITCH_TO_SPEED_LOOP_COUNTS  12
  #define OVER_CURRENT_FLAG                  0x02
  
  //  PWM DAC
  #define PWMDAC_PWM_PIN_PORT_A_DEBUG    	0x38            // Pin mask for LS gate drive PWM for Port A
  
  
  // Definitions
  #define TIMERA_PERIOD_TICKS           781				// Number of timer a ticks for PWM
  #define TIMERB_TICKS_DEBUG_DAC_45KHZ  1111
  #define TIMERB_PERIOD_TICKS_PPM       65535
  #define TIMERC_PERIOD_TICKS           500     		// Number of timer c ticks for 100Khz timer (up timer, HCLK@50MHz, /1)
  #define TIMERD_TICKS_30DEG_PLL        65535             // Number of timer ticks for 30 degree timer (max 335ms per 60 degrees)
  
  #define FIX16_1DOT_024                 	   0x10624
  #define RATIO_BW_TIMERC_FREQ_TIMERD_FREQ   16777   		// TimerC 100Khz:  0x4189 = 65536*(100Kz/(50M/128))  TimerC 160Khz:  26843 = 65536*(160Kz/(50M/128))
  #define TIMER_D_FREQ_F16		            (0x0186A000)			// TMRD Freq = 50MHz / 128 = 195,312.5 Hz (This number is divided by 1000 so it can be represented by a Fix16 type)
  
  #define SPEED_RAMP_COUNTS    5
  #define CURRENT_RAMP_COUNTS  10
  
  #define LED_PIN_MASK         0x01					// Pin mask for LED output PE0
  #define LED_PIN_NUM          0						// Pin number for LED output (active high) PE0
  #define LED1_TOGGLE          (pac5xxx_gpio_out_toggle_e(LED_PIN_MASK))		// Toggle LED state
  #define LED1_ON	             (pac5xxx_gpio_out_pin_set_e(LED_PIN_NUM))		// Set LED to on
  #define LED1_OFF      	     (pac5xxx_gpio_out_pin_clear_e(LED_PIN_NUM))		// Set LED to off
  
  
  #define NIRQ1_PIN_MASK       0x01
  #define NIRQ2_PIN_MASK       0x80
  #define SLCOMP7	             0x10
  #define SLCOMP8	             0x20
  #define SLCOMP9	             0x30
  
  
  #define AIO7_LOW2HIGH        0
  #define AIO7_HIGH2LOW        1
  #define AIO8_LOW2HIGH        0
  #define AIO8_HIGH2LOW        1
  #define AIO9_LOW2HIGH        0
  #define AIO9_HIGH2LOW        1
  
  
  #define HALF_DEGREE_ADV_DLY		        (0x00000222)				// 0.5 degree advance delay factor = 1/2 Comm Adv Delay * 1/2 degree * 1/30 degrees
  
  #define COMMUTATION_BLANKING_COUNT          10
  
  #define IQ_RAMP_RATE                        0x65536            	// 0.01 A, convert into fix16
  #define IQ_REFERENCE                        0x00008000             // 0.5 A, convert to fix16
  #define TD_FOR_IQ_PID                       0x000020C5			    // 8KHZ = 125 usec * 1024 = 0.128* 65536, converted into fix16 = 0x000020CA
  
  #define TRUE   (1)
  #define FALSE  (0)
  
  #define DEFAULT_GOOD_ZERO_CROSS_SAMPLES    3
  #define DEFAULT_CLOSE_LOOP_SPEED           50
  
  #define OPEN_TO_CLOSE_LOOP_GOOD_SPEED_COUNT       1
  #define SPEED_RAMP_RATE_1HZ_SEC                   0x00001999
  
  #define DEFAULT_AUTO_BLANKING_PERCENT             0x00008000  		// 50% of commutation time
  
  #define MATH_ZERO_DOT_ONE_FIX16                   0x1999
  #define MATH_ONE_DIV_SIX_FIX16                    0x2AAA
  #define MATH_ONE_DIV_THREE_FIX16                  0x5555
  
  #define SINE_WAVE_ARRAY_INDEX_MAX     	          59
  #define SINE_WAVE_ARRAY_INDEX_MIN                 0
  
  #define COASTING_DUTY_REDUCE_RATE             	   5
  #endif
