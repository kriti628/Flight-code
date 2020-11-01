#include "avr_lib.h"
#include "hmData.h"
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "timer.h"

extern uint8_t hmData[18];
extern uint8_t opMode;
extern int timeCounter1;
extern int timeCounter2;
extern uint8_t addr;
extern int uartTransCounter;

void HMDataLoop(int freq1, int freq2){
	//setting the pin status variables to their starting value
	hmData[5]=0x00;
	hmData[6]=0x00;
	hmData[9]=0x00;
	//setting up the timer with the required settings and initializing the various communication protocols used
	
	//enabling the external interrupts and enabling global interrupts
	
	while(1){
		if(timeCounter1 == 2){
			timeCounter1 = 0;
			
			adcCheck(0x00,7,42);
			adcCheck(0x01,8,42);
			adcCheck(0x02,10,42);
			adcCheck(0x03,11,42);
			adcCheck(0x04,12,42);
			adcCheck(0x05,13,42);
			adcCheck(0x06,14,42);
			adcCheck(0x07,15,42);
			
			// receive data from comm microcontroller
			uartTransCounter = 18;
			UDR0 = 0x04;
			//check voltage values on comm microcontroller
			voltageCheck(16, 42);
			voltageCheck(4,42);
			
			timeCounter2++ ;
			}
		//this is the code that gets executed every minute, and writes the HM data in the EEPROM
		if (timeCounter2 == 30){	
			//resetting the count variable and starting the i2c connection and sending the data to the EEPROM
			timeCounter2 = 0;
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
		if(opMode==NOMINAL){
			if(timecounter2==15){
				uartTransCounter= 18;
				UDR0 = 0x02;	
				}
			if(timeCounter2==30){
				uartTransCounter = 0;
				UDR0 = 0x03;
				}
			}
			
		
		
		}
	}
