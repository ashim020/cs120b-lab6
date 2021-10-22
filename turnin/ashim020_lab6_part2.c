/*	Author: Andrew Shim
 *  	Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: Three blinking lights on PB2 - PB0 blink in ascending order (PB0, PB1, PB2, PB0, PB1, ...), changing lights every 300 ms. 
                          Pressing a button connected to PA0 will pause the sequence on whatever light is currently lit. Pressing the button again
                          will reset the sequence.
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

enum States {Start, ONE, TWO, THREE, BUTTON, WAIT} state;

unsigned char alt = 0x00;
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

void TimerISR(){
	TimerFlag = 1;
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
	    if (PINA == 0xFE) {
	        state = BUTTON;
	    } else {
                state = TWO;
	    }
            break;

        case TWO:
            if (PINA == 0xFE) {
	        state = BUTTON;
	    } else {
	        if (alt) {
		    state = ONE;
		} else {
		    state = THREE;
		}
	    }
            break;

	case THREE:
	    if (PINA == 0xFE) {
		state = BUTTON;
	    } else {
		state = TWO;
	    }
	    break;

	case BUTTON:
	    if (PINA == 0xFE) {
		state = BUTTON;
	    } else {
		state = WAIT;
	    }
	    break;

	case WAIT:
	    if (PINA == 0xFE) {
		state = ONE;
	    } else {
		state = WAIT;
	    }
	    break;

        default:
            state = Start;
            break;
    }

    switch(state){ //State Actions
        case Start:
            break;

        case ONE:
	    alt = 0x00;
            PORTB = 0x01;
            break;

        case TWO:
            PORTB = 0x02;
            break;

        case THREE:
	    alt = 0x01;
            PORTB = 0x04;
            break;

	case BUTTON:
	    break;

	case WAIT:
	    break;

        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;    
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    TimerSet(300);
    TimerOn();

    while (1) {
        Tick();
        while(!TimerFlag) {}; //Wait 1 second
        TimerFlag = 0;
    }
}
