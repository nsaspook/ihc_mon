#include "ihc_vector.h"

volatile uint8_t tw;

void __interrupt() tm_handler(void) // timer functions are handled here
{
	static uint8_t tick60 = 0, tickwidth = 0;
	uint16_t tmp;

	if (PIR1bits.TMR1IF) { //      Timer1 int handler
		PIR1bits.TMR1IF = false; //      clear int flag
		tmp = SAMPLEFREQ >> 8;
		TMR1H = tmp;
		tmp = SAMPLEFREQ & 0xFF;
		TMR1L = tmp;
		if (++tickwidth > tw) { // pulse width timer trigger
			tickwidth = 0;
			ANA_SIG = 0;
			LED0 = 1;
			LED1 = 0;
		}
	}

	if (INTCONbits.TMR0IF) { //      check timer0 irq time timer
		INTCONbits.TMR0IF = false; //      clear interrupt flag
		tmp = TIMERFAST >> 8;
		TMR0H = tmp;
		tmp = TIMERFAST & 0xFF;
		TMR0L = tmp;
		if (++tick60 > TICK60) { // 60 second tick trigger
			tick60 = 0;
			tickwidth = 0;
			ANA_SIG = 1;
			LED0 = 0;
			LED1 = 1;
			CLOCK = ~CLOCK;
			PIR1bits.TMR1IF = false; // clear int flag, reset trigger for pulse width timer
			tmp = SAMPLEFREQ >> 8;
			TMR1H = tmp;
			tmp = SAMPLEFREQ & 0xFF;
			TMR1L = tmp;
		}
		LED = ~LED; // on-board led flasher
	}
}
