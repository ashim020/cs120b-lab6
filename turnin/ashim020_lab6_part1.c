/*	Author: Andrew Shim
 *  	Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: Three blinking lights on PB2 - PB0 blink in ascending order (PB0, PB1, PB2, PB0, PB1, ...), changing lights every second.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  	Demo Link:
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, ONE, TWO, THREE} state;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet (unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void Tick(){
    switch(state){ //State Transitions
        case Start:
            state = ONE;
            break;

        case ONE:
            state = TWO;
            break;

        case TWO:
            state = THREE;
            break;

	case THREE:
	    state = ONE;
	    break;

        default:
            state = Start;
            break;
    }

    switch(state){ //State Actions
        case Start:
            break;

        case ONE:
            PORTB = 0x01;
            break;

        case TWO:
            PORTB = 0x02;
            break;

        case THREE:
            PORTB = 0x04;
            break;

        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    TimerSet(1000);
    TimerOn();

    while (1) {
        Tick();
        while(!TimerFlag) {}; //Wait 1 second
        TimerFlag = 0;
    }
    return 1;
}
