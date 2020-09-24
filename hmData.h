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


void HMDataLoop(int freq1, int freq2);

#endif
