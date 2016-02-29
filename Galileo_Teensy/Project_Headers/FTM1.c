/*
 * FTM1.c
 *
 *  Created on: Feb 17, 2016
 *      Author: Julio Fajardo
 */

#include "IO_Map.h"

void FTM1_Init(void){
	SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
	PORTA_PCR12 = PORT_PCR_MUX(0x03);
	PORTA_PCR13 = PORT_PCR_MUX(0x03);
	FTM1_MODE |= FTM_MODE_WPDIS_MASK; 									//Write protection disable   
	FTM1_C0SC = FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK;					//C0 Edge Align PWM High TRue
	FTM1_C1SC = FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK;					//C1 Edge Align PWM High TRue
	FTM1_C0V = FTM_CnV_VAL(0x0546);										//C0V = 1350 - 2.4ms
	FTM1_C1V = FTM_CnV_VAL(0x0152);										//C1V =  338 - 0.6ms
	FTM1_MOD = FTM_MOD_MOD(0x2BF2);										//0x2BF2 = 11250, 11250*(1/(72MHz/2/64)) = 20 ms
	FTM1_SC = FTM_SC_CLKS(0x01) + FTM_SC_PS(0x06);						//System Clock/64 									
}
