volatile unsigned int timeSync = 0;


void setup(){

    /*
	=============
	TIMER 1 SETUP
	=============
	*/

	//General interrupts enable bit clear (Status Register)
	SREG &= ~0x80;

	//Disable power-saving feature (enables Timer 1)
	PRR &= ~0x80;

	//Compare A interrupt enable
	TIMSK1 |= 0x02; 	

	//Clear timer value on compare match mode (CTC mode)	
	TCCR1A  = 0x00;
	TCCR1B |= 0x08;

	//Prescaler /8 clk source (higher resolution 16-bit timer)
	TCCR1B |= 0x02;

	//Comparator A register limit (overflow value)
	//Comparator set to 249 counts (250 - 1)
	OCR1A = 249;

	//General interrupt enable bit set (Status Register)
	//SREG |= 0x80;	 //Won't enable here, as Timer 2 setup is next




    /*
    =============
    TIMER 2 SETUP
    =============
    */

    //General interrupts enable bit clear (Status Register)
    SREG &= ~0x80;

    //Disable power-saving feature (enables Timer 2)
    PRR &= ~0x40;

    //Compare A interrupt enable
    TIMSK2 |= 0x02; 

    //Clear timer value on compare match mode (CTC mode)
    TCCR2A = 0x02;
    TCCR2B &= ~0x08;

    //Prescaler /64 clk source
    TCCR2B |= 0x04;

    //Comparator A register comparator limit (overflow value)
    OCR2A = 249; //250 - 1

    //General interrupt enable bit set (Status Register)
    SREG |= 0x80;

    //62.5 KHz Clk Source for Timer 2
    //62 counts compare match generates interrupt
    //Interrupt rate = 1 kHz



    //Your setup code here!





}

void loop(){
    //Non-blocking (interrupt-driven flags polling)

    
    //Timer synchronization 
    timeSync = 0;
    while(timeSync < 1){
        ;
    }
}


//TIMER 2 used as system clock
ISR(TIMER2_COMPA_vect){ //Timer comparison interrupt
    //Interrupt code here
    //Modify interupt flags here



    //Timer synchronization
    timeSync = 1;
}



//TIMER 1 used for motor control
ISR(TIMER1_COMPA_vect){
    //Interrupt code here
    //Modify interupt flags here


}
