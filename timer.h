#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "avr_lib.h"

#define OUTPUT_COMPARE 0x3D09
#define FREQ_FACTOR(OUTPUT_COMPARE, F_CPU) (1024/F_CPU)*OUTPUT_COMPARE


void setupTimer(void);

#endif
