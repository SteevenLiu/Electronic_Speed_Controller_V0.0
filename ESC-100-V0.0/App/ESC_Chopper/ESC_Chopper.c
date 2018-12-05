// -----------------------------------------------------------
// FILE: ESC_Chopper.c
//
// Description: this is a template for newly created .c files
//
// -----------------------------------------------------------
// Release Date: year-month-day;
// Authour: Name;
// -----------------------------------------------------------

// 1st.macros
// -----------------------------------------------------------
   # include "ESC_Chopper.h"

//
// 2nd. variables
// -----------------------------------------------------------

//
// 3rd.function prototypes
// -----------------------------------------------------------

//
// 4th.funcions
// -----------------------------------------------------------
// 1.Chopper phase I
// ...........................................................
   /**
   @brief Configure phase I PWM outputs.
   @param None.
   @retval None.
   */
   void Chopper_Phase_I(void)
   {
		 U_Forced_PWM_MODE1;
     UH_Turn_Off;
     UL_Turn_Off;
   
     V_Forced_PWM_MODE1;
     VH_Turn_Off;
     VL_Turn_On;
 
     W_Forced_Active;
     WH_Turn_On;
     WL_Turn_Off;
   }

// 2.Chopper phase II
// ...........................................................
   /**
   @brief Configure phase II PWM outputs.
   @param None.
   @retval None.	 
   */
   void Chopper_Phase_II(void)
   {
     U_Forced_PWM_MODE1;
     UH_Turn_On;
     UL_Turn_Off;

     V_Forced_Active;
     VH_Turn_Off;
     VL_Turn_On;

     W_Forced_PWM_MODE1;
     WH_Turn_Off;
     WL_Turn_Off;
   }

// 3.Chopper phase III
// ...........................................................
   /**
   @brief Configure phase III PWM outputs.
   @param None.
   @retval None.	
   */
   void Chopper_Phase_III(void)
   {
     U_Forced_Active;
     UH_Turn_On;
     UL_Turn_Off;

		 V_Forced_PWM_MODE1;
     VH_Turn_Off;
     VL_Turn_Off;

     W_Forced_PWM_MODE1;
     WH_Turn_Off;
     WL_Turn_On;
   }

// 4.Chopper phase IV
// ...........................................................
   /**
   @brief Configure phase IV PWM outputs.
   @param None.
   @retval None.	
   */
   void Chopper_Phase_IV(void)
   {
     U_Forced_PWM_MODE1;
     UH_Turn_Off;
     UL_Turn_Off;

     V_Forced_PWM_MODE1;
     VH_Turn_On;
     VL_Turn_Off;

     W_Forced_Active;
     WH_Turn_Off;
     WL_Turn_On;
   }	 

// 5.Chopper phase V
// ...........................................................
   /**
   @brief Configure phase V PWM outputs.
   @param None.
   @retval None.	
   */
   void Chopper_Phase_V(void)
   {
     U_Forced_PWM_MODE1;
     UH_Turn_Off;
     UL_Turn_On;

     V_Forced_Active;
     VH_Turn_On;
     VL_Turn_Off;

		 W_Forced_PWM_MODE1;
     WH_Turn_Off;
     WL_Turn_Off;
   }

// 6.Chopper phase VI
// ...........................................................
   /**
   @brief Configure phase VI PWM outputs.
   @param None.
   @retval None.	
   */
   void Chopper_Phase_VI(void)
   {
     U_Forced_Active;
     UH_Turn_Off;
     UL_Turn_On;

		 V_Forced_PWM_MODE1;
     VH_Turn_Off;
     VL_Turn_Off;

     W_Forced_PWM_MODE1;
     WH_Turn_On;
     WL_Turn_Off;
   }

// 7.Chopper phase ZRO
// ...........................................................
   /**
   @brief Configure phase ZRO PWM outputs.
   @param None.
   @retval None.	
   */
   void Chopper_Phase_ZRO(void)
   {
     U_Forced_InActive;
     UH_Turn_Off;
     UL_Turn_Off;
		 
     V_Forced_InActive;
     VH_Turn_Off;
     VL_Turn_Off;
		 
     W_Forced_InActive;
     WH_Turn_Off;
     WL_Turn_Off;
   }
	 
// no more.
// -----------------------------------------------------------

