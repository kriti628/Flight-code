#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adcInit(void);
void adcCheck(uint8_t mux, int i, uint8_t idealValue, volatile uint8_t *hmData2, volatile uint8_t *opMode2);

#endif
