/* ###################################################################
**     Filename    : Events.c
**     Project     : Galileo_Teensy
**     Processor   : MK20DX256VLL7
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-17, 14:12, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

extern void LED_On(void);
extern void LED_Off(void);
extern void LED_Toggle(void);
extern uint16_t ADC_Read(unsigned int channel);
extern void UART_send(uint8_t dato);
extern void UART_putString(uint8_t *mystring);

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX256LL7]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

void PORTC_IRQHandler(void){
	if(PORTC_PCR6&PORT_PCR_ISF_MASK){
		PORTC_PCR6 |= (PORT_PCR_ISF_MASK);
		//LED_Toggle();
	}
}

void PIT0_IRQHandler(void){
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;
	LED_Toggle();
}

void UART0_RX_TX_IRQHandler(void){
	(void) UART0_S1;
	uint8_t data = UART0_D;
	UART0_D = data;
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
