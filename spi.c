void spiInit(void){
	//set MISO as output
	DDRB = (1<<3);
	//enable SPI and SPI interrupt
	SPCR |=(1<<SPIE)|(1<<SPE);
}

uint8_t spiTrans(uint8_t data){
	//load data into SPDR
	SPDR = data;
	// Wait for reception complete 
	while(!(SPSR & (1<<SPIF)));
	//Return data register
	return  SPDR;
}
