#ifndef EASYVR_H_
#define EASYVR_H_

#include <stdint.h>
#include "drivers.h"

void EasyVR_Init(void);
void EasyVR_Start(void);
void EasyVR_Read(void);
char EasyVR_Speech(char status);
	
#endif /* EASYVR_H_ */
