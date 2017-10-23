#include "ihc_vector.h"

#pragma tmpdata ISRHtmpdata

#pragma interrupt tm_handler nosave=section (".tmpdata")

void tm_handler(void) // timer/serial functions are handled here
{
	static uint8_t led_cache = 0xff, config_found = 0, c_error = 0;
	static int16_t ihc_d_prev = 0;
	int16_t ihc_d_roc;

	if (PIR1bits.RCIF) { // is data from host light link via RS-232 port
		link_count++;
		ibs_stream_file = RCREG;
		if (RCSTAbits.OERR || RCSTAbits.FERR) {
			ibs_stream_file = 0x00; // nulls for data on errors
			RCSTAbits.CREN = FALSE; // clear overrun
			RCSTAbits.CREN = TRUE; // re-enable
			if (c_error++>MAX_C_ERROR)
				c_error = 0;
		} else {
			if (!V.config)
				TXREG = ibs_stream_file; // echo
		}
		if (ibs_stream_file == 0x00) // this is bad data in the stream
			ibs_d = 1; // reset at bad data
		if (ibs_stream_file == CONFIG_CHAR) { // search for configuration stream
			if (++config_found > CONFIG_REPEATS) {
				V.config = TRUE; //
				config_found = 0;
			}
		} else {
			config_found = 0;
		}
		if (ibs_stream_file & 0x80) { // stream data bit 7 set
			ibs_data[ibs_d] = ibs_stream_file & 0x3f;
			ibs_d++; // index to store the data stream
			if (ibs_d > MAX_DATA)
				ibs_d = 1; // reset on overrun
		} else { // stream codes for source parameters
			ibs_d = 1;
			ihc_d = ((ibs_data[1]&0x0f) << 6)+(ibs_data[2]); // convert the 10 bit data from the stream
			ibs_data[0] = ibs_stream_file; // store the stream code
			// parse the stream codes
			switch (ibs_stream_file_prev) {
			case IHC_CODE0: // extraction regulation
				if (++ihc_count[0] > IHC_SAMPLES)
					V.ihc_data0 = FALSE; // in range preset to false
				if ((ihc_d > IHC_CODE0L) && (ihc_d < IHC_CODE0H)) {
					V.ihc_data0 = TRUE; // set range code to true
					ihc_count[0] = 0;
					ihc_d_roc = ihc_d - ihc_d_prev;
					V.ihc_d_abs = (ihc_d_roc < 0 ? (-ihc_d_roc) : ihc_d_roc);
					ihc_d_prev = ihc_d;
					if ((V.ihc_d_abs <= V.fine)) {
						if (V.inreg) FINE_REG = LEDON; // regulation in tight mode
						V.stable = TRUE;
						if (!glitch_count)
							GLITCH_ERROR = LEDOFF;
					} else {
						FINE_REG = LEDOFF; // not in fine regulation
					}
				} else {
					FINE_REG = LEDOFF; // not in fine regulation
				}
				break;
			case IHC_CODE1: // filament voltage
				if (++ihc_count[1] > IHC_SAMPLES)
					V.ihc_data1 = FALSE;
				if ((ihc_d > IHC_CODE1L) && (ihc_d < IHC_CODE1H)) {
					V.ihc_data1 = TRUE;
					ihc_count[1] = 0;
				}
				break;
			case IHC_CODE2: // filament current
				if (++ihc_count[2] > IHC_SAMPLES)
					V.ihc_data2 = FALSE;
				if ((ihc_d > IHC_CODE2L) && (ihc_d < IHC_CODE2H)) {
					V.ihc_data2 = TRUE;
					ihc_count[2] = 0;
				}
				break;
			case IHC_CODE3: // cathode voltage
				if (++ihc_count[3] > IHC_SAMPLES)
					V.ihc_data3 = FALSE;
				if ((ihc_d > IHC_CODE3L) && (ihc_d < IHC_CODE3H)) {
					V.ihc_data3 = TRUE;
					ihc_count[3] = 0;
				}
				break;
			case IHC_CODE4: // cathode current
				V.ibs_block_done = TRUE; // update display now
				if (++ihc_count[4] > IHC_SAMPLES)
					V.ihc_data4 = FALSE;
				if ((ihc_d > IHC_CODE4L) && (ihc_d < IHC_CODE4H)) {
					V.ihc_data4 = TRUE;
					ihc_count[4] = 0;
					if (!V.ihc_data3) {
						if (V.stable && ((glitch_count++) > MAX_GLITCH))
							GLITCH_ERROR = LEDON;
					} else {
						glitch_count = 0;
					}
				}
				break;
			default:
				break;
			}
			ibs_stream_file_prev = ibs_stream_file;
		}
	}

	if (PIR1bits.TMR1IF) { //      Timer1 int handler
		PIR1bits.TMR1IF = FALSE; //      clear int flag
		WriteTimer1(SAMPLEFREQ);
		// aux work thread, nothing for now
		if (!link_ok)
			V.ibs_block_done = TRUE; // update display quickly
	}

	if (INTCONbits.TMR0IF) { //      check timer0 irq time timer
		INTCONbits.TMR0IF = FALSE; //      clear interrupt flag
		WriteTimer0(timer0_off);
		/* some data link housekeeping */
		if (link_count > LINK_COUNT) { // data bytes per led flash time
			link_ok = TRUE;
			link_count = 0;
		} else {
			link_ok = FALSE;
			V.ihc_data0 = V.ihc_data1 = V.ihc_data2 = V.ihc_data3 = V.ihc_data4 = 0;
			FINE_REG = LEDOFF; // no fine regulation
		}

		/* Start Led Blink Code */
		if (V.blink_alt) {
			if (V.blink & 0b00000001) LEDS.out_bits.b0 = !LEDS.out_bits.b0;
			if (V.blink & 0b00000010) LEDS.out_bits.b1 = !LEDS.out_bits.b0;
			if (V.blink & 0b00000100) LEDS.out_bits.b2 = !LEDS.out_bits.b2;
			if (V.blink & 0b00001000) LEDS.out_bits.b3 = !LEDS.out_bits.b2;
			if (V.blink & 0b00010000) LEDS.out_bits.b4 = !LEDS.out_bits.b4;
			if (V.blink & 0b00100000) LEDS.out_bits.b5 = !LEDS.out_bits.b4;
			if (V.blink & 0b01000000) LEDS.out_bits.b6 = !LEDS.out_bits.b6;
			if (V.blink & 0b10000000) LEDS.out_bits.b7 = !LEDS.out_bits.b6;
		} else {
			if (V.blink & 0b00000001) LEDS.out_bits.b0 = !LEDS.out_bits.b0;
			if (V.blink & 0b00000010) LEDS.out_bits.b1 = !LEDS.out_bits.b1;
			if (V.blink & 0b00000100) LEDS.out_bits.b2 = !LEDS.out_bits.b2;
			if (V.blink & 0b00001000) LEDS.out_bits.b3 = !LEDS.out_bits.b3;
			if (V.blink & 0b00010000) LEDS.out_bits.b4 = !LEDS.out_bits.b4;
			if (V.blink & 0b00100000) LEDS.out_bits.b5 = !LEDS.out_bits.b5;
			if (V.blink & 0b01000000) LEDS.out_bits.b6 = !LEDS.out_bits.b6;
			if (V.blink & 0b10000000) LEDS.out_bits.b7 = !LEDS.out_bits.b7;
		}
		if (LEDS.out_byte != led_cache) {
			if (LEDS.out_bits.b0) {
				LED0 = LEDON;
			} else {
				LED0 = LEDOFF;
			}
			//			LED0 = (LEDS.out_bits.b0 ? LEDON : LEDOFF); // this way generates nasty C18 code
			if (LEDS.out_bits.b1) {
				LED1 = LEDON;
			} else {
				LED1 = LEDOFF;
			}
			if (LEDS.out_bits.b2) {
				LED2 = LEDON;
			} else {
				LED2 = LEDOFF;
			}
			if (LEDS.out_bits.b3) {
				LED3 = LEDON;
			} else {
				LED3 = LEDOFF;
			}
			if (LEDS.out_bits.b4) {
				LED4 = LEDON;
			} else {
				LED4 = LEDOFF;
			}
			if (LEDS.out_bits.b5) {
				LED5 = LEDON;
			} else {
				LED5 = LEDOFF;
			}
			if (LEDS.out_bits.b6) {
				LED6 = LEDON;
			} else {
				LED6 = LEDOFF;
			}
			if (LEDS.out_bits.b7) {
				LED7 = LEDON;
			} else {
				LED7 = LEDOFF;
			}
			led_cache = LEDS.out_byte;
		}
		/* End Led Blink Code */
	}
}
#pragma	tmpdata