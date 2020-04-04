// PIC18F1320 Configuration Bit Settings

// 'C' source line config statements
#include <xc.h>

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
#pragma config LVP = OFF         // Low-Voltage ICSP Enable bit (Low-Voltage ICSP DISenabled)

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
 * 1.1 for rev 1.1 PCB
 * 1.2 full CRC for TX and RX
 * 1.3 status led blinker code
 * 1.4 adjust pwm values for new board
 * 1.5 switch to High Voltage chip programming
 * 1.6 convert to xc8 compiler
 * 1.7 sequence mode and error modbus commands
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pic18f1320.h>
#include "ibsmon.h"
#include "ihc_vector.h"
#include "crc.h"

#define BusyUSART( ) (!TXSTAbits.TRMT)

int8_t controller_work(void);
void init_ihcmon(void);
uint8_t init_stream_params(void);

uint16_t req_length = 0;
const uint8_t modbus_cc_mode[] = {0x01, 0x03, 0x01, 0x20, 0x00, 0x01},
modbus_cc_error[] = {0x01, 0x03, 0x01, 0x21, 0x00, 0x02},
modbus_cc_clear[] = {0x01, 0x79, 0x00, 0x00, 0x00, 0x01},
modbus_cc_freset[] = {0x01, 0x78, 0x00, 0x00, 0x00, 0x01},
re20a_mode[] = {0x01, 0x03, 0x02, 0x00, 0x02, 0x39, 0x85},
re20a_error[] = {0x01, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x39, 0x85},
re20a_clear[] = {0x01, 0x79, 0x00, 0x00, 0x00, 0x01, 0x5d, 0xc0},
re20a_freset[] = {0x01, 0x78, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00};

volatile struct V_data V = {
	.blink_lock = 0,
};
volatile uint8_t cc_stream_file, cc_buffer[MAX_DATA]; // half-duplex so we can share the cc_buffer for TX and RX
uint32_t crc_error;
comm_type cstate = CLEAR;
cmd_type modbus_command = G_MODE;
const char *build_date = __DATE__, *build_time = __TIME__, build_version[5] = "1.7";

void SetDCPWM1(uint16_t dutycycle)
{
	union PWMDC DCycle;

	// Save the dutycycle value in the union
	DCycle.lpwm = dutycycle << 6;

	// Write the high byte into CCPR1L
	CCPR1L = DCycle.bpwm[1];

	// Write the low byte into CCP1CON5:4
	CCP1CON = (CCP1CON & 0xCF) | ((DCycle.bpwm[0] >> 2) & 0x30);
}

