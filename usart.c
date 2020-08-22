#include "usart.h"
#include "avr_compiler.h"

void uartInit (void){
	//setting baud rate to 9600
	UBRR0H=0x00;
	UBRR0L=0x33;
	//setting no. of data bits to 8
	UCSR0C=0x06;
	//enable receive complete interrupt, receiver enable, transmitter enable
	UCSR0B=0x98;
}
