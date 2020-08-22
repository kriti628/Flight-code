#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define OUTPUT_COMPARE 0x3D08;
void setupTimer(volatile uint8_t *count2);

#endif
