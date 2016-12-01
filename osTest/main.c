#include "stm32f3xx.h"                  // Device header
#include "os.h"                  

void Task0(void);
void Task1(void);
void Task2(void);
void Task3(void);
									
uint32_t ticks0 = 0, ticks1 = 0, ticks2 = 0, ticks3 = 0;
									
int main(void){
	KernelInit();
	AddThreads(&Task0, &Task1, &Task2, &Task3);
	KernelLaunch(100000);
	return 0;
}

void Task0(void){
	//thread 0
	while(1){
		ticks0++;
	}
}

void Task1(void){
	//thread 1
	while(1){
		ticks1 = ticks1 + 2;
	}
}

void Task2(void){
	//thread 2
	while(1){
		ticks2 = ticks2 + 3;
	}
}

void Task3(void){
	//thread 3
	while(1){
		ticks3 = ticks3 + 4;
	}
}
