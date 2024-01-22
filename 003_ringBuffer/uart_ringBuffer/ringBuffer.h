#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

#define RING_SIZE   64
typedef uint8_t ring_pos_t;
volatile ring_pos_t ring_head;
volatile ring_pos_t ring_tail;
volatile char ring_data[RING_SIZE];

int add(char c);
int remove(void);
