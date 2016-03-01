#ifndef DRIVERS_H_
#define DRIVERS_H_

#include <stdint.h>

void LED_Init(void);
void Switch_Init(void);
void ADC0_Init(void);
void FTM1_Init(void);
void FTM0_Init(void);
void UART0_Init(void);
void UART2_Init(void);

void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
uint16_t ADC0_Read(unsigned int channel);
void UART0_send(char dato);
void UART0_putString(char *mystring);
void UART2_send(char dato);
void UART2_putString(char *mystring);

#endif /* DRIVERS_H_ */
