  
  #ifndef ADC_H
  #define ADC_H

  #include <stdint.h>

  void adcInit(void);
  void adcCheck(uint8_t mux, int i, uint8_t idealValue);

  #endif
