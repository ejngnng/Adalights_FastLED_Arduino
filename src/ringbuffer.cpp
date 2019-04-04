#include "ringbuffer.h"

ring_t ada_buffer;

void ringbuffer_setup(){
    memset(&ada_buffer, 0, sizeof(ring_t));
}

bool ringbuffer_read(rgb_t *rgb){
    if(ada_buffer.counter == 0){
        return false;
    }
    *rgb = ada_buffer.buffer[ada_buffer.head];
    ada_buffer.head = (ada_buffer.head + 1) % MAX_ADA_RGB_BUFFER_SIZE;
    ada_buffer.counter --;

    return true;

}

bool ringbuffer_write(rgb_t rgb){
    if(ada_buffer.counter >= MAX_ADA_RGB_BUFFER_SIZE){
        return false;
    }

    ada_buffer.buffer[ada_buffer.tail] = rgb;
    ada_buffer.tail = (ada_buffer.tail + 1) % MAX_ADA_RGB_BUFFER_SIZE;
    ada_buffer.counter ++;

    return true;
}