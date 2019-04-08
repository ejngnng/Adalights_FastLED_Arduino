#ifndef ADA_H
#define ADA_H

#include <Arduino.h>

#define BAUD_RATE   57600

typedef enum{
    STATE_WAIT = 0,
    STATE_HEADER,
    STATE_DATA
}ada_state;

void ada_setup();
void ada_loop();

void ada_header_construct(uint8_t *header, uint16_t led_size);
void adaHeader_print(uint16_t led_size);

#endif