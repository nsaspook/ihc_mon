#include "ihc_vector.h"

static void led_blink(void);

void __interrupt() tm_handler(void) // timer/serial functions are handled here
{
	static uint8_t c_error = 0;
	uint16_t tmp;

	if (PIR1bits.RCIF) { // is data from RS485 port
		cc_stream_file = RCREG;
		if (RCSTAbits.OERR || RCSTAbits.FERR) {
			cc_stream_file = 0x00; // nulls for data on errors
			RCSTAbits.CREN = FALSE; // clear overrun
			RCSTAbits.CREN = TRUE; // re-enable
			if (c_error++>MAX_C_ERROR) {
				c_error = 0;
			}
		} else {
			/*
			 * process received charge controller data stream
			 */
			cc_buffer[V.recv_count] = cc_stream_file;
			if (++V.recv_count >= MAX_DATA)
				V.recv_count = 0; // reset buffer position
		}
	}

	if (PIR1bits.TMR1IF) { //      Timer1 int handler
		PIR1bits.TMR1IF = FALSE; //      clear int flag
		tmp = SAMPLEFREQ >> 8;
		TMR1H = tmp;
		tmp = SAMPLEFREQ & 0xFF;
		TMR1L = tmp;
		V.clock_500hz++;
	}

	if (INTCONbits.TMR0IF) { //      check timer0 irq time timer
		INTCONbits.TMR0IF = FALSE; //      clear interrupt flag
		tmp = TIMERFAST >> 8;
		TMR0H = tmp;
		tmp = TIMERFAST & 0xFF;
		TMR0L = tmp;
		V.clock_2hz++;
		V.clock_blinks++;
		led_blink();
	}

	if (PIR1bits.TMR2IF) { //      check timer0 irq time timer
		PIR1bits.TMR2IF = FALSE; //      clear interrupt flag
	}

	if (PIR1bits.CCP1IF) { //      check timer0 irq time timer
		PIR1bits.CCP1IF = FALSE; //      clear interrupt flag
	}

}

void clear_2hz(void)
{
	INTCONbits.GIEH = 0;
	V.clock_2hz = 0;
	INTCONbits.GIEH = 1;
}

void clear_500hz(void)
{
	INTCONbits.GIEH = 0;
	V.clock_500hz = 0;
	INTCONbits.GIEH = 1;
}

uint32_t get_2hz(uint8_t mode)
{
	static uint32_t tmp = 0;

	if (mode)
		return tmp;

	INTCONbits.GIEH = 0;
	tmp = V.clock_2hz;
	INTCONbits.GIEH = 1;
	return tmp;
}

uint32_t get_500hz(uint8_t mode)
{
	static uint32_t tmp = 0;

	if (mode)
		return tmp;

	INTCONbits.GIEH = 0;
	tmp = V.clock_500hz;
	INTCONbits.GIEH = 1;
	return tmp;
}

/*
 * link condition status server via blinking led
 * runs in timer 0 ISR @ 2Hz
 */
static void led_blink(void)
{
	// range checks
	if (V.num_blinks == 255) {
		LED1 = ON;
		V.clock_blinks = 0;
		V.blink_lock = 0;
		return;
	}
	if (!V.num_blinks || V.num_blinks > MAX_BLINKS) {
		LED1 = OFF;
		V.clock_blinks = 0;
		V.blink_lock = 0;
		return;
	}

	// time spacing and blink counter
	if (V.clock_blinks > BLINK_SPACE) {
		if ((BLINK_SPACE + (V.num_blinks << 1)) <= V.clock_blinks) {
			V.clock_blinks = 0;
			LED1 = OFF;
			V.blink_lock = 0;
		} else {
			LED1 = ~LED1;
		}
	}
}

/*
 * set the number of blinks variable from mainline code
 */
void set_led_blink(uint8_t blinks)
{
	if (V.blink_lock)
		return;

	if (blinks > MAX_BLINKS && (blinks != 255))
		blinks = 0;

	INTCONbits.GIEH = 0;
	V.blink_lock = 1;
	V.num_blinks = blinks;
	INTCONbits.GIEH = 1;
}
