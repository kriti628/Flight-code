/*
 * flight_code_elec.c
 *
 * Created: 9/13/2020 9:46:36 AM
 * Author : kriti
 */ 
#define F_CPU 8000000

#include "avr_lib.h"

volatile uint8_t hmData[18];
volatile int timeCounter1 = 0;
volatile int timeCounter2 = 0;
uint8_t add = 0, addr = 0;
volatile int spiRecCounter=0;
volatile int uartRecCounter=0;
volatile int uartTransCounter=0;
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
	while(1)
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
	}
}

ISR(SPI_STC_vect){
	/*this is the interrupt for SPI communication from the PS4 OP micro controller, switch statement is used to store the data in different variables*/
	command = SPDR;
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
		if(addr == 0x09) spiRecCounter = 0;
		else spiRecCounter = 5;
		addr++;
		break;
		
		case TIMESTAMP:
		switch(spiRecCounter){
			case 0 :
			hmData[0]=SPDR;
			spiRecCounter++;
			break;
			
			case 1 :
			hmData[1]=SPDR;
			spiRecCounter++;
			break;
			
			case 2 :
			hmData[2]=SPDR;
			spiRecCounter++;
			break;
			
			case 3 :
			hmData[3]=SPDR;
			spiRecCounter = 0;
			break;
		break;
	}
}

/*These are the external interrupts for various pin statuses that we are including in the HM data, that we are storing in variables*/
ISR(TIMER1_COMPC_vect){
	TCNT1 = 0;
	timeCounter1++;
	PORTA = 0x01;
	_delay_ms(100);
	PORTA = 0x00;
}
	
ISR(USART0_RX_vect)
{
	/*this is the interrupt for the USART communicstion, for getting the HM data from comm microcontroller*/
	switch(uartRecCounter){
		case 0:
		hmData[4] = UDR0;
		uartRecCounter++;
		break;
		
		case 1:
		hmData[16] = UDR0;
		uartRecCounter++;
		break;
		
		case 2:
		hmData[17] = UDR0;
		uartRecCounter = 0;
		break;
		

}
	
ISR(USART0_TX_vect)
{
	/*this is the interrupt for the USART communicstion, for  SENDING the HM data to comm microcontroller*/
	if(uartTransCounter<18){
	UDR0 = hmData[uartTransCounter];
	uartTransCounter++;
	}
}



