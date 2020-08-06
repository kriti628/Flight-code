void i2cInit(void){
	//setting division factor for SCL to 32
	TWBR=0x20;
	//setting prescaler to 1
	TWSR=0x00;
	add=0x00;
}

void i2cStart(void){
	//clearing interrupt flag, generate start condition, enable twi operation
	TWCR=0b10100100;
	//waiting for interrupt flag to set
	while(!(TWCR & (1<<TWINT)));
	//checking status register
	while((TWSR & 0xF8)!= 0x08);
}

void eepromWr(void){
	//loading SLA+W 
	TWDR=0b10100000;
	//clear TWINT
	TWCR=(1<<TWINT)|(1<<TWEN);
	//wait for flag to set
	while (!(TWCR & (1<<TWINT)));
	//check status register
	while( (TWSR & 0xF8) != 0x18);
}

void address(uint8_t addrs){
	/*sends to eeprom the address to write at
	*Parameters
	*addrs     address at which to write
	*/
	TWDR=addrs;
	//clear TWINT
	TWCR=(1<<TWINT)|(1<<TWEN);
	//wait for flag to set
	while (!(TWCR & (1<<TWINT)));
	//check status register
	while( (TWSR & 0xF8) != 0x28);
}

void eepromWrite(unsigned char data){
	//load data into TWDR
	TWDR=data;
	//clear TWINT
	TWCR=(1<<TWINT)|(1<<TWEN);
	//wait for flag to set
	while (!(TWCR & (1<<TWINT)));
	//check status register
	while( (TWSR & 0xF8) != 0x28);
	//increment add for next write operation
	add+=0x01;
}

unsigned char eepromRandomRead(void){
	/*returns the data stored in EEPROM at the prev sent address
	*/
	//sending repeated start condition
	TWCR=0b10100100;      
	//waiting for flag to set
	while(!(TWCR & (1<<TWINT)));
	//checking status register
	while((TWSR & 0xF8)!= 0x10);
	
	//loading SLA+R
	TWDR=0b10100001; 
	//clear TWINT
	TWCR=(1<<TWINT)|(1<<TWEN);
	//waiting for flag to set
	while (!(TWCR & (1<<TWINT)));
	//check status register
	while( (TWSR & 0xF8) != 0x40);
	
	// TWEA not set as we have to send nack
	TWCR = (1<<TWINT)|(1<<TWEN);  
	//waiting for flag to set
	while (!(TWCR & (1<<TWINT)));
	//check status register
	while(((TWSR & 0xF8)!=0x58));
	
	return(TWDR);
}


void i2cStop(void){
	//sending stop conditon
	TWCR=0b10010100;
}
