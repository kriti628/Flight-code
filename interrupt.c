void initInterrupt(void){
	//setting to generate interrupt request at rising edge
	EICRA = (1<<ISC20)|(1<<ISC21)|(1<<ISC30)|(1<<ISC31);
	//setting to generate interrupt request when logic changes
	EICRB = (1<<ISC40)|(1<<ISC50)|(1<<ISC60)|(1<<ISC70);
	//enabling external interrupts
	EIMSK = (1<<INT2)|(1<<INT3)|(1<<INT4)|(1<<INT5)|(1<<INT6)|(1<<INT7);
}
