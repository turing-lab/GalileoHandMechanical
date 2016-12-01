#include "MKL25Z4.h"                    // Device header
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX


static void thread0 (void const *arg);
static void thread1 (void const *arg);
static void thread2 (void const *arg);


int main(void){
	
	osKernelInitialize();
	
	
	
	osKernelStart();
	
	while(1){
		
	}
	
	return 0;
}

static void thread0 (void const *arg){
	
	while(1){
	}
}

static void thread1 (void const *arg){
	
	while(1){
	}
}

static void thread2 (void const *arg){
	
	while(1){
	}
}