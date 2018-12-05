// -----------------------------------------------------------
// FILE: VOID.c
//
// Description: this is a template for newly created .c files
//
// -----------------------------------------------------------
// Release Date: year-month-day;
// Authour: Name;
// -----------------------------------------------------------
//
// 1st.macros
// -----------------------------------------------------------
// # include "headfilename.h"

//
// 2nd. variables
// -----------------------------------------------------------

//
// 3rd.function prototypes
// -----------------------------------------------------------

// 2.electric machine servo function
//   .........................................................
//   this is the top-level electric machine servo program,
//   main founctionalities of which are:
//
//   a.determine the state of the Servo Finite State Machine
//     (FSM) according to the last state, logic input, and
//     other denymic parameters;
//   b.calculate the PWM duty using PID functions and
//     configure the ePWMx peripheral propperly according to
//     different Servo FSM state;
//   c.TBD
//  
//   a proper ePWM interrupt server pointer should be pointed
//   here;
//  
//   *state ------- pointer to the machine servo state
//   instr -------- machine working instruction
//   *pSSP -------- pointer to the static parameter struct
//   *pSDP -------- pointer to the dynamic parameter struct
//   *fbPHYS ------ pointer to the physical feedback struct
//   wTG ---------- machine target speed

     void ESC_StateMachine(enum InstrHost instr,
                volatile struct EPWM_REGS *pntr_EPWMA,
                volatile struct EPWM_REGS *pntr_EPWMB,
                volatile struct EPWM_REGS *pntr_EPWMC,
                /*Float32 dtTg, Uint16 vrPhs,*/
                struct SERVOPRM_STATIC_MNBRS *pSSP,
                struct SERVOPRM_DYNAMIC_MNBRS *pSDP,
                struct PHYSFDBCK_MNBRS *fbPHYS )
     {
//   A.variables
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//     the machine rotor speed feed-back
//     Float32 wFB = 0;
//
     # if 10 // 20180530
//     the machine rotor axis D electric position (rad)
       Float32 pstnDe = 0;
//     
//     the pseudo machine rotor axis D phase
//     enum RtrPhs phsD_ps = PHS_ZRO;
       struct RotorPhaseChin_MNBRS phs0_ps = phs_I;
//     Uint16 nPwmPId3;
//     Uint16 nPwmPId6;
//
//     the machine rotor axis D phase in the current chop
//       enum RtrPhs phsP0 = pSDP->phP1;
//
//     the machine rotor axis D phase in the next chop
//       enum RtrPhs phsP1;
//     
//     the speed PID loop output
//     Float32 oSL;
//     
//     pseudo machine rotor axis D electric position (rad)
       Float32 pstnDe_ps = pSDP->pstPsDe;
//     
//     pseudo machine rotation speed (r/min)
       Float32 wFB_ps = pSDP->wPsSpdFb;
       
//     machine start scenario duty
       Float32 dutyStrt = 0;
     # endif /*"# if 0 // 20180530"*/
//
//     Uint16 eVoid1 = 1;
//     Uint16 eVoid2 = 2;
//     Uint16 eVoid3 = 3;
//
//     1/6 back-EMF period (s)
//     Float32 tPhs = pSDP->tBEMFd6;
//     Uint16 tPhsU16 = (Uint16)tPhs;
//
//     number of chops in 1/6 period
//     Uint16 nPwmPhs = pSDP->nPwmBEMFd6;
//
//     flag if crossing point detected
//     Uint16 fCP = 0; //pSDP->fCrssPnt;
//     Uint16 f_CrssPnt;
//     enum Bool fCP = False; //pSDP->fCrssPnt;
//     enum Bool fAlt = False;
//
       /*
       enum Bool evA0 = fbPHYS->evA;
       enum Bool evB0 = fbPHYS->evB;
       enum Bool evC0 = fbPHYS->evC;

       enum Bool evAn1 = pSDP->evA_n1;
       enum Bool evBn1 = pSDP->evB_n1;
       enum Bool evCn1 = pSDP->evC_n1;

       enum Bool evAn2 = pSDP->evA_n2;
       enum Bool evBn2 = pSDP->evB_n2;
       enum Bool evCn3 = pSDP->evC_n2;
       */
//
//     Uint16 fCPx = 0x0000;
//     Uint16 meanNP1Phs;
//     Uint16 optmNP1Phs;
//     Uint16 d0,d1,d2,d3,d4,d5,d6,d7;
//
       Uint16 wFbPrnt;
//
//   B.alter the Servo FSM state propperly:
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       switch (pSDP->sFsmN1)
       {
//     <SERVO_DFLT>. (default)
//     source -- START, TRANS, STEER, FAULT, default
//     sink ---- STOP
         case SERVO_DFLT:
              pSDP->sFSM = SERVO_STOP;
              break;
//
//     <SERVO_STOP>. machine stop state
//     source -- DFLT, STOP
//     sink ---- STOP, START
         case SERVO_STOP:
//            if(instr == MCH_RUN) pSDP->sFSM = SERVO_START;
              if(instr == MCH_RUN) pSDP->sFSM = SERVO_DCDC;
//            if(instr == MCH_RUN) pSDP->sFSM = SERVO_LOCAT;
              break;
//
//     <SERVO_LOCAT>. machine rotor locate
//     source -- NAN
//     sink ---- DFLT, LOCAT
         case SERVO_LOCAT:
              if(instr == MCH_STOP) pSDP->sFSM = SERVO_DFLT;
              break;
//
//     <SERVO_SYNCH>. machine external synchronous rotate
//     source -- NAN
//     sink ---- DFLT, SYNCH
         case SERVO_SYNCH:
              if(instr == MCH_STOP) pSDP->sFSM = SERVO_DFLT;
              break;
//     
//     <SERVO_START>. machine start state
//     source -- STOP, START
//     sink ---- DFLT, START, TRANS, FAULT
         case SERVO_START:
              if(instr == MCH_STOP) pSDP->sFSM = SERVO_DFLT;
              if(0/*wFB_ps > 0.3E3*/) pSDP->sFSM = SERVO_TRANS;
              break;
//
//     <SERVO_TRANS>.
//     source -- START, TRANS
//     sink ---- DFLT, TRANS, STEER, FAULT
         case SERVO_TRANS:
              if(instr == MCH_STOP) pSDP->sFSM = SERVO_DFLT;
              break;
//
//     <SERVO_STEER>. machine steer state
//     source -- TRANS, STEER
//     sink ---- DFLT, STEER, FAULT
         case SERVO_STEER:
              if(instr == MCH_STOP) pSDP->sFSM = SERVO_DFLT;
              break;
//
//     <SERVO_DCDC>. DCDC test
//     source -- STOP, DCDC
//     sink ---- DFLT, DCDC
         case SERVO_DCDC:
              if(instr == MCH_STOP) pSDP->sFSM = SERVO_DFLT;
              break;
//
//     <SERVO_FAULT>. machine fault state
//     source -- START, TRANS, STEER, FAULT
//     sink ---- DFLT, FAULT
         case SERVO_FAULT:
              if(instr == MCH_STOP) pSDP->sFSM = SERVO_DFLT;
              break;
//     
//     < >.
//       source -- unknown
//       sink ---- DFLT
         default:
              pSDP->sFSM = SERVO_DFLT;
              break;
       }       
//
//   C.determine what operations to execute according to
//   the Servo FSM state correspondingly:
//     . . . . . . . . . . . . . . . . . . . . . . . . . . . .
       switch (pSDP->sFSM)
       {
//     <SERVO_DFLT>.
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
         case SERVO_DFLT:
         {
           DINT;
//
//         stop chopping
           pntr_EPWMA->AQCSFRC.all = BoffAoff;
           pntr_EPWMB->AQCSFRC.all = BoffAoff;
           pntr_EPWMC->AQCSFRC.all = BoffAoff;
//         pntr_EPWMC->AQCSFRC.all = BonAoff;
//
//         reset phase detecting state
           pSDP->ph_n1 = PHS_ZRO;
           pSDP->ph_0 = PHS_ZRO;
           pSDP->ph_p1 = PHS_ZRO;
//
//         reset rotor phase
           pSDP->phsN1 = phs_Z;
           pSDP->phs0  = phs_Z;
           pSDP->phs1  = phs_Z;

//         pSDP->wPsSpdFb = 36; // reset pseudo totation speed
           pSDP->wPsSpdFb = ThDtStart*pSSP->cWfb2Duty;
//
           pSDP->pstPsDe = 0;  // clear pseudo rotor position

           pSDP->phs0 = phs_I; // reset rotor phase
           pSDP->wSpdFb = 0;  // reset feed-back speed
//
           pSDP->flts &= (Uint16)FLTID_NAN; // clear fault flags

           pSDP->wSpdFb = 0;  // reset feed-back speed to 0

           pSDP->cntr_SteerChops = 0; //test
//
           EINT;
           break;
         }
//     <SERVO_STOP>. machine stop state (default)
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
//       stop the machine by forcing PWMs low;
         case SERVO_STOP:
         {
           //pSDP->phDly30d = dtct_PhsFree( pSDP,fbPHYS );

//           fbPHYS->evN1 = 0;
/*
           EALLOW;
             pntr_EPWMA->TZCLR.bit.OST = 1;
             pntr_EPWMB->TZCLR.bit.OST = 1;
             pntr_EPWMC->TZCLR.bit.OST = 1;
//
             pntr_EPWMA->TZCLR.bit.INT = 1;
             pntr_EPWMB->TZCLR.bit.INT = 1;
             pntr_EPWMC->TZCLR.bit.INT = 1;
           EDIS;
*/
           asm("  NOP");
           break;
         }
//     <SERVO_LOCAT>.
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
         case SERVO_LOCAT:
         {
           switch (pSDP->pVrPhs)
           {
             case 5: pSDP->phs_locat = phs_I;
                     break;
             case 4: pSDP->phs_locat = phs_II;
                     break;
             case 6: pSDP->phs_locat = phs_III;
                     break;
             case 2: pSDP->phs_locat = phs_IV;
                     break;
             case 3: pSDP->phs_locat = phs_V;
                     break;
             case 1: pSDP->phs_locat = phs_VI;
                     break;
             default: pSDP->phs_locat = phs_Z;
                     break;
           }
//
           chopper( 100,                                     \
                    pSDP->phs_locat,                         \
                    pSDP->phs_locat,                         \
                    pSDP,                                    \
                    0,                                       \
                    pntr_EPWMA,                              \
                    pntr_EPWMB,                              \
                    pntr_EPWMC  );
           break;
         }
//     <SERVO_SYNCH>.
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
         case SERVO_SYNCH:
         {
           break;
         }
//     
//     <SERVO_START>. machine start state
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
//       start up the machine using virtual PWM duty and
//       D-axis positon
         case SERVO_START:
         {
         # if 10 // 20180530
//       1st> calculate the pseudo speed (wFB_ps, r/min)
//            alternate state after the pseudo speed reaches
//            300rpm
           if (wFB_ps < pSSP->thPsWfbTrans/*0.5E3*/ ) wFB_ps += pSSP->incPsWfb;
           else
           {
           # if 1
             pSDP->sFSM = SERVO_TRANS;
             set_fltr_8(&(pSDP->frNPhs), pSSP->cNPwm2Wfb/wFB_ps/*8.333E3/wFB_ps*/);
//
//           pSDP->dDtTg = dutyStrt;
//           pSDP->dDtOpt = 340; //10kHz
//           pSDP->dDtOpt = 240; //20kHz
             pSDP->dDtOpt = ThDtTrans;
             pSDP->sAlt = True;
//
             pSDP->nPwm1Phs = pSDP->frNPhs.mean;
             pSDP->cntrPwm  = 0;
             pSDP->sCP      = PHS_ZRO;
//             pSDP->sAlt     = False;
             pSDP->ph_n1    = PHS_ZRO;
             pSDP->ph_0     = PHS_ZRO;
             pSDP->ph_p1    = PHS_ZRO;
//
             pSDP->mRngMap.rData_1.ofRd = 0;
             pSDP->mRngMap.rData_2.ofRd = 0;
             pSDP->mRngMap.rData_3.ofRd = 0;
             pSDP->mRngMap.rData_4.ofRd = 0;
             pSDP->mRngMap.rData_5.ofRd = 0;
             pSDP->mRngMap.rData_6.ofRd = 0;
             pSDP->mRngMap.rData_7.ofRd = 0;
             pSDP->mRngMap.rData_8.ofRd = 0;
             pSDP->mRngMap.rData_9.ofRd = 0;
             pSDP->mRngMap.rData_A.ofRd = 0;
//
             pSDP->mRngMap.rData_1.ofWr = 1;
             pSDP->mRngMap.rData_2.ofWr = 1;
             pSDP->mRngMap.rData_3.ofWr = 1;
             pSDP->mRngMap.rData_4.ofWr = 1;
             pSDP->mRngMap.rData_5.ofWr = 1;
             pSDP->mRngMap.rData_6.ofWr = 1;
             pSDP->mRngMap.rData_7.ofWr = 1;
             pSDP->mRngMap.rData_8.ofWr = 1;
             pSDP->mRngMap.rData_9.ofWr = 1;
             pSDP->mRngMap.rData_A.ofWr = 1;
           # endif
//
//         delete lines below
           # if 0
             pSDP->cWr = 0;

             /*
             pSDP->fklNPhs.opt_X  = 8.333E3/wFB_ps;
             pSDP->fklNPhs.opt_P  = 1/(pSDP->fklNPhs.opt_X);
             pSDP->fklNPhs.opt_P /= (pSDP->fklNPhs.opt_X);
             */
           # endif
           }
//
           pSDP->wPsSpdFb = wFB_ps;  // renew pseudo speed
           pSDP->wSpdFb   = wFB_ps;  // use pseudo speed as feed-back speed
//
//       2nd> calculate duty for the next chop
           dutyStrt = wFB_ps*pSSP->cWfb2Duty;
//         dutyStrt = wFB_ps*0.7867+150;  // 10kHz
//         dutyStrt = wFB_ps*0.3820+50;   // 20kHz
//         dutyStrt = wFB_ps*0.3320+75;   // 20kHz
//         dutyStrt = wFB_ps*0.4700+100;  // 20kHz
//         dutyStrt = wFB_ps*0.3033+150;  // 20kHz
//
//       3rd> calculate pseudo D-axis position (pstnDe_ps,
//         rad)
           pstnDe_ps += wFB_ps*pSSP->cWfb2DltaTheta;
//
           if ((pstnDe_ps> PI*2)||(PI*2==pstnDe_ps))         \
              pstnDe_ps -= 2*PI;
//
           pSDP->pstPsDe = pstnDe_ps;
//
//       4th> calculate pseudo D-axis phase
//         phsD_ps = calcu_PseudoPhase(pstnDe_ps, pSSP->cBD);
           phs0_ps = calcu_PseudoPhase(pstnDe_ps, pSSP->cBD);

           pSDP->phsN1 = pSDP->phs0;
           pSDP->phs0 = phs0_ps;

//         pSDP->phsN1 = *(phs0_ps.pN1);
//         pSDP->phs0 = phs0_ps; // use pseudo phase as rotor phase
//
//       5th> determine the chopping patern for the next chop
           chopper( dutyStrt,pSDP->phs0,pSDP->phsN1,pSDP,pstnDe,                 \
                    pntr_EPWMA,pntr_EPWMB,pntr_EPWMC);

//       b).calculate the machine speed
//         wFB = calcu_Speed();
//         pSDP->wSpdFb = wFB;
//
//       c).determine the rotor position
//         pstnDe = calcu_Theta();
//         pstnDe = pstnDe_ps;
//         phsD = calcu_PseudoPhase(pstnDe, pSSP->cBD);
//     
//       d).calculate the speed loop output
//         oSL = dtTg;
//         oSL = wPID(wFB, wTG);
//     
//       e).calculate the current loop output
//
//       6th> sample physical feed-backs
           RngWriteOne16 ( &(pSDP->mRngMap.rEvA), &(fbPHYS->evA) );
           RngWriteOne16 ( &(pSDP->mRngMap.rEvB), &(fbPHYS->evB) );
           RngWriteOne16 ( &(pSDP->mRngMap.rEvC), &(fbPHYS->evC) );
//
         # if 0
           RngWriteOne16 ( &(fbPHYS->rEvA), &(fbPHYS->evA) );
           RngWriteOne16 ( &(fbPHYS->rEvB), &(fbPHYS->evB) );
           RngWriteOne16 ( &(fbPHYS->rEvC), &(fbPHYS->evC) );
         # endif
//
//       check out if hardware over current occoured
           if( (pntr_EPWMA->TZFLG.bit.OST) |      \
               (pntr_EPWMB->TZFLG.bit.OST) |      \
               (pntr_EPWMC->TZFLG.bit.OST)   )
           {
             pSDP->sFSM = SERVO_FAULT;
             pSDP->flts |= (Uint16)FLTID_OCH;
           }

           if(pSDP->sFSM != SERVO_START) { pSDP->phs0  = phs_Z;
                                           pSDP->phsN1 = phs_Z;
                                           pSDP->phs1  = phs_Z; }
//
         # endif /*"# if 0 // 20180530"*/
           break;
         }
//
//     <SERVO_TRANS>.
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
         case SERVO_TRANS:
         {
         # if 10 // 20180530
//         stop chopping
           pntr_EPWMA->AQCSFRC.all = BoffAoff;
           pntr_EPWMB->AQCSFRC.all = BoffAoff;
           pntr_EPWMC->AQCSFRC.all = BoffAoff;
//
//         detect crossing events
           dtct_CrssPnt_Trans(pSDP, fbPHYS);
//
//         counting and filtering the number of chopps in a
//         phase
           if(pSDP->fCP_x)
           {
             pSDP->nPwm1Phs = pSDP->cntrPwm;
             pSDP->cntrPwm = 0;

//           fltr_kal (&(pSDP->fklNPhs),(Float32)pSDP->nPwm1Phs);
             fltr_8(&(pSDP->frNPhs),(Float32)(pSDP->nPwm1Phs));
           }
           else
           { pSDP->cntrPwm ++;}
//
//         renew feed-back speed
           pSDP->wSpdFb = (pSSP->cNPwm2Wfb)/(pSDP->frNPhs.mean);
//
//         determine what the current phase is
           dtct_Phs (pSDP);
//
//         alter state when at least two phases have been    \
//         detected
           if (pSDP->phsN1.p0 != PHS_ZRO)
           {
             pSDP->sFSM = SERVO_STEER;
//           pSDP->dDtTg *= (0/10);
           }
//
           if((pSDP->mRngMap.rData_1.ofRd) !=(pSDP->mRngMap.rData_1.ofWr))
           {
//
//           temp = (Uint16)pSDP->frNPhs.mean;
//
             RngWriteOne16 ( &(pSDP->mRngMap.rData_1), &(fbPHYS->evA) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_2), &(fbPHYS->evB) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_3), &(fbPHYS->evC) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_4), &(pSDP->cntrPwm) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_5), &(pSDP->phs0.p0) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_6), &(pSDP->sFSM) );
