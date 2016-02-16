#define ARM_MATH_CM4
#if !defined  (__FPU_PRESENT) 
  #define __FPU_PRESENT             1       
#endif 

#include "MK20D7.h"

void Pin_Muxing(void);
void LED_Initialize(void);
void Switch_Initialize(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
void ADC_Init(void);
uint16_t ADC_Read(unsigned int channel);
void FTM1_Init(void);
void FTM2_Init(void);
void FTM0_Init(void);
void UART0_Init(void);

uint32_t i = 0;
uint32_t count = 0;
uint32_t value = 0;

static const uint8_t channel2sc1a[] = {
	5, 14, 8, 9, 13, 12, 6, 7, 15, 4,
	0, 19, 3, 19+128, 26, 18+128, 23,
	5+192, 5+128, 4+128, 6+128, 7+128, 4+192
};

int main (void) {
  // initialize peripherals here
	FTM1_Init();
  Switch_Initialize();
  LED_Initialize(); 
	FTM2_Init();
	FTM0_Init();
	ADC_Init();
	//UART0_Init();
	LED_Off();
	
  while(1){
		value = ADC_Read(0);
		//if(value>2048) LED_Off();
		//else LED_On();
	}
}

//Interrupciones
void PORTC_IRQHandler(void){
	if(PORTC->PCR[6]&PORT_PCR_ISF_MASK){
		PORTC->PCR[6] |= (PORT_PCR_ISF_MASK);
		//LED_Toggle();
		count++;
	}
}

void FTM2_IRQHandler(void){
	FTM2->SC &= ~(FTM_SC_TOF_MASK); 
	LED_Toggle();
}

//Metodos
void LED_On(void){
	PTC->PSOR |= (1UL<<5);
}

void LED_Off(void){
	PTC->PCOR |= (1UL<<5);
}

void LED_Toggle(void){
	PTC->PTOR |= (1UL<<5);
}

uint16_t ADC_Read(unsigned int index){
	uint8_t channel = channel2sc1a[index];
	ADC0->SC1[0] = ADC_SC1_ADCH(channel);   
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	return ADC0->R[0];
}

//Inicializaciones
void LED_Initialize(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; 														  /* Enable Clock to Port C */ 
  PORTC->PCR[5]  = (1UL <<  8);                           /* PTC.5 is GPIO */
	PTC->PDOR &= ~(1UL <<  5);
	PTC->PDDR |= (1UL <<  5);
}

void Switch_Initialize(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;							
	PORTC->PCR[6] |= PORT_PCR_IRQC(0x0A) + PORT_PCR_MUX(0x01) + PORT_PCR_PE_MASK;	 
	PORTC->PCR[6] &= ~(PORT_PCR_PS_MASK);
	PTC->PDDR &= ~(0 << 6);														/*Setting the bit 6 of the port C as Input*/
	PORTC->ISFR = PORT_ISFR_ISF(0x40); 	  					/* Clear interrupt status flag */
	NVIC_EnableIRQ(PORTC_IRQn);		
}

//Ref 3.3V
void ADC_Init(void){
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

void FTM2_Init(void){
  SIM->SCGC3 |= SIM_SCGC3_FTM2_MASK;     
	FTM2->MODE |= FTM_MODE_WPDIS_MASK; 																						//Write protection disable   
  FTM2->CONTROLS[0].CnSC = FTM_CnSC_MSA_MASK;																		//Output Compare
  FTM2->CONTROLS[0].CnV = FTM_CnV_VAL(0x00);																		//Value = 0
	FTM2->MOD = FTM_MOD_MOD(0xDBBA);																							//0xDBBA = 11250, 56250*(1/(72MHz/2/64)) = 100 ms
	FTM2->SC = FTM_SC_TOIE_MASK + FTM_SC_CLKS(0x01) + FTM_SC_PS(0x06);						//Overflow interrupt, System Clock/64 
	NVIC_EnableIRQ(FTM2_IRQn);										
}

void UART0_Init(void){
	SIM->SOPT5 &= (uint32_t)~(uint32_t)(SIM_SOPT5_UART0TXSRC(0x03));
  PORTB->PCR[16] = (uint32_t)(PORT_PCR_MUX(0x03));
  PORTB->PCR[17] = (uint32_t)(PORT_PCR_MUX(0x03));
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
  UART0->C2 &= (uint8_t)~(uint8_t)((UART_C2_TE_MASK | UART_C2_RE_MASK));
  UART0->BDH = UART_BDH_SBR(0x00);
  UART0->BDL = UART_BDL_SBR(0x27);
  UART0->C4 = UART_C4_BRFA(0x02);
  UART0->C1 = 0x00U;
  UART0->S2 = (UART_S2_LBKDIF_MASK | UART_S2_RXEDGIF_MASK);
  (void) UART0->S1;                   /* Dummy read of the UART0_S1 register to clear flags */
  (void) UART0->D;                    /* Dummy read of the UART0_D register to clear flags */
  UART0->C5 &= (uint8_t)~(uint8_t)(UART_C5_TDMAS_MASK | UART_C5_RDMAS_MASK | 0x4FU);
  UART0->C3 = 0x00U;
  UART0->C2 = (UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK);
	NVIC_EnableIRQ(UART0_RX_TX_IRQn);			
}
