#include "avr_lib.h"
#include "timer.h"

void setupTimer(void){
	//selecting clock, enabling CTC mode (Clear Timer on Compare)
	TCCR1B = (1<<CS12)|(1<<CS10);
	//putting the value to compare counter with
	OCR1C = OUTPUT_COMPARE;
	//enabling output compare interrupt
	ETIMSK = (1<<OCIE1C);
	TCNT1 = 0;
	
}
