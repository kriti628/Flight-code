#include "adc.h"
#include "avr_compiler.h"
#include "hmData.h"
#include <stdlib.h>

void adcInit(void){
	//enabling ADC, setting frequency pre-scaler to 16
	ADCSRA |= (1<<ADEN)|(1<<ADPS2);
}

void adcCheck(uint8_t mux, int i, uint8_t idealValue, volatile uint8_t *hmData2, volatile uint8_t *opMode2){
	/*Writes the adc value into EEPROM
	*parameters
	*mux     analog channel
	*/
	//setting external voltage reference, left adjust result
	ADMUX = 0x20;
	ADMUX |= mux;
	//start conversion
	ADCSRA |= (1<<ADSC);
	//wait for conversion to finish
	while(!(ADCSRA & (1<<ADIF)));
	
	hmData2+=i;
    *hmData2=ADCH;
  
    if(abs(ADCH-idealValue) > 0.5) *opMode2=EMERGENCY;
}
