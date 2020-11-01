#include "avr_lib.h"
#include "adc.h"
#include "hmData.h"
#include <stdlib.h>

extern uint8_t hmData[18];
extern uint8_t opMode;  

void adcInit(void){
	//enabling ADC, setting frequency pre-scaler to 16
	ADCSRA = (1<<ADEN)|(1<<ADPS2);
}

void adcCheck(uint8_t mux, int i, uint8_t idealValue){
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
	
	hmData[i] = ADCH;
	if(abs(hmData[i]-idealValue) > 0.5) opMode=EMERGENCY;
	}

void voltageCheck(int i, uint8_t idealValue){
    if(abs(hmData[i]-idealValue) > 0.5) opMode=EMERGENCY;
}
