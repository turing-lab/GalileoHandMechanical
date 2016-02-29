/*
 * Methods.c
 *
 *  Created on: Feb 17, 2016
 *      Author: Julio Fajardo
 */

#include "IO_Map.h"

static const uint8_t channel2sc1a[] = {
	5, 14, 8, 9, 13, 12, 6, 7, 15, 4,
	0, 19, 3, 19+128, 26, 18+128, 23,
	5+192, 5+128, 4+128, 6+128, 7+128, 4+192
};

void LED_On(void){
	GPIOC_PSOR |= (1UL<<5);
}

void LED_Off(void){
	GPIOC_PCOR |= (1UL<<5);
}

void LED_Toggle(void){
	GPIOC_PTOR |= (1UL<<5);
}

uint16_t ADC0_Read(unsigned int index){
	uint8_t channel = channel2sc1a[index];
	ADC0_SC1A = ADC_SC1_ADCH(channel);   
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));
	return ADC0_RA;
}

void UART0_send(uint8_t dato){
	while (!((UART0_S1)&(UART_S1_TDRE_MASK)));  //ejecuta lo demas hasta que el buffer este libre
	UART0_D = dato;
}

void UART0_putString(uint8_t *mystring){
	while(*mystring){
		UART0_send(*mystring);
		mystring++;
	}
}

