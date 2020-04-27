
void setup(){

    //General interrupts enable bit clear (Status Register)
    SREG &= ~0x80;

    //Disable power-saving feature (enables Timer 2)
    PPR &= ~0x40;

    //Compare A interrupt enable
    TIMSK2 |= 0x02; 

    //Clear timer value on compare match mode (CTC mode)
    TCCR2A = 0x02;
    TCCR2B &= ~0x08;

    //Prescaler /64 clk source
    TCCR2B |= 0x04;

    //Comparator A register comparator limit (overflow value)
    OCR2A = 61; //62 - 1

    //General interrupt enable bit set (Status Register)
    SREG |= 0x80;

    //62.5 KHz Clk Source for Timer 2
    //62 counts compare match generates interrupt
    //Interrupt rate = 1 kHz



    //Your setup code here!


}

void loop(){
    //Non-blocking (interrupt-driven flags polling)

    
}


ISR(TIMER2_COMPA_vect){ //Timer comparison interrupt
    //Interrupt code here
    //Modify interupt flags here
}