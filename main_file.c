#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t hmData[18];
volatile uint8_t count;
volatile uint8_t add = 0, addr = 0;
int times=0;
int repeat=0;
uint8_t temp = 0x00;

#include "timer.c"
#include "interrupt.c"
#include "adc.c"
#include "i2c.c"
#include "usart.c"
#include "spi.c"
#include "hmData.c"

int main(void){
  initInterrupt();
  sei();
  while(1){
    switch(opMode){
    case KILL:
    break;
    
    case RESTART:
    break;
    
    case EMERGENCY:
    break;
    
    case INITIAL:
    HMDataCheck(60);
    break;
    
    case PREDEPL:
    HMDataCheck(2);
    break;
    
    case POSTDEPL:
    HMDataCheck(60);
    break;
    
    case NOMINAL:
    HMDataCheck(60);
    
    break;
  
  
  }
return 0;
}

ISR(SPI_STC_vect)
{	
	/*this is the interrrupt for SPI communication from the PS4 OP microcontroller, switch statement is used to store the data in different variables*/
	switch(times)
	{
		//cases 0-4 is getting operational mode and timestamp from PS4 OP microcontroller
		case 0 :
		hmData[4]=SPDR;
		times++;
		break;
			
		case 1 :
		hmData[0]=SPDR;
		times++;
		break;
			
		case 2 :
		hmData[1]=SPDR;
		times++;
		break;
			
		case 3 :
		hmData[2]=SPDR;
		times++;
		break;
			
		case 4 :
		hmData[3]=SPDR;
		times++;
		break;
		//this case is for reading the HM data from the EEPROM and sending it to PS4 for telemetry	
		case 5 :
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
