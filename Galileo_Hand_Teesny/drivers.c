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
	PORTC->PCR[5]  = (1UL <<  8);                           											//PTC.5 is GPIO 
	PTC->PDOR &= ~(1UL <<  5);
	PTC->PDDR |= (1UL <<  5);
}

void Switch_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;							
	PORTC->PCR[6] |= PORT_PCR_IRQC(0x0A) + PORT_PCR_MUX(0x01) + PORT_PCR_PE_MASK;	 
	PORTC->PCR[6] &= ~(PORT_PCR_PS_MASK);
	PTC->PDDR &= ~(0 << 6);																												//Setting the bit 6 of the port C as Input
	PORTC->ISFR = PORT_ISFR_ISF(0x40); 	  																				//Clear interrupt status flag 
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
	PORTC->PCR[1] |= PORT_PCR_MUX(0x04);
	PORTC->PCR[2] |= PORT_PCR_MUX(0x04);
	PORTC->PCR[3] = PORT_PCR_MUX(0x04);
	FTM0->MODE |= FTM_MODE_WPDIS_MASK + FTM_MODE_INIT_MASK;												//Write protection disable   
	FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK;							//C2 Edge Align PWM High TRue
	FTM0->CONTROLS[1].CnSC = FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK;							//C4 Edge Align PWM High TRue
	FTM0->CONTROLS[2].CnSC = FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK;							//C7 Edge Align PWM High TRue
	FTM0->CONTROLS[0].CnV = FTM_CnV_VAL(0x0152);																	//C0V = 338 - 0.6ms
	FTM0->CONTROLS[1].CnV = FTM_CnV_VAL(0x0152);																	//C1V = 338 - 0.6ms
	FTM0->CONTROLS[2].CnV = FTM_CnV_VAL(0x0152);																	//C1V = 338 - 0.6ms
	FTM0->MOD = FTM_MOD_MOD(0x2BF2);																							//0x2BF2 = 11250, 11250*(1/(72MHz/2/64)) = 20 ms
	FTM0->SC = FTM_SC_CLKS(0x01) + FTM_SC_PS(0x06);																//System Clock/64									
}

void FTM1_Init(void){
	SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
	PORTA->PCR[12] = PORT_PCR_MUX(0x03);
	PORTA->PCR[13] = PORT_PCR_MUX(0x03);
	FTM1->MODE |= FTM_MODE_WPDIS_MASK; 																						//Write protection disable   
	FTM1->CONTROLS[0].CnSC = FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK;							//C0 Edge Align PWM High TRue
	FTM1->CONTROLS[1].CnSC = FTM_CnSC_MSB_MASK + FTM_CnSC_ELSB_MASK;							//C1 Edge Align PWM High TRue
	FTM1->CONTROLS[0].CnV = FTM_CnV_VAL(0x0546);																	//C0V = 1350 - 2.4ms
	FTM1->CONTROLS[1].CnV = FTM_CnV_VAL(0x0152);																	//C1V =  338 - 0.6ms
	FTM1->MOD = FTM_MOD_MOD(0x2BF2);																							//0x2BF2 = 11250, 11250*(1/(72MHz/2/64)) = 20 ms
	FTM1->SC = FTM_SC_CLKS(0x01) + FTM_SC_PS(0x06);																//System Clock/64 									
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

void UART2_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK; 
	PORTD->PCR[2] = (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_PFE_MASK | PORT_PCR_MUX(3));
	PORTD->PCR[3] = (PORT_PCR_DSE_MASK  | PORT_PCR_SRE_MASK | PORT_PCR_MUX(3));
	UART2->C2 &= (uint8_t)~(uint8_t)((UART_C2_TE_MASK | UART_C2_RE_MASK));
	UART2->BDH = UART_BDH_SBR(0x00);
	UART2->BDL = UART_BDL_SBR(0xEA);																																		//115200 bauds - 0x13, 9600 bauds - 0xEA
	UART2->C4 = UART_C4_BRFA(0x0C);																																			//115200 bauds - 0x11, 9600 bauds - 0x0C																										
	UART2->C1 = UART_C1_ILT_MASK;
	//UART2->TWFIFO = 2; 																																									// tx watermark, causes S1_TDRE to set
	//UART2->RWFIFO = 2; 																																									// rx watermark, causes S1_RDRF to set
	//UART2->PFIFO = UART_PFIFO_TXFE_MASK | UART_PFIFO_RXFE_MASK;
	UART2->C2 = (UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK);
	NVIC_EnableIRQ(UART2_RX_TX_IRQn);			
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
