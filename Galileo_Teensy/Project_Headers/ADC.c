/*
 * ADC.c
 *
 *  Created on: Feb 17, 2016
 *      Author: Julio Fajardo
 */

#include "IO_Map.h"

void ADC_Init(void){
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	ADC0_CFG1 = ADC_CFG1_MODE(1) + ADC_CFG1_ADLSMP_MASK + ADC_CFG1_ADICLK(0);  	//Clock/4 - short sample - 12 bits - Bus clk/2
	ADC0_CFG2 = ADC_CFG2_MUXSEL_MASK + ADC_CFG2_ADLSTS(2); 											//High Speed, ADCB - Clk enable
	ADC0_SC2 = 0x00;																															//Software trigger
	ADC0_SC3 = ADC_SC3_ADCO_MASK + ADC_SC3_AVGE_MASK + ADC_SC3_AVGS(2);					//Continuos conversions - Hardware Average - 16 samples
	ADC0_CV1 = 0x00;																															//Compare value not used
	ADC0_CV2 = 0x00;																															//Compare value not used
	ADC0_OFS = 0x04;																															//Offset value
}



