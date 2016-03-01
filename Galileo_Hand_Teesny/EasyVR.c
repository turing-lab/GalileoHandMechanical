#include <stdint.h>
#include "drivers.h"

//Arguments 
//ASCII  @, A, B, C, D, E, F, G, H, I, J,
//Value -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 

void EasyVR_Init(void){
	UART2_send('l'); 																											//Language selection command
	UART2_send('E');																											//Spanish - E, English - A
	UART2_send('o');																											//Set Timeout command
	UART2_send('D'); 																											//3 seconds argument
}

void EasyVR_Start(void){
  UART2_send('i');																										  //Start recognition
  UART2_send('D');																										  //Set 3
}

void EasyVR_Read(void){
	UART2_send(' ');
}

char EasyVR_Speech(char status){
	return status - 'A';
}
