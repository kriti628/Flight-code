#ifndef HMDATA_H
#define HMDATA_H

#include <stdint.h>

#define KILL 0b00000001
#define RESTART	0b00000010
#define EMERGENCY 0b00000100
#define INITIAL 0b00001000
#define PREDEPL 0b00010000
#define POSTDEPL 0b00100000
#define NOMINAL 0b01000000

void HMDataCheck(int freq,volatile uint8_t *hmData1,volatile int *count1,volatile int *add1,volatile uint8_t *opMode1);

#endif
