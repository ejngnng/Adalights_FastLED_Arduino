#ifndef ADA_H
#define ADA_H

#include <Arduino.h>

#define BAUD_RATE   57600

void ada_setup();
void ada_loop();

void serialEvent();

#endif