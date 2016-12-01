#ifndef OS_H_
#define OS_H_

#include <stdint.h>

#define NUMTHREADS  4        // maximum number of threads
#define STACKSIZE   100      // number of 32-bit words in stack per thread

struct tcb{
  int32_t *sp;       // pointer to stack (valid for threads not running
  struct tcb *next;  // linked-list pointer
};
typedef struct tcb tcbType;									

extern void KernelStart(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical(void);    
void EndCritical(long sr);    // restore I bit to previous value
void SetInitialStack(int i);
void KernelInit(void);
void KernelLaunch(uint32_t freq);
void Scheduler(void);
int AddThreads(void(*thread0)(void),
                  void(*thread1)(void),
                  void(*thread2)(void),
                  void(*thread3)(void));

#endif /* OS_H_ */