//
           # if 0
             RngWriteOne16 ( &(fbPHYS->rData_1), &(fbPHYS->evA) );
             RngWriteOne16 ( &(fbPHYS->rData_2), &(fbPHYS->evB) );
             RngWriteOne16 ( &(fbPHYS->rData_3), &(fbPHYS->evC) );
             RngWriteOne16 ( &(fbPHYS->rData_4), &(pSDP->ph_0) );
           # endif
           }
         # endif /*"# if 0 // 20180530"*/
           break;
         }
//
//     <SERVO_STEER>.machine steer state
         case SERVO_STEER:
         {
         # if 10 // 20180530"*/
//
           if(pSDP->phsN1.p0 != pSDP->phs0.p0) pSDP->cPhsAltDly = 0;
           else pSDP->cPhsAltDly ++ ;
//
//         detect crossing events
           dtct_CrssPnt_Steer(pSDP, fbPHYS);
//
//         counting and filtering the number of chopps in a
//         phase
           if(pSDP->fCP_x)
           {
             pSDP->nPwm1Phs = pSDP->cntrPwm;
             pSDP->cntrPwm = 0;

//           fltr_kal (&(pSDP->fklNPhs),(Float32)pSDP->nPwm1Phs);
             fltr_8(&(pSDP->frNPhs),(Float32)(pSDP->nPwm1Phs));
           }
           else
           { pSDP->cntrPwm ++;}
//
//         renew feed-back speed
           pSDP->wSpdFb = (pSSP->cNPwm2Wfb)/(pSDP->frNPhs.mean);
           wFbPrnt = (Uint16)pSDP->frNPhs.mean;
//
//         determine what the current phase is
           dtct_Phs (pSDP);
//
           if( pSDP->dDtOpt < pSDP->dDtTg ) pSDP->dDtOpt ++;
           if( pSDP->dDtOpt > pSDP->dDtTg ) pSDP->dDtOpt --;
//
//         determine the chopping patern for the next chop
           chopper( pSDP->dDtOpt,pSDP->phs0,pSDP->phsN1,pSDP,pstnDe,                 \
                    pntr_EPWMA,pntr_EPWMB,pntr_EPWMC);
//
//         check out if hardware over current occoured
           if( (pntr_EPWMA->TZFLG.bit.OST) |
               (pntr_EPWMB->TZFLG.bit.OST) |
               (pntr_EPWMC->TZFLG.bit.OST)   )
           {
             pSDP->sFSM = SERVO_FAULT;
             pSDP->flts |= (Uint16)FLTID_OCH;
           }
//
//         temp = (Uint16)pSDP->frNPhs.mean;
//
           if(1)//(pSDP->mRngMap.rData_1.ofRd) !=(pSDP->mRngMap.rData_1.ofWr))
           {
             RngWriteOne16 ( &(pSDP->mRngMap.rData_1), &(fbPHYS->evA) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_2), &(fbPHYS->evB) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_3), &(fbPHYS->evC) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_4), &(pSDP->sAlt) );
