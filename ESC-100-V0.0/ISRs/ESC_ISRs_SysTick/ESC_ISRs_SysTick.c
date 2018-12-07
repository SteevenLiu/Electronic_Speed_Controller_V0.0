// -----------------------------------------------------------
// FILE: ESC_ISRs_SysTick.c
//
// Description: This is a template for newly created .c files.
//
// -----------------------------------------------------------
// Release Date: 2018-09-11;
// Authour: Steven Liu;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
 # include "ESC_ISRs_SysTick.h"

//
// 2nd. variables
// -----------------------------------------------------------
//   u16 i=0;
//   u16 j=0;
//   u16 instr = 0;


//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
// 1. System Tick interrupt service routine
// ...........................................................
// @brief  This function handles SysTick Handler.
// @param  None
// @retval None/
//
   void SysTick_Handler(void)
   {
     BLDCM_Controller* motor_ptr;
     motor_ptr = &bldcm_m1;

     Hall_Observer* hall_ptr;
     hall_ptr = &bldcm_hall_observer_m1;

     STDSCI_BLOCK_TX* btx_ptr;
     btx_ptr = &block_tx;
		 
     Boole overrun_tx = False;

     STDSCI_PACK_BUFF* prx_ptr; 
     prx_ptr = &pack_rx_buff;

		 WatchWindow* ww_ptr;
		 ww_ptr = &num_pwm;		 
		 
     u16 frame_Data;

     main_state_machine();

//   transmit one package every 50ms
		 if(++btx_ptr->tick >49)
     {
       btx_ptr->tick = 0;
       btx_ptr->flag_TC = False;
     }

     if(btx_ptr->flag_TC == True)
     {
			 btx_ptr->pck_0x00.pck = prx_ptr->pck;
       if (btx_ptr->pck_0x00.flag_pck_renewed == True) overrun_tx |= True;
       else btx_ptr->pck_0x00.flag_pck_renewed = True;

       if (1)//prx_ptr->pck.frame.CrcRsd == StdSci_CrcRsdGnrtr(prx_ptr->pck))
       {
         frame_Data  = prx_ptr->pck.frame.DataLwr;
         frame_Data |= (prx_ptr->pck.frame.DataHghr)<<StdSci_CharBits;

         switch (prx_ptr->pck.frame.DataType)
         {
           case CMD_MotorEnable:
             motor_ptr->motor_enable_cmd = frame_Data;
           break;
           case CMD_TargetSpeed:
             motor_ptr->app_speed_command = frame_Data;
           break;
           case CMD_TargetDuty:
             motor_ptr->pwm_duty_command = frame_Data;
           break;
           case CMD_TargetCurrent:
           break;
           case Config_SpeedPid_Ki:
           break;
           case Config_SpeedPid_Kp:
           break;
					 default:;
         }
       } /*if (prx_ptr->pck.frame.CrcRsd == StdSci_CrcRsdGnrtr(prx_ptr->pck))*/
		 }

//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0x80), main_machine_state); //q?
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0x81), control_machine_state); //q?
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0x90), motor_ptr->app_status);
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0x91), motor_ptr->Ibus_ADC);
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0x98), motor_ptr->temp_pwm_duty);

//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0xB0), hall_ptr->hall_value);

//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0xC0), feedback_CodeEfficiency_SMC);
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0xC1), feedback_CodeEfficiency_SMM);

     SET_STDSCI_PACK_TX_OVERRUN(&(btx_ptr->pck_0x90), motor_ptr->app_status);

//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0xF0), feedback_Test0);
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0xF1), feedback_Test1);
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0xF2), feedback_Test2);
//     overrun_tx |= SET_STDSCI_PACK_TX(&(btx_ptr->pck_0xF3), feedback_Test3);

     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0x80), main_machine_state,999); //1s interval
     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0x81), control_machine_state,999); //1s interval
     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0x82), hall_ptr->observer_state,999); //1s interval

     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0x90), motor_ptr->app_status,999); //1s interval
     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0x91), motor_ptr->Ibus_ADC,999); //1s interval
//     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0x98), motor_ptr->temp_pwm_duty,999); //1s interval

     SET_STDSCI_PACK_32_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xA0), &(btx_ptr->pck_0xA1), hall_ptr->dt_commutate_m_average, 999); //1s
     SET_STDSCI_PACK_32_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xA2), &(btx_ptr->pck_0xA3), hall_ptr->dt_commutate_p, 999); //1s
//     SET_STDSCI_PACK_32_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xA4), &(btx_ptr->pck_0xA5), hall_ptr->e_dt_commutate, 999); //1s
//     SET_STDSCI_PACK_32_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xA4), &(btx_ptr->pck_0xA5), hall_ptr->dt_base_commutate, 999);

     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xB0), hall_ptr->hall_value, 999); //1s interval
//     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xB1), hall_ptr->num_pwm_60d_m, 999); //1s interval
//     SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xB2), hall_ptr->num_pwm_60d_p, 999); //1s interval

     if(main_machine_state == STATE_MAIN_STOP_STANDBY)
     {
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD0), ww_ptr->num_pwm_60d_m_wx0, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD1), ww_ptr->num_pwm_60d_p_wx0, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD2), ww_ptr->num_pwm_60d_m_wx1, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD3), ww_ptr->num_pwm_60d_p_wx1, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD4), ww_ptr->num_pwm_60d_m_wx2, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD5), ww_ptr->num_pwm_60d_p_wx2, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD6), ww_ptr->num_pwm_60d_m_wx3, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD7), ww_ptr->num_pwm_60d_p_wx3, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD8), ww_ptr->num_pwm_60d_m_wx4, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xD9), ww_ptr->num_pwm_60d_p_wx4, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xDA), ww_ptr->num_pwm_60d_m_wx5, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xDB), ww_ptr->num_pwm_60d_p_wx5, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xDC), ww_ptr->num_pwm_60d_m_wx6, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xDD), ww_ptr->num_pwm_60d_p_wx6, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xDE), ww_ptr->num_pwm_60d_m_wx7, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xDF), ww_ptr->num_pwm_60d_p_wx7, 1999);

       SET_STDSCI_PACK_32_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xE0), &(btx_ptr->pck_0xE1), feedback_Test_0_Long, 1999); //2s
//     SET_STDSCI_PACK_32_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xE2), &(btx_ptr->pck_0xE3), feedback_Test1_32, 1999); //2s

       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xF0), feedback_Test_0, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xF1), feedback_Test_1, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xF2), feedback_Test_2, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xF3), feedback_Test_3, 1999);
       SET_STDSCI_PACK_TX_OVERRUN_INTERVAL(&(btx_ptr->pck_0xF4), feedback_Test_4, 1999);
     }

     if(btx_ptr->flag_TC == False) StdSci_Send_in_ISR(USART1);

     if(overrun_tx) motor_ptr->app_status |= status_TX_overrun;
     else motor_ptr->app_status &= ~status_TX_overrun;

//   feedback_CodeEfficiency_SMM = ?;
   }

//
// 2. 
// ...........................................................
// @brief  This function handles SysTick Handler.
// @param  None
// @retval None/
//
// u16 Get_duty(void){return duty;}
//	 u16 Get_instr(void){return instr;}
	 
// no more.
// -----------------------------------------------------------

