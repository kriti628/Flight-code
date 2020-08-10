#include "hmData.h"

void HMDataCheck(int freq){
	//setting the pin status variables to their starting value
	hmData[5]=0x00;
	hmData[9]=0x00;
	hmData[6]=0x00;
	//setting up the timer with the required settings and initializing the various communication protocols used
	setupTimer();
	adcInit();
	uartInit();
	spiInit();
	i2cInit();
	//enabling the external interrupts and enabling global interrupts
	
	
	while (opmode!=Emergency)
	{
		//this is the code that gets executed every minute, and writes the HM data in the EEPROM
		if (count==(freq/2))
		{
			//resetting the count variable and starting the i2c connection and sending the data to the EEPROM
			count=0;
			i2cStart();
			eepromWr();
			address(0x00);
			address(add);
			for (int i=0; i<18 ;i++){
				eepromWrite(hmData[i]);
			}
			i2cStop();
			}
      
    else 
    {
    	adcCheck(0,7,42);
      adcCheck(1,8,42);
      adcCheck(2,10,42);
      adcCheck(3,11,42);
      adcCheck(4,12,42);
      adcCheck(5,13,42);
      adcCheck(6,14,42);
      adcCheck(7,15,42);
    }
		
	}
}
