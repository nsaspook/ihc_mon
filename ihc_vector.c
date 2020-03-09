#include "ihc_vector.h"

#pragma tmpdata ISRHtmpdata

#pragma interrupt tm_handler nosave=section (".tmpdata")

void tm_handler(void) // timer/serial functions are handled here
{
	static uint8_t c_error = 0;

	if (PIR1bits.RCIF) { // is data from host light link via RS-232 port
		cc_stream_file = RCREG;
		if (RCSTAbits.OERR || RCSTAbits.FERR) {
			cc_stream_file = 0x00; // nulls for data on errors
			RCSTAbits.CREN = FALSE; // clear overrun
			RCSTAbits.CREN = TRUE; // re-enable
			if (c_error++>MAX_C_ERROR) {
				c_error = 0;
				//                LED1 = LEDON;
			}
		} else {
			/*
			 * process received data stream
			 */
			cc_buffer[V.recv_count] = cc_stream_file;
			if (++V.recv_count >= MAX_DATA)
				V.recv_count = 0; // reset buffer position
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

	if (PIR1bits.TMR2IF) { //      check timer0 irq time timer
		PIR1bits.TMR2IF = FALSE; //      clear interrupt flag
	}

	if (PIR1bits.CCP1IF) { //      check timer0 irq time timer
		PIR1bits.CCP1IF = FALSE; //      clear interrupt flag
	}

}
#pragma	tmpdata

void clear_2hz(void)
{
	INTCONbits.GIEH = 0;
	V.clock_2hz = 0;
	INTCONbits.GIEH = 1;
}

void clear_100hz(void)
{
	INTCONbits.GIEH = 0;
	V.clock_100hz = 0;
	INTCONbits.GIEH = 1;
}

uint32_t get_2hz(uint8_t mode)
{
	static uint32_t tmp;

	if (mode)
		return tmp;

	INTCONbits.GIEH = 0;
	tmp = V.clock_2hz;
	INTCONbits.GIEH = 1;
	return tmp;
}

uint32_t get_100hz(uint8_t mode)
{
	static uint32_t tmp;

	if (mode)
		return tmp;

	INTCONbits.GIEH = 0;
	tmp = V.clock_100hz;
	INTCONbits.GIEH = 1;
	return tmp;
}
