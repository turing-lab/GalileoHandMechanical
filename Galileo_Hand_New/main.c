#define ARM_MATH_CM4

#include "MK20D7.h"                     // Device header
#include <stdlib.h>
#include "drivers.h"
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIZE 	50

uint32_t count = 0;
uint32_t mcount = 600;
uint8_t action = 0;
uint8_t state = 0;
uint8_t ticks = 0;
uint8_t mstate = 0;

q15_t IM2_mean = 0;
q15_t IM2_Buffer[SIZE];

int main (void) {
	Switch_Init();
	LED_Init(); 
	Output_Init();
	ADC0_Init();
	UART0_Init();
	SysTick_Config(SystemCoreClock/1000);
	//FTM0_Init();
	
	for(int i=0;i<SIZE;i++) IM2_Buffer[i]=0;
	
	while(1){
		/*
		arm_mean_q15(IM2_Buffer,SIZE,&IM2_mean);
		switch(mstate){
			case 0:{
				if(IM2_mean>160) mstate = 1;
		  	PTD->PCOR |= (1<<3);														//M2+
				PTC->PSOR |= (1<<3);														//M2-
			} break;
			case 1:{
				PTD->PCOR |= (1<<3);														//M2+
				PTC->PCOR |= (1<<3);														//M2-
			}
		}
		*/
		switch(mstate){
			case 0:{
				if(mcount==0) mstate = 1;
				PTD->PSOR |= (1<<3);														//M2+
				PTC->PCOR |= (1<<3);														//M2-
			} break;
			case 1:{
				PTD->PCOR |= (1<<3);														//M2+
				PTC->PCOR |= (1<<3);														//M2-
			} break;
		}
		
		/*switch(action){
			case 0:{
				arm_mean_q15(IM2_Buffer,SIZE,&IM2_mean);
				switch(mstate){
					case 0:{
						if(IM2_mean>160) mstate = 1;
						PTD->PCOR |= (1<<3);														//M2+
						PTC->PSOR |= (1<<3);														//M2-
					} break;
					case 1:{
						PTD->PCOR |= (1<<3);														//M2+
						PTC->PCOR |= (1<<3);														//M2-
					}
				}
			} break;
			case 5:{
				switch(mstate){
					case 1:{
						if(mcount==0) mstate = 1;
						PTD->PSOR |= (1<<3);														//M2+
						PTC->PCOR |= (1<<3);														//M2-
					} break;
					case 0:{
						PTD->PCOR |= (1<<3);														//M2+
						PTC->PCOR |= (1<<3);														//M2-
					} break;
				}
			}
		}*/
	}
}


//Interrupts
void PORTC_IRQHandler(void){
	if(PORTC->PCR[6]&PORT_PCR_ISF_MASK){
		if(count<9) count++;
		else count = 0;
		PORTC->PCR[6] |= (PORT_PCR_ISF_MASK);
		LED_On();
	}
	if(PORTC->PCR[7]&PORT_PCR_ISF_MASK){
		if(count>0) count--;
		else count = 9;
		PORTC->PCR[7] |= (PORT_PCR_ISF_MASK);
		LED_Off();
	}	
	switch(count){
		case 0: action = 0; break;
		case 1: action = 5; break;
		case 2: action = 1; break;
		case 3: action = 5; break;
		case 4: action = 2; break;
		case 5: action = 5; break;
		case 6: action = 3; break;
		case 7: action = 5; break;
		case 8: action = 4; break;
		case 9: action = 5; break;
	}
	UART0_send(action+'0');
		
}

void SysTick_Handler(void) {
	//LED_Toggle();
	IM2_Buffer[ticks%SIZE] = ADC0_Read(4);
	if (mstate==0) mcount--;
	ticks++; 
}

void UART0_RX_TX_IRQHandler(void){
	uint8_t data ;
  (void) UART0->S1;
	data = UART0->D;
	UART0->D = data;
}

//DC Motors 
void FTM0_IRQHandler(void){
	if(FTM0->SC & FTM_SC_TOF_MASK){
		FTM0->SC &= ~FTM_SC_TOF_MASK;
		PTC->PSOR |= (1<<4);														//M1+
		PTC->PCOR |= (1<<2);														//M1-
		PTD->PSOR |= (1<<3);														//M2+
		PTC->PCOR |= (1<<3);														//M2-
		PTD->PSOR |= (1<<2);														//M3+
		PTD->PCOR |= (1<<4);														//M3-
		PTA->PSOR |= (1<<13);														//M4+
		PTD->PCOR |= (1<<7);														//M4-
		PTD->PSOR |= (1<<0);														//M5+
		PTA->PCOR |= (1<<12);														//M5-
		PTC->PSOR |= (1<<1);														//M6+
		PTD->PCOR |= (1<<6);														//M6-
	}
	if(FTM0->CONTROLS[0].CnSC & FTM_CnSC_CHF_MASK){		//M1
		FTM0->CONTROLS[0].CnSC &= ~FTM_CnSC_CHF_MASK;	
		PTC->PSOR |= (1<<2);														//M1+
		PTC->PCOR |= (1<<4);														//M1-
	}
	if(FTM0->CONTROLS[1].CnSC & FTM_CnSC_CHF_MASK){		//M2
		FTM0->CONTROLS[1].CnSC &= ~FTM_CnSC_CHF_MASK;
		PTD->PCOR |= (1<<3);														//M2+
		PTC->PSOR |= (1<<3);														//M2-
	}
	if(FTM0->CONTROLS[2].CnSC & FTM_CnSC_CHF_MASK){		//M3
		FTM0->CONTROLS[2].CnSC &= ~FTM_CnSC_CHF_MASK;	
		PTD->PCOR |= (1<<2);														//M3+
		PTD->PSOR |= (1<<4);														//M3-
	}
	if(FTM0->CONTROLS[3].CnSC & FTM_CnSC_CHF_MASK){		//M4
		FTM0->CONTROLS[3].CnSC &= ~FTM_CnSC_CHF_MASK;
		PTA->PCOR |= (1<<13);														//M4+
		PTD->PSOR |= (1<<7);														//M4-
	}
	if(FTM0->CONTROLS[4].CnSC & FTM_CnSC_CHF_MASK){		//M5
		FTM0->CONTROLS[4].CnSC &= ~FTM_CnSC_CHF_MASK;	
		PTD->PCOR |= (1<<0);														//M5+
		PTA->PSOR |= (1<<12);														//M5-
	}
	if(FTM0->CONTROLS[5].CnSC & FTM_CnSC_CHF_MASK){		//M6
		FTM0->CONTROLS[5].CnSC &= ~FTM_CnSC_CHF_MASK;
		PTC->PCOR |= (1<<1);														//M6+
		PTD->PSOR |= (1<<6);														//M6-
	}
}
	
