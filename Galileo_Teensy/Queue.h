#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

void init_Queue(void);
int isEmpty();
void Enqueue(float sample);
float Dequeue(void);

#endif /* QUEUE_H_ */