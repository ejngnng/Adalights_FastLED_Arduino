#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <Arduino.h>

#define MAX_ADA_RGB_BUFFER_SIZE 128

typedef struct rgb_s{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}rgb_t;

typedef struct ring_s{
    uint8_t head;
    uint8_t tail;
    uint8_t counter;
    rgb_t buffer[MAX_ADA_RGB_BUFFER_SIZE];
}ring_t;

void ringbuffer_setup();
bool ringbuffer_read(rgb_t *rgb);
bool ringbuffer_write(rgb_t rgb);

#endif