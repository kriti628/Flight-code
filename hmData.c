#include "avr_lib.h"
#include "hmData.h"
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "timer.h"

extern uint8_t hmData[18];
extern uint8_t opMode;
extern int counter1;
extern int counter2;
extern uint8_t addr;

void HMDataLoop(int freq1, int freq2){
	//setting the pin status variables to their starting value
	hmData[5]=0x00;
	hmData[6]=0x00;
	hmData[9]=0x00;
	//setting up the timer with the required settings and initializing the various communication protocols used
	
	//enabling the external interrupts and enabling global interrupts
	
	while(1){
		if(counter1 == 2){
			counter1 = 0;
			
			adcCheck(0x00,7,42);
			adcCheck(0x01,8,42);
			adcCheck(0x02,10,42);
			adcCheck(0x03,11,42);
			adcCheck(0x04,12,42);
			adcCheck(0x05,13,42);
			adcCheck(0x06,14,42);
			adcCheck(0x07,15,42);
			
			counter2++ ;
			PORTC = counter2;
			_delay_ms(100);
			PORTC = 0x00;
			}
			//this is the code that gets executed every minute, and writes the HM data in the EEPROM
		if (counter2 == 5){	
			//resetting the count variable and starting the i2c connection and sending the data to the EEPROM
			counter2 = 0;
			if (PE0 == 1 && PE1 == 1) hmData[5] = 0x33;
			if (PE2 == 1 && PE3 == 1) hmData[6] = 0x33;
			if (PE4 == 1 && PE5 == 1) hmData[9] = 0x33;
			i2cStart();
			eepromWr();
			address(0x00);
			address(addr);
			for (int i=0; i<18 ;i++){
				eepromWrite(hmData[i]);
				}
			i2cStop();
			}
		
		}
	}
