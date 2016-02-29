#include <stdint.h>

int head, tail;
extern float *samples;

void init_Queue(void){
    head = tail = -1;
}

int isEmpty(){
    return (head == tail);
}

void Enqueue(float sample){
    tail++;
    samples[tail] = sample;
}

float Dequeue(){
    float sample;
    head++;
    sample = samples[head];
    return sample;
}