int8_t controller_work(void)
{
	static uint8_t mcmd = G_MODE;

	switch (cstate) {
	case CLEAR:
		clear_2hz();
		cstate = INIT;
		modbus_command = mcmd++;
		if (mcmd > G_LAST)
			mcmd = G_MODE;
		/*
		 * command specific tx buffer setup
		 */
		switch (modbus_command) {
		case G_ERROR: // error code request
			req_length = modbus_rtu_send_msg((void*) cc_buffer, (const void *) modbus_cc_error, sizeof(modbus_cc_error));
			break;
		case G_MODE: // operating mode request
		default:
			req_length = modbus_rtu_send_msg((void*) cc_buffer, (const void *) modbus_cc_mode, sizeof(modbus_cc_mode));
			break;
		}
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
				TXREG = cc_buffer[V.send_count];
			} while (++V.send_count < req_length);
			while (BusyUSART()); // wait for the last byte
			cstate = RECV;
			clear_500hz();
		}
		break;
	case RECV:
		if (get_500hz(FALSE) > TDELAY) {
			uint16_t c_crc, c_crc_rec;

			DE = 0;
			RE_ = 0;

			/*
			 * check received response data for size and format for each command sent
			 */
			switch (modbus_command) {
			case G_ERROR: // check for controller error codes
				req_length = sizeof(re20a_error);
				if ((V.recv_count >= req_length) && (cc_buffer[0] == 0x01) && (cc_buffer[1] == 0x03)) {
					uint16_t temp;
					c_crc = crc16(cc_buffer, req_length - 2);
					c_crc_rec = (uint16_t) ((uint16_t) cc_buffer[req_length - 2] << (uint16_t) 8) | ((uint16_t) cc_buffer[req_length - 1] & 0x00ff);
					if (c_crc == c_crc_rec) {
						if ((temp = (cc_buffer[3] << 8) +(cc_buffer[4]&0xff))) {
							NOP();
							RE20A_ERROR = ON;
							set_led_blink(ERROR_BLINKS);
						} else {
							RE20A_ERROR = OFF;
						}
					}
					cstate = CLEAR;
				} else {
					if (get_500hz(FALSE) > RDELAY) {
						cstate = CLEAR;
						RE20A_ERROR = OFF;
						mcmd = G_MODE;
					}
				}
				break;
			case G_MODE: // check for current operating mode
			default:
				req_length = sizeof(re20a_mode);
				if ((V.recv_count >= req_length) && (cc_buffer[0] == 0x01) && (cc_buffer[1] == 0x03)) {
					uint8_t temp;
					static uint8_t volts = CC_OFFLINE;

					c_crc = crc16(cc_buffer, req_length - 2);
					c_crc_rec = (uint16_t) ((uint16_t) cc_buffer[req_length - 2] << (uint16_t) 8) | ((uint16_t) cc_buffer[req_length - 1] & 0x00ff);

					if (c_crc == c_crc_rec) {
						if ((temp = cc_buffer[4])) {
							set_led_blink(temp);
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
							set_led_blink(BON);
							volts = CC_DEACT;
						}
					} else {
						crc_error++;
						set_led_blink(BOFF);
					}
					V.pwm_volts = volts;
					SetDCPWM1(V.pwm_volts);
					cstate = CLEAR;
				} else {
					if (get_500hz(FALSE) > RDELAY) {
						set_led_blink(BOFF);
						cstate = CLEAR;
						V.pwm_volts = CC_OFFLINE;
						SetDCPWM1(V.pwm_volts);
						mcmd = G_MODE;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

void init_ihcmon(void)
{
	uint16_t tmp;
	V.boot_code = FALSE;
	BOOT_FLAG = FALSE;
	if (RCON != 0b0011100)
		V.boot_code = TRUE;

	if (STKPTRbits.STKFUL || STKPTRbits.STKUNF) {
		V.boot_code = TRUE;
		STKPTRbits.STKFUL = 0;
		STKPTRbits.STKUNF = 0;
	}

	if (V.boot_code)
		BOOT_FLAG = TRUE;

	ADCON1 = 0x7F; // all digital, no ADC
	/* interrupt priority ON */
	RCONbits.IPEN = 1;
	/* define I/O ports */
	IBSPORTA = IBSPORT_IOA;
	IBSPORTB = IBSPORT_IOB;
	INTCON2bits.RBPU = 0; // enable weak pull-ups, mainly for receive serial when RS485 Rx transceiver is off.

	LED1 = OFF;
	RE20A_ERROR = OFF;
	V.clock_blinks = 0;
	set_led_blink(BOFF);
	//OpenTimer0(TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_64);
	T0CON = 0b10000101;
	tmp = TIMERFAST >> 8;
	TMR0H = tmp;
	tmp = TIMERFAST & 0xFF;
	TMR0L = tmp;
	//OpenTimer1(TIMER_INT_ON & T1_16BIT_RW & T1_SOURCE_INT & T1_PS_1_4 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF);
	T1CON = 0b10100101;
	tmp = SAMPLEFREQ >> 8;
	TMR1H = tmp;
	tmp = SAMPLEFREQ & 0xFF;
	TMR1L = tmp;

	CCP1CON |= 0b00001100;
	T2CONbits.TMR2ON = 0;
	PR2 = PWMFREQ;
	T2CONbits.TMR2ON = 1;
	V.pwm_volts = CC_OFFLINE;
	SetDCPWM1(V.pwm_volts);

	/* MODBUS data line UART1 */
	TXSTA = 0;
	RCSTA = 0;
	PIE1bits.RCIE = 1;
	PIE1bits.TXIE = 0;
	TXSTAbits.SYNC = 0;
	RCSTAbits.CREN = 1;
	PIR1bits.TXIF = 0;
	PIR1bits.RCIF = 0;
	BAUDCTLbits.BRG16 = 0; // 40MHz osc HS/PLL 9600 baud
	TXSTAbits.BRGH = 0;
	SPBRGH = 0;
	SPBRG = 64;
	TXSTAbits.TXEN = 1;
	RCSTAbits.SPEN = 1;

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