//           RngWriteOne16 ( &(pSDP->mRngMap.rData_4), &(pSDP->cntrPwm) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_5), &(pSDP->phs0.p0) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_6), &(pSDP->fCP_x) );
//           RngWriteOne16 ( &(pSDP->mRngMap.rData_6), &(pSDP->sFSM) );
             RngWriteOne16 ( &(pSDP->mRngMap.rData_7), &(wFbPrnt) );
//           RngWriteOne16 ( &(pSDP->mRngMap.rData_5), &(pSDP->cntr_SteerChops) );
//
           # if 0
             RngWriteOne16 ( &(fbPHYS->rData_1), &(fbPHYS->evA) );
             RngWriteOne16 ( &(fbPHYS->rData_2), &(fbPHYS->evB) );
             RngWriteOne16 ( &(fbPHYS->rData_3), &(fbPHYS->evC) );
             RngWriteOne16 ( &(fbPHYS->rData_4), &(pSDP->ph_0) );
           # endif
           }
//
//         pSDP->cntr_SteerChops ++;
//         if(((pSDP->cntr_SteerChops)++)>100) pSDP->sFSM = SERVO_FAULT;
         # endif /*"# if 0 // 20180530"*/
           break;
         }
//     
//     <SERVO_DCDC>. only for DCDC test
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
         case SERVO_DCDC:
         {
//         pntr_EPWMA->AQCSFRC.all = BchopAchop;
//         pntr_EPWMB->AQCSFRC.all = BchopAchop;
//         pntr_EPWMC->AQCSFRC.all = BoffAchop;
           pntr_EPWMC->AQCSFRC.all = BchopAchop;

           pntr_EPWMA->CMPA.half.CMPA = (Uint16)pSDP->dDtTg;
           pntr_EPWMB->CMPA.half.CMPA = (Uint16)pSDP->dDtTg;
           pntr_EPWMC->CMPA.half.CMPA = (Uint16)pSDP->dDtTg;

           pntr_EPWMC->CMPB = 3550;//(Uint16)pSDP->dDtTg;

           break;
         }
//
//     <SERVO_FAULT>. machine fault state
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
//       stop the machine by clearing the PWM duty;
         case SERVO_FAULT:
         {
           pntr_EPWMA->AQCSFRC.all = BoffAoff;
           pntr_EPWMB->AQCSFRC.all = BoffAoff;
           pntr_EPWMC->AQCSFRC.all = BoffAoff;

           EALLOW;
             pntr_EPWMA->TZCLR.bit.OST = 1;
             pntr_EPWMB->TZCLR.bit.OST = 1;
             pntr_EPWMC->TZCLR.bit.OST = 1;
           EDIS;

           break;
         }
//     
//     < >.
//       .   .   .   .   .   .   .   .   .   .   .   .   .   .
//       stop the machine by clearing the PWM duty;
         default:
         {
           pntr_EPWMA->AQCSFRC.all = BoffAoff;
           pntr_EPWMB->AQCSFRC.all = BoffAoff;
           pntr_EPWMC->AQCSFRC.all = BoffAoff;
           break;
         }
       }
//
//     save current FSM state
       pSDP->sFsmN1 = pSDP->sFSM;
//
       asm(" NOP");
     } 

//
// 4th.funcions
// -----------------------------------------------------------

// no more.
// -----------------------------------------------------------

