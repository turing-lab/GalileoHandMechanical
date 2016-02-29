/* ###################################################################
**     Filename    : main.c
**     Project     : Galileo_Teensy
**     Processor   : MK20DX256VLL7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-17, 14:12, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains application code to control the Galileo Hand Myoelectric Prosthetic.
**         Alan Turing Research Laboratory
**         FISICC (School of Electrical and Computer Engineering)
**         Universidad Galileo
**         Guatemala City, Guatemala
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PTC.h"
#include "PIT.h"
#include "UART0.h"
#include "FTM0.h"
#include "FTM1.h"
#include "ADC.h"
#include "Methods.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "arm_math.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

uint32_t i = 0;
uint32_t count = 0;
uint32_t value = 0;
float32_t res = 0.0f;


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  ADC_Init();
  FTM0_Init();
  FTM1_Init();
  /*** End of Processor Expert internal initialization.                    ***/
  LED_On();
  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;){
	  value = ADC0_Read(0);
	  arm_sqrt_f32((float32_t)value,&res);
	  //if(value>2048) LED_Off();
	  //else LED_On();
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
