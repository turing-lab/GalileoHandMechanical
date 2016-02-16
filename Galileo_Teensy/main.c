#define ARM_MATH_CM4
#if !defined  (__FPU_PRESENT) 
  #define __FPU_PRESENT             1       
#endif 

#include "MK20D7.h"

void LED_Initialize(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
void FTM2_Init(void);
void UART0_Init(void);

int main (void) {
	PORTB->PCR[16] = PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_MUX(0x03);
  PORTB->PCR[17] = PORT_PCR_DSE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_MUX(0x03);
	LED_Initialize(); 
	FTM2_Init();
	UART0_Init();
	NVIC_EnableIRQ(FTM2_IRQn);
	NVIC_EnableIRQ(UART0_RX_TX_IRQn);			
	LED_On();
	
	while(1){
		
	}
	return 0;
}

void FTM2_IRQHandler(void){
	FTM2->SC &= ~(FTM_SC_TOF_MASK); 
	LED_Toggle();
}

void UART0_RX_TX_IRQHandler(void){
	
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

void LED_Initialize(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; 														  /* Enable Clock to Port C */ 
  PORTC->PCR[5]  = (1UL <<  8);                           /* PTC.5 is GPIO */
	PTC->PDOR &= ~(1UL <<  5);
	PTC->PDDR |= (1UL <<  5);
}

void FTM2_Init(void){
  SIM->SCGC3 |= SIM_SCGC3_FTM2_MASK;     
	FTM2->MODE |= FTM_MODE_WPDIS_MASK; 																						//Write protection disable   
  FTM2->CONTROLS[0].CnSC = FTM_CnSC_MSA_MASK;																		//Output Compare
  FTM2->CONTROLS[0].CnV = FTM_CnV_VAL(0x00);																		//Value = 0
	FTM2->MOD = FTM_MOD_MOD(0xDBBA);																							//0xDBBA = 11250, 56250*(1/(72MHz/2/64)) = 100 ms
	FTM2->SC = FTM_SC_TOIE_MASK + FTM_SC_CLKS(0x01) + FTM_SC_PS(0x06);						//Overflow interrupt, System Clock/64 										
}

void UART0_Init(void){
	SIM->SOPT5 &= (uint32_t)~(uint32_t)(SIM_SOPT5_UART0TXSRC(0x03));
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
  PORTB->PCR[16] = PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_MUX(0x03);
  PORTB->PCR[17] = PORT_PCR_DSE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_MUX(0x03);
  UART0->C2 &= (uint8_t)~(uint8_t)((UART_C2_TE_MASK | UART_C2_RE_MASK));
  UART0->BDH = UART_BDH_SBR(0x00);
  UART0->BDL = UART_BDL_SBR(0x27);
  UART0->C4 = UART_C4_BRFA(0x02);
  UART0->C1 = 0x00U;
  UART0->S2 = (UART_S2_LBKDIF_MASK | UART_S2_RXEDGIF_MASK);
  UART0->C3 = 0x00U;
  UART0->C2 = (UART_C2_TE_MASK | UART_C2_RE_MASK);//(UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK);
}

