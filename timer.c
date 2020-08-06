#include "timer.h"

void setupTimer(void){
	//enabling output compare interrupt
	TIMSK = (1<<OCIE1A);
	//putting the value to compare counter with
	OCR1A = OUTPUT_COMPARE;
	//selecting clock, enabling CTC mode (Clear Timer on Compare) 
	TCCR1B = (1<<CS12)|(1<<CS10)|(1<<WGM12);
	count=0;
}
