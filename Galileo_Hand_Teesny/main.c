#define ARM_MATH_CM4

#include <stdlib.h>
#include "MK20D7.h"
#include "drivers.h"
#include "EasyVR.h"
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SAMPLES 							100
#define NUM_TAPS              29

uint32_t i = 0;
uint8_t COCO = 0;

uint32_t count = 0;
uint8_t status_state = 0;
uint8_t speech = 'a';

uint32_t ulValue[3];
float32_t E1_Voltage;
float32_t E2_Voltage;

float32_t mean = 0.0f;
float32_t mean1 = 0.0f;
float32_t mean2 = 0.0f;
float32_t mean33 = 0.0f;
float32_t samples1[100];
float32_t samples2[100];
float32_t abs_samples1[100];
float32_t abs_samples2[100];
float32_t fir_samples1[100];
float32_t fir_samples2[100];
float32_t ones[100];

q31_t mean3;
q31_t samples3[100];
q31_t abs_samples3[100];
q31_t fir_samples3[100];
float32_t fir_samples33[100];

static float32_t firStateF32[SAMPLES + NUM_TAPS - 1];
static q31_t firStateQ31[SAMPLES + NUM_TAPS - 1];
//LPF FIR Impulse response
float32_t h[29] = {
	 0.005122283331907f,0.005887141527430f,0.008108906860497f,0.011692906924201f,0.016472293441426f,0.022216298876727f,0.028641952887652f,0.035428649080362f,
	 0.042234794064957f,0.048715653723188f,0.054541442583407f,0.059414685262420f,0.063085915202651f,0.065366863558607f,0.0661404253491338f,0.065366863558607f,
	 0.063085915202651f,0.059414685262420f,0.054541442583407f,0.048715653723188f,0.042234794064957f,0.035428649080362f,0.028641952887652f,0.022216298876727f,
	 0.016472293441426f,0.011692906924201f,0.008108906860497f,0.005887141527430f,0.005122283331907f
};

q31_t H[29] = {
		0x0A7D8D3,0x0C0E8EC,0x109B670,0x17F2736,0x21BC39C,0x2D7FBD2,0x3AA8A1D,0x488ED0C,
		0x567F321,0x63C5085,0x6FB36C8,0x79AE681,0x8133303,0x85DF0FE,0x8774A19,0x85DF0FE,
	  0x8133303,0x79AE681,0x6FB36C8,0x63C5085,0x567F321,0x488ED0C,0x3AA8A1D,0x2D7FBD2,
		0x21BC39C,0x17F2736,0x109B670,0x0C0E8EC,0x0A7D8D3
};

arm_fir_instance_f32 S;
arm_fir_instance_q31 SS;

int main (void) {
	//array initialization
	arm_fill_f32(0.5f, samples1, SAMPLES);
	arm_fill_f32(0.5f, samples2, SAMPLES);
	arm_float_to_q31(samples1, samples3, SAMPLES);
	arm_float_to_q31(h, H, NUM_TAPS);
	arm_fill_f32(1.0f, ones, SAMPLES);
	arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&h[0], &firStateF32[0], SAMPLES);
	arm_fir_init_q31(&SS, NUM_TAPS, (q31_t *)&H[0], &firStateQ31[0], SAMPLES);
	
	//Peripherals initialization
	SysTick_Config(SystemCoreClock/10);
	Switch_Init();
	LED_Init(); 
	FTM0_Init();
	FTM1_Init();
	ADC0_Init();
	UART0_Init();
	UART2_Init();
	
	LED_Off();
	
	//Easy VR initialization
  EasyVR_Init();	
	
	COCO = 0;
	
  while(1){
		if(COCO){
			//mean for threshold
			arm_abs_f32(samples1, abs_samples1, 100);													//Rectifier
			arm_fir_f32(&S, abs_samples1, fir_samples1, SAMPLES);							//LPF FIR 
			arm_abs_f32(samples2, abs_samples2, 100);													//Rectifier
			arm_fir_f32(&S, abs_samples1, fir_samples2, SAMPLES);							//LPF FIR 
			arm_abs_q31(samples3, abs_samples3, 100);													//Rectifier
			arm_fir_q31(&SS, abs_samples3, fir_samples3, SAMPLES);						//LPF FIR 
			arm_q31_to_float(fir_samples3,fir_samples33, SAMPLES);
			arm_mean_f32(fir_samples1, 100, &mean1);														//RMS
			arm_mean_f32(fir_samples2, 100, &mean2);														//RMS			
			arm_mean_f32(fir_samples33, 100, &mean);														//RMS			
			arm_mean_q31(fir_samples3, 100, &mean3);	
			mean33 = mean3/2147483648.0f;
			COCO = 0;
		}
		
	}
}

//Interrupts
void PORTC_IRQHandler(void){
	if(PORTC->PCR[6]&PORT_PCR_ISF_MASK){
		PORTC->PCR[6] |= (PORT_PCR_ISF_MASK);
		UART0_putString("Start recognition!\r\n");
		EasyVR_Start();
		for(i=0;i<720000;i++);
	}
}

void SysTick_Handler(void) {
	uint32_t m;
	LED_Toggle();
	ulValue[0] = ADC0_Read(0);
	ulValue[1] = ADC0_Read(1);
	ulValue[2] = ADC0_Read(2);
	E1_Voltage = ((int32_t)(ulValue[0]-ulValue[2])*3.3f)/4095.0f;		//Palmaris Longus
	E2_Voltage = ((int32_t)(ulValue[1]-ulValue[2])*3.3f)/4095.0f;		//Extonsorum Digitorum
	
	m = __get_PRIMASK();
	__disable_irq();		
	
	for(i=SAMPLES-1;i>0;i--) {
		samples1[i]=samples1[i-1];														//Fill Array
		samples2[i]=samples2[i-1];														//Fill Array
	}
	samples1[0]=E1_Voltage;
	samples2[0]=E2_Voltage;
	
	__set_PRIMASK(m);
	COCO = 1;
}

void UART0_RX_TX_IRQHandler(void){
	uint8_t data ;
  (void) UART0->S1;
	data = UART0->D;
	UART0->D = data;
}

void UART2_RX_TX_IRQHandler(void){
	uint8_t status;
  (void) UART2->S1;
	status = UART2->D;
	switch (status_state){
		case 0:{
			switch(status){
				case 's':{
					EasyVR_Read();
					status_state = 1;
				} break;
				case 't':{
					status_state = 0;
					UART0_putString("timeout...\r\n");
				} break;
				case 'v':{
					status_state = 0;
					UART0_putString("invalid...\r\n");
				} break;
				case 'e':{
					status_state = 0;
					UART0_putString("error...\r\n");
				}
				case 'o':{
					status_state = 0;
					UART0_putString("OK...\r\n");
				}
				default:{
					status_state = 0;
					UART0_putString("invalid...\r\n");
				}
			}
		} break;
		case 1:{
			speech = EasyVR_Speech(status);
			switch(speech){
				case 0: UART0_putString("Zero\r\n"); break;
				case 1: UART0_putString("One\r\n"); break;
				case 2: UART0_putString("Two\r\n"); break;
				case 3: UART0_putString("Three\r\n"); break;
				case 4: UART0_putString("Four\r\n"); break;
				case 5: UART0_putString("Five\r\n"); break;
				case 6: UART0_putString("Six\r\n"); break;
				case 7: UART0_putString("Seven\r\n"); break;
				case 8: UART0_putString("Eight\r\n"); break;
				case 9: UART0_putString("Nine\r\n"); break;
				case 10: UART0_putString("Ten\r\n"); break;
			}	
			status_state = 0;
		}
	}
}


 

