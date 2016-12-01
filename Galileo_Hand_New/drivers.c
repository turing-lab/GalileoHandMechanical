#include <stdint.h>
#include "MK20D7.h"

static const uint8_t channel2sc1a[] = {
	5, 14, 8, 9, 13, 12, 6, 7, 15, 4,
	0, 19, 3, 19+128, 26, 18+128, 23,
	5+192, 5+128, 4+128, 6+128, 7+128, 4+192
};

//Peripheral Configurations
void LED_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; 																					//Enable Clock to Port C  
	PORTC->PCR[5]  = (1<<8);                           														//PTC.5 is GPIO  	
	PTC->PDOR &= ~(1<<5);
	PTC->PDDR |= (1<<5);																													//PTC.5 as Output
}

void Output_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;	
	PORTC->PCR[2] |= PORT_PCR_MUX(0x01);																					//PTC.2 is gayyyyyyyyyb! GPIO -> M1-
	PORTC->PCR[4] |= PORT_PCR_MUX(0x01);																					//PTC.4 is GPIO -> M1+
	PORTC->PCR[3] |= PORT_PCR_MUX(0x01);																					//PTC.3 is GPIO -> M2-
	PORTD->PCR[3] |= PORT_PCR_MUX(0x01);																					//PTD.3 is GPIO -> M2+
	PORTD->PCR[4] |= PORT_PCR_MUX(0x01);																					//PTD.4 is GPIO -> M3-
	PORTD->PCR[2] |= PORT_PCR_MUX(0x01);																					//PTD.2 is GPIO -> M3+
	PORTD->PCR[7] |= PORT_PCR_MUX(0x01);																					//PTD.7 is GPIO -> M4-
	PORTA->PCR[13] |= PORT_PCR_MUX(0x01);																					//PTA.13 is GPIO -> M4+
	PORTA->PCR[12] |= PORT_PCR_MUX(0x01);																					//PTA.12 is GPIO -> M5-
	PORTD->PCR[0] |= PORT_PCR_MUX(0x01);																					//PTD.0 is GPIO -> M5+
	PORTD->PCR[6] |= PORT_PCR_MUX(0x01);																					//PTD.6 is GPIO -> M6-
	PORTC->PCR[1] |= PORT_PCR_MUX(0x01);																					//PTC.1 is GPIO -> M6+
	PTA->PDDR |= (1<<12)|(1<<13);																									//PTA.12&13 amo a cw gayyyyyyy Output
	PTC->PDDR |= (1<<1)|(1<<2)|(1<<3)|(1<<4);																			//PTC.1,amo a 2,3&4 as Output 
	PTD->PDDR |= (1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<6)|(1<<7);												//PTD.0,2,3,4,6&7 as Output
}

void Switch_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;						
  PORTC->PCR[6] |= PORT_PCR_IRQC(0x09) + PORT_PCR_MUX(0x01) + PORT_PCR_PE_MASK;	//PTC6 es el 11 
	PORTC->PCR[6] |= PORT_PCR_PFE_MASK;
	PORTC->PCR[6] &= ~(PORT_PCR_PS_MASK);
	PORTC->PCR[7] |= PORT_PCR_IRQC(0x09) + PORT_PCR_MUX(0x01) + PORT_PCR_PE_MASK;	//PTC7 es el 12 
	PORTC->PCR[7] |= PORT_PCR_PFE_MASK;
	PORTC->PCR[7] &= ~(PORT_PCR_PS_MASK);
	PTC->PDDR &= ~(0 << 6);																												//Setting the bit 6 of the port C as Input
	PTC->PDDR &= ~(0 << 7);																												//Setting the bit 7 of the port C as Input
	PORTC->ISFR = PORT_ISFR_ISF(0xC0); 	  																				//Clear interrupt status flag 
	NVIC_EnableIRQ(PORTC_IRQn);		
}

//Ref 3.3V
void ADC0_Init(void){
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	ADC0->CFG1 = ADC_CFG1_MODE(1) + ADC_CFG1_ADLSMP_MASK + ADC_CFG1_ADICLK(0);  	//Clock/4 - short sample - 12 bits - Bus clk/2
	ADC0->CFG2 = ADC_CFG2_MUXSEL_MASK + ADC_CFG2_ADLSTS(2); 											//High Speed, ADCB - Clk enable
	ADC0->SC2 = 0x00;																															//Software trigger
	ADC0->SC3 = ADC_SC3_ADCO_MASK + ADC_SC3_AVGE_MASK + ADC_SC3_AVGS(2);					//Continuos conversions - Hardware Average - 16 samples
	ADC0->CV1 = 0x00;																															//Compare value not used
	ADC0->CV2 = 0x00;																															//Compare value not used
	ADC0->OFS = 0x04;																															//Offset value
}

