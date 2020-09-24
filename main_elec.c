/*
 * flight_code_elec.c
 *
 * Created: 9/13/2020 9:46:36 AM
 * Author : kriti
 */ 
#define F_CPU 8000000

#include "avr_lib.h"

volatile uint8_t hmData[18];
volatile int counter1 = 0;
volatile int counter2 = 0;
uint8_t add = 0, addr = 0;
volatile int times=0;
volatile int repeat=0;
volatile uint8_t temp = 0x00;
volatile uint8_t opMode;
volatile uint8_t command;

#include "timer.h"
#include "interrupt.h"
#include "adc.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"
#include "hmData.h"

int main(void)
{	opMode = INITIAL;
	DDRA = 0xFF;
	DDRC = 0xFF;
	initInterrupt();
	sei();
	setupTimer();
	adcInit();
	uartInit();
	spiInit();
	i2cInit();
	/*while(1)
	{
		switch(opMode)
		{
			case KILL:
			_delay_ms(10);
			break;
			
			case RESTART:
			_delay_ms(10);
			break;
			
			case EMERGENCY:
			_delay_ms(10);
			PORTA = 0x01;
			break;
			
			case INITIAL:
			PORTA = 0x02;
			HMDataLoop(2, 60);
			PORTA = 0x10;
			break;
			
			case PREDEPL:
			HMDataLoop(2, 4);
			break;
			
			case POSTDEPL:
			HMDataLoop(2, 60);
			break;
			
			case NOMINAL:
			HMDataLoop(2, 60);
			break;
		}
	}*/
	HMDataLoop(2, 60);
	//PORTA = 0x01;
	return 0;
}

ISR(SPI_STC_vect){
	/*this is the interrupt for SPI communication from the PS4 OP micro controller, switch statement is used to store the data in different variables*/
	/*command = SPDR;
	switch(command){
		case KILL_COMMAND:
		opMode = KILL;
		break;
		
		case EMERGENCY_COMMAND:
		opMode = EMERGENCY;
		break;
		
		case RESTART_COMMAND:
		opMode = RESTART;
		break;
		
		case DEPLOY_COMMAND:
		opMode = PREDEPL;
		break;
		
		case SEND_DATA_COMMAND:
		i2cStart();
		eepromWr();
		address(0x00);
		address(addr);
		temp = SPDR;
		SPDR = eepromRandomRead();
		i2cStop();
		//ensuring the data gets read to a certain address
		if(addr == 0x09) times = 0;
		else times = 5;
		addr++;
		break;
		
		case TIMESTAMP:*/
		switch(times){
			case 0 :
			hmData[0]=SPDR;
			times++;
			break;
			
			case 1 :
			hmData[1]=SPDR;
			times++;
			break;
			
			case 2 :
			hmData[2]=SPDR;
			times++;
			break;
			
			case 3 :
			hmData[3]=SPDR;
			times = 0;
			break;
		//break;
	}
}

/*These are the external interrupts for various pin statuses that we are including in the HM data, that we are storing in variables*/
ISR(TIMER1_COMPC_vect){
	TCNT1 = 0;
	counter1++;
	PORTA = 0x01;
	_delay_ms(100);
	PORTA = 0x00;
}



