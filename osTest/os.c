#include "stm32f3xx.h"                  // Device header
#include "os.h"                  

tcbType tcbs[NUMTHREADS];
tcbType *RunPt;

int32_t Stacks[NUMTHREADS][STACKSIZE];

void KernelInit(void){
	DisableInterrupts();
}

void KernelLaunch(uint32_t freq){
	SysTick_Config(SystemCoreClock/freq);
	KernelStart(); 
}

void SetInitialStack(int i){
  tcbs[i].sp = &Stacks[i][STACKSIZE-16]; // thread stack pointer
  Stacks[i][STACKSIZE-1] = 0x01000000;   // thumb bit
  Stacks[i][STACKSIZE-3] = 0x14141414;   // R14
  Stacks[i][STACKSIZE-4] = 0x12121212;   // R12
  Stacks[i][STACKSIZE-5] = 0x03030303;   // R3
  Stacks[i][STACKSIZE-6] = 0x02020202;   // R2
  Stacks[i][STACKSIZE-7] = 0x01010101;   // R1
  Stacks[i][STACKSIZE-8] = 0x00000000;   // R0
  Stacks[i][STACKSIZE-9] = 0x11111111;   // R11
  Stacks[i][STACKSIZE-10] = 0x10101010;  // R10
  Stacks[i][STACKSIZE-11] = 0x09090909;  // R9
  Stacks[i][STACKSIZE-12] = 0x08080808;  // R8
  Stacks[i][STACKSIZE-13] = 0x07070707;  // R7
  Stacks[i][STACKSIZE-14] = 0x06060606;  // R6
  Stacks[i][STACKSIZE-15] = 0x05050505;  // R5
  Stacks[i][STACKSIZE-16] = 0x04040404;  // R4
}

int AddThreads(void(*thread0)(void),
                  void(*thread1)(void),
                  void(*thread2)(void),
                  void(*thread3)(void)){
	int32_t status;
	status = StartCritical();
	// initialize TCB circular list and initialize Stacks and PC
	tcbs[0].next = &tcbs[1]; // 0 points to 1
  tcbs[1].next = &tcbs[2]; // 1 points to 2
  tcbs[2].next = &tcbs[3]; // 2 points to 3
	tcbs[3].next = &tcbs[0]; // 3 points to 0
	SetInitialStack(0); Stacks[0][STACKSIZE-2] = (int32_t)(thread0); // PC
  SetInitialStack(1); Stacks[1][STACKSIZE-2] = (int32_t)(thread1); // PC
  SetInitialStack(2); Stacks[2][STACKSIZE-2] = (int32_t)(thread2); // PC
	SetInitialStack(3); Stacks[3][STACKSIZE-2] = (int32_t)(thread3); // PC									
	// initialize RunPt
	RunPt = &tcbs[0];       // thread 0 will run first
  EndCritical(status);

  return 1;               // successful
}
									
void Scheduler(void){ // every time slice
  // run any periodic event threads if needed
  // implement round robin scheduler, update RunPt
  RunPt = RunPt->next;    // Round Robin
}

  __asm void
  __weak DisableInterrupts(void)
  {
    CPSID   I
    bx      lr
  }
	
	__asm void
  __weak EnableInterrupts(void)
  {
    CPSIE   I
    bx      lr
  }
	
	__asm long
	__weak StartCritical(void)
  {
    MRS     R0, PRIMASK
    CPSID   I
    bx      lr
  }

	__asm void
  __weak EndCritical(long sr)
  {
    MSR     PRIMASK, R0
    bx      lr
  }
