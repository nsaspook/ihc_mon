// PIC18F1320 Configuration Bit Settings

// 'C' source line config statements

#include <p18f1320.h>

// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (clock frequency = 4 x FOSC1))
#pragma config FSCM = ON        // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bit (Brown-out Reset enabled)
// BORV = No Setting

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled, RA5 input pin disabled)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Low-Voltage ICSP Enable bit (Low-Voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = ON         // Code Protection bit (Block 0 (00200-000FFFh) code-protected)
#pragma config CP1 = ON         // Code Protection bit (Block 1 (001000-001FFFh) code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (00200-000FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (001000-001FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (00200-000FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (001000-001FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)





/*
 * Driver software Rover Elite charge mode monitor
 * Runs on a PIC18F1320 
 *	nsaspook@nsaspook.com
 * cpu clock 10mhz external
 * Version
 * 1.0 Rover Elite SR485 controller status monitor
 */

#include <p18f1320.h>
#include <timers.h>
#include <pwm.h>
#include <stdlib.h>
#include <usart.h>
#include <stdio.h>
#include <EEP.h>
#include "ibsmon.h"
#include "ihc_vector.h"
#include "crc.h"

void tm_handler(void);
int8_t controller_work(void);
uint8_t do_config(void);
void init_ihcmon(void);
uint8_t init_stream_params(void);
uint8_t crc_match(uint8_t, uint8_t, uint16_t);

#pragma udata
const rom uint8_t modbus_cc_mode[] = {0x01, 0x03, 0x01, 0x20, 0x00, 0x01, 0x84, 0x3c},
re20a_mode[] = {0x01, 0x03, 0x02, 0x00, 0x02, 0x39, 0x85};
volatile struct V_data V;
volatile uint8_t cc_stream_file, cc_stream_file_prev = 0, cc_buffer[MAX_DATA];
#pragma udata access ACCESSBANK
near uint32_t crc_error;
volatile uint16_t timer0_off = TIMEROFFSET;
comm_type cstate = CLEAR;
const rom uint8_t *build_date = __DATE__, *build_time = __TIME__, build_version[5] = "1.0";

#pragma code tm_interrupt = 0x8

void tm_int(void)
{
	_asm goto tm_handler _endasm
}
#pragma code

uint8_t crc_match(uint8_t upper, uint8_t lower, uint16_t crc)
{
	if ((upper == (crc >> 8) & 0x00ff) && (lower == (crc & 0x00ff)))
		return TRUE;
	return FALSE;
}

int8_t controller_work(void)
{
	switch (cstate) {
	case CLEAR:
		clear_2hz();
		cstate = INIT;
		break;
	case INIT:
		if (get_2hz(FALSE) > QDELAY) {
#ifdef LOCAL_ECHO
			RE_ = 0; // keep receiver active
#else
			RE_ = 1; // shutdown receiver
#endif
			DE = 1;
			V.send_count = 0;
			V.recv_count = 0;
			cstate = SEND;
			clear_500hz();
		}
		break;
	case SEND:
		if (get_500hz(FALSE) > TDELAY) {
			do {
				while (BusyUSART()); // wait for each byte
				TXREG = modbus_cc_mode[V.send_count];
			} while (++V.send_count < sizeof(modbus_cc_mode));
			while (BusyUSART()); // wait for the last byte
			cstate = RECV;
			clear_500hz();
		}
		break;
	case RECV:
		if (get_500hz(FALSE) > TDELAY) {
			DE = 0;
			RE_ = 0;
			/*
			 * check received data for size and format
			 */
			if ((V.recv_count >= sizeof(re20a_mode)) && (cc_buffer[0] == 0x01) && (cc_buffer[1] == 0x03)) {
				uint8_t temp;
				uint16_t c_crc, c_crc_rec;
				static uint8_t volts = CC_OFFLINE;

				c_crc = crc16(cc_buffer, 5);
				c_crc_rec = ((uint16_t) (cc_buffer[5] << 8)) | ((uint16_t) cc_buffer[6]);

				if (c_crc == c_crc_rec) {
					if ((temp = cc_buffer[4])) {
						LED1 = ~LED1;
						switch (temp) {
						case 1:
							volts = CC_ACT;
							break;
						case 2:
							volts = CC_MPPT;
							break;
						case 3:
							volts = CC_EQUAL;
							break;
						case 4:
							volts = CC_BOOST;
							break;
						case 5:
							volts = CC_FLOAT;
							break;
						case 6:
							volts = CC_LIMIT;
							break;
						default:
							volts = CC_ACT;
							break;
						}
					} else {
						LED1 = ON;
						volts = CC_DEACT;
					}
				} else {
					crc_error++;
					LED1 = OFF;
				}
				V.pwm_volts = volts;
				SetDCPWM1(V.pwm_volts);
				cstate = CLEAR;
			} else {
				if (get_500hz(FALSE) > RDELAY) {
					LED1 = OFF;
					cstate = CLEAR;
					V.pwm_volts = CC_OFFLINE;
					SetDCPWM1(V.pwm_volts);
				}
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

uint8_t do_config(void)
{
	INTCONbits.GIEH = 0;
	if (Read_b_eep(0) == '?') { // use default options
		Write_b_eep(0, 'D'); // write into EEPROM
	} else { // set FINE options.
		Write_b_eep(0, '?'); // write into EEPROM
	}
	Busy_eep();
	INTCONbits.GIEH = 1;
	V.config = FALSE;
	return 0;
}

void init_ihcmon(void)
{
	ADCON1 = 0x7F; // all digital, no ADC
	/* interrupt priority ON */
	RCONbits.IPEN = 1;
	/* define I/O ports */
	IBSPORTA = IBSPORT_IOA;
	IBSPORTB = IBSPORT_IOB;
	INTCON2bits.RBPU = 0; // enable weak pull-ups, mainly for receive serial when RS485 Rx transceiver is off.

	LED1 = LEDON;
	FINE_REG = LEDON; // debug
	timer0_off = TIMERFAST; // blink fast
	OpenTimer0(TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_64);
	WriteTimer0(timer0_off);
	OpenTimer1(TIMER_INT_ON & T1_16BIT_RW & T1_SOURCE_INT & T1_PS_1_4 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF);
	WriteTimer1(SAMPLEFREQ);

	OpenPWM1(PWMFREQ);
	V.pwm_volts = CC_OFFLINE;
	SetDCPWM1(V.pwm_volts);
	SetOutputPWM1(SINGLE_OUT, PWM_MODE_1);

	/* Light-link data input */
	OpenUSART(USART_TX_INT_OFF &
		USART_RX_INT_ON &
		USART_ASYNCH_MODE &
		USART_EIGHT_BIT &
		USART_CONT_RX &
		USART_BRGH_LOW, 64); // 40MHz osc HS/PLL 9600 baud
	BAUDCTLbits.BRG16 = 0;
	TXSTAbits.BRGH = 0;
	SPBRGH = 0;
	SPBRG = 64;

	INTCONbits.TMR0IE = 1; // enable int
	INTCON2bits.TMR0IP = 1; // make it high level
	PIE1bits.TMR1IE = 1; // enable int
	IPR1bits.TMR1IP = 1; // make it high level

	init_stream_params();

	/* Enable all high priority interrupts */
	INTCONbits.GIEH = 1;
}

uint8_t init_stream_params(void)
{
	V.config = FALSE;
	return 0;
}

void main(void)
{
	init_ihcmon();
	/* Loop forever */
	while (TRUE) { // busy work
		controller_work();
	}
}
