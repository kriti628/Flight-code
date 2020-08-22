#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t hmData[18];
volatile uint8_t count;
volatile uint8_t add = 0, addr = 0;
int times=0;
int repeat=0;
uint8_t temp = 0x00;
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
{
	initInterrupt();
	sei();
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
			break;
			
			case INITIAL:
			HMDataCheck(60, hmData,&count,&add,&opMode);
			break;
			
			case PREDEPL:
			HMDataCheck(2, hmData,&count,&add,&opMode);
			break;
			
			case POSTDEPL:
			HMDataCheck(60, hmData,&count,&add,&opMode);
			break;
			
			case NOMINAL:
			HMDataCheck(60, hmData,&count,&add,&opMode);
			break;
		}
	}
		return 0;
}

	ISR(SPI_STC_vect){
		/*this is the interrupt for SPI communication from the PS4 OP micro controller, switch statement is used to store the data in different variables*/
		command = SPDR;
		switch(command){
			case kill:
			opMode = KILL;
			break;
			
			case emergency:
			opMode = EMERGENCY;
			break;
			
			case restart:
			opMode = RESTART;
			break;
			
			case deploy:
			opMode = PREDEPL;
			break;
			
			case send_data:
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
			
			case hm_data:
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
			}
			break;
		}
	}
	
	/*These are the external interrupts for various pin statuses that we are including in the HM data, that we are storing in variables*/
	ISR(TIMER1_COMPA_vect)
	{
		count++;
	}

	ISR(INT2_vect)
	{
		hmData[5] |= 0x30;
	}

	ISR(INT3_vect)
	{
		hmData[5] |= 0x03;
	}

	ISR(INT4_vect)
	{
		hmData[6] |= 0x30;
	}

	ISR(INT5_vect)
	{
		hmData[6] |= 0x03;
	}

	ISR(INT6_vect)
	{
		hmData[9] |= 0x30;
	}

	ISR(INT7_vect)
	{
		hmData[9] |= 0x03;
	}
