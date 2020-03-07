#include "ihc_vector.h"

#pragma tmpdata ISRHtmpdata

#pragma interrupt tm_handler nosave=section (".tmpdata")

void tm_handler(void) // timer/serial functions are handled here
{
	static uint8_t c_error = 0;

	if (PIR1bits.RCIF) { // is data from host light link via RS-232 port
		link_count++;
		ibs_stream_file = RCREG;
		if (RCSTAbits.OERR || RCSTAbits.FERR) {
			ibs_stream_file = 0x00; // nulls for data on errors
			RCSTAbits.CREN = FALSE; // clear overrun
			RCSTAbits.CREN = TRUE; // re-enable
			if (c_error++>MAX_C_ERROR) {
				c_error = 0;
				LED1 = LEDON;
			}
		} else {
			/*
			 * process received data stream
			 */
			TXREG = ibs_stream_file; // echo for now
		}
	}

	if (PIR1bits.TMR1IF) { //      Timer1 int handler
		PIR1bits.TMR1IF = FALSE; //      clear int flag
		WriteTimer1(SAMPLEFREQ);
		V.clock_100hz++;
	}

	if (INTCONbits.TMR0IF) { //      check timer0 irq time timer
		INTCONbits.TMR0IF = FALSE; //      clear interrupt flag
		WriteTimer0(timer0_off);
		V.clock_2hz++;
	}
}
#pragma	tmpdata