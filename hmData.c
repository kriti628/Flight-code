#include "hmData.h"
#include "avr_compiler.h"
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "timer.h"

void HMDataCheck(int freq, volatile uint8_t *hmData1, volatile int *count1, volatile int *add1, volatile uint8_t *opMode1){
	//setting the pin status variables to their starting value
	hmData1+=5;
	*hmData1=0x00;
	hmData1++;
	*hmData1=0x00;
	hmData1+=3;
	*hmData1=0x00;
	//setting up the timer with the required settings and initializing the various communication protocols used
	setupTimer(count1);
	adcInit();
	uartInit();
	spiInit();
	i2cInit(add1);
	//enabling the external interrupts and enabling global interrupts
	hmData1-=9;
	
	while (*opMode1!=EMERGENCY)
	{
		//this is the code that gets executed every minute, and writes the HM data in the EEPROM
		if (*count1==(freq/2))
		{
			//resetting the count variable and starting the i2c connection and sending the data to the EEPROM
			*count1=0;
			hmdata1 += 5;
			if (DEPL1 == 1 && DEPL2 == 1) *hmdata1 = 0x33;
			hmdata++;
			if (VOLT1 == 1 && VOLT2 == 1) *hmdata1 = 0x33;
			hmData1+=3;
			if (CURR1 == 1 && CURR2 == 1) *hmdata1 = 0x33;
			hmData1-=9;
			i2cStart();
			eepromWr();
			address(0x00);
			address(*add1);
			for (int i=0; i<18 ;i++){
				eepromWrite(*hmData1,add1);
				hmData1++;
			}
			hmData1-=17;
			i2cStop();
			}
      
    		else 
    		{
      			adcCheck(0,7,42,hmData1,opMode1);
     			adcCheck(1,8,42,hmData1,opMode1);
      			adcCheck(2,10,42,hmData1,opMode1);
      			adcCheck(3,11,42,hmData1,opMode1);
      			adcCheck(4,12,42,hmData1,opMode1);
      			adcCheck(5,13,42,hmData1,opMode1);
      			adcCheck(6,14,42,hmData1,opMode1);
      			adcCheck(7,15,42,hmData1,opMode1);
    			}
		
	}
}
