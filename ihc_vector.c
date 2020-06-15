#include "ihc_vector.h"

void __interrupt() tm_handler(void) // timer/serial functions are handled here
{
	static uint8_t tick60 = 0, tickwidth = 0;
	uint16_t tmp;

	if (PIR1bits.TMR1IF) { //      Timer1 int handler
		PIR1bits.TMR1IF = FALSE; //      clear int flag
		tmp = SAMPLEFREQ >> 8;
		TMR1H = tmp;
		tmp = SAMPLEFREQ & 0xFF;
		TMR1L = tmp;
		if (++tickwidth > TICKWIDTH) {
			tickwidth = 0;
			ANA_SIG = 0;
			LED0 = 1;
			LED1 = 0;
		}
	}

	if (INTCONbits.TMR0IF) { //      check timer0 irq time timer
		INTCONbits.TMR0IF = FALSE; //      clear interrupt flag
		tmp = TIMERFAST >> 8;
		TMR0H = tmp;
		tmp = TIMERFAST & 0xFF;
		TMR0L = tmp;
		if (++tick60 > TICK60) {
			tick60 = 0;
			tickwidth = 0;
			ANA_SIG = 1;
			LED0 = 0;
			LED1 = 1;
			CLOCK=~CLOCK; 
			PIR1bits.TMR1IF = FALSE; //      clear int flag
			tmp = SAMPLEFREQ >> 8;
			TMR1H = tmp;
			tmp = SAMPLEFREQ & 0xFF;
			TMR1L = tmp;
		}
		LED = ~LED;
	}
}