void FTM0_Init(void){
  SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
	FTM0->MODE |= FTM_MODE_WPDIS_MASK + FTM_MODE_INIT_MASK;														//Write protection disable   
	FTM0->CONTROLS[0].CnSC = FTM_CnSC_CHIE_MASK+FTM_CnSC_MSB_MASK+FTM_CnSC_ELSB_MASK; //C0 Edge Align PWM High True
	FTM0->CONTROLS[1].CnSC = FTM_CnSC_CHIE_MASK+FTM_CnSC_MSB_MASK+FTM_CnSC_ELSB_MASK;	//C1 Edge Align PWM High True
	FTM0->CONTROLS[2].CnSC = FTM_CnSC_CHIE_MASK+FTM_CnSC_MSB_MASK+FTM_CnSC_ELSB_MASK; //C2 Edge Align PWM High True
	FTM0->CONTROLS[3].CnSC = FTM_CnSC_CHIE_MASK+FTM_CnSC_MSB_MASK+FTM_CnSC_ELSB_MASK;	//C3 Edge Align PWM High True
	FTM0->CONTROLS[4].CnSC = FTM_CnSC_CHIE_MASK+FTM_CnSC_MSB_MASK+FTM_CnSC_ELSB_MASK; //C4 Edge Align PWM High True
	FTM0->CONTROLS[5].CnSC = FTM_CnSC_CHIE_MASK+FTM_CnSC_MSB_MASK+FTM_CnSC_ELSB_MASK;	//C5 Edge Align PWM High True
	FTM0->CONTROLS[0].CnV = FTM_CnV_VAL(1125);																				//C0V = 1125 - 0.5 ms
	FTM0->CONTROLS[1].CnV = FTM_CnV_VAL(1125);																				//C1V = 1125 - 0.5 ms, 562, 1687, 0 , 2250
	FTM0->CONTROLS[2].CnV = FTM_CnV_VAL(1125);																				//C2V = 1125 - 0.5 ms
	FTM0->CONTROLS[3].CnV = FTM_CnV_VAL(1125);																				//C3V = 1125 - 0.5 ms
	FTM0->CONTROLS[4].CnV = FTM_CnV_VAL(1125);																				//C4V = 1125 - 0.5 ms
	FTM0->CONTROLS[5].CnV = FTM_CnV_VAL(1125);																				//C5V = 1125 - 0.5 ms*/
	FTM0->MOD = FTM_MOD_MOD(2250);																							  		//2250*(1/(72MHz/2/16)) = 1 msay
	FTM0->SC = FTM_SC_TOIE_MASK + FTM_SC_CLKS(0x01) + FTM_SC_PS(0x04);								//System Clock/16							 // Gayyyyyyyyyy gayyyyyyyyyy
	NVIC_EnableIRQ(FTM0_IRQn);
}

void UART0_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; 
	PORTB->PCR[16] = (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_PFE_MASK | PORT_PCR_MUX(3));
	PORTB->PCR[17] = (PORT_PCR_DSE_MASK  | PORT_PCR_SRE_MASK | PORT_PCR_MUX(3));
	UART0->C2 &= (uint8_t)~(uint8_t)((UART_C2_TE_MASK | UART_C2_RE_MASK));
	UART0->BDH = UART_BDH_SBR(0x00);																																		// 115200 Bauds	
	UART0->BDL = UART_BDL_SBR(0x27);	
	UART0->C4 = UART_C4_BRFA(0x02);
	UART0->C1 = UART_C1_ILT_MASK;
	//UART0->TWFIFO = 2; 																																									// tx watermark, causes S1_TDRE to set
	//UART0->RWFIFO = 2; 																																									// rx watermark, causes S1_RDRF to set
	//UART0->PFIFO = UART_PFIFO_TXFE_MASK | UART_PFIFO_RXFE_MASK;
	UART0->C2 = (UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK);
	NVIC_EnableIRQ(UART0_RX_TX_IRQn);			
}

//Methods
void LED_On(void){
	PTC->PSOR |= (1UL<<5);
}

void LED_Off(void){
	PTC->PCOR |= (1UL<<5);
}

void LED_Toggle(void){
	PTC->PTOR |= (1UL<<5);
}

uint16_t ADC0_Read(unsigned int index){
	uint8_t channel = channel2sc1a[index];
	ADC0->SC1[0] = ADC_SC1_ADCH(channel);   
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	return ADC0->R[0];
}

void UART0_send(char dato){
	while (!((UART0->S1)&(UART_S1_TDRE_MASK)));  
	UART0->D = dato;
}

void UART0_putString(char *mystring){
	while(*mystring){
		UART0_send(*mystring);
		mystring++;
	}
}

void UART2_send(char dato){
	while (!((UART2->S1)&(UART_S1_TDRE_MASK)));  
	UART2->D = dato;
}

void UART2_putString(char *mystring){
	while(*mystring){
		UART2_send(*mystring);
		mystring++;
	}
}
