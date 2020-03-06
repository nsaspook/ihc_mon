
// PIC18F1320 Configuration Bit Settings

#include <p18f1320.h>

// CONFIG1H
#pragma config OSC = ECIO       // Oscillator Selection bits (Ext oscillator, port function on RA6)
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
#pragma config LVP = OFF        // Low-Voltage ICSP Enable bit (Low-Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = ON        // Code Protection bit (Block 0 (00200-000FFFh) not code-protected)
#pragma config CP1 = ON        // Code Protection bit (Block 1 (001000-001FFFh) not code-protected)

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
 * Driver software IBS IHC source monitor
 * Runs on a PIC18F1320 
 *	nsaspook@nsaspook.com
 * cpu clock 10mhz external
 * Version
 * 0.1  config chip to read the data stream
 * 0.2  Alpha test version, move to external 10mhz clock for stable 57600 baud timing
 * 0.3  Beta test version
 * 0.4  Adjust comm error and code settings.
 * 0.5  Add Glitch error for red led instead of comm error
 * 0.6  Clean up Glitch code, open filament data limits and code style fixes
 * 0.7	refactor names and functions
 * 1.0 Rover Elite SR485 controller status monitor
 */

#include <p18f1320.h>
#include <timers.h>
#include <stdlib.h>
#include <usart.h>
#include <stdio.h>
#include <EEP.h>
#include "ibsmon.h"
#include "blinker.h"

void tm_handler(void);
int16_t display_work(void);
uint8_t do_config(void);
void init_ihcmon(void);
uint8_t init_stream_params(void);

#pragma udata
volatile struct V_data V;
volatile union Obits2 LEDS;
volatile uint8_t ibs_stream_file, ibs_stream_file_prev = 0;
volatile int16_t ihc_d;
#pragma udata access ACCESSBANK
volatile uint16_t timer0_off = TIMEROFFSET, ibs_data[MAX_DATA] = {0}, link_count = 0;
volatile uint8_t ihc_count[MAX_PARAMS] = {0}, link_ok = FALSE, glitch_count = 0;
volatile int16_t ibs_d = 1;
near uint16_t blink_speed;

const rom uint8_t *build_date = __DATE__, *build_time = __TIME__, build_version[5] = "0.7";

#pragma code tm_interrupt = 0x8

void tm_int(void)
{
	_asm goto tm_handler _endasm
}
#pragma code

/* this is the two color red/green HID controller */
int16_t display_work(void)
{
	if (V.ibs_block_done) {
		if (GLITCH_ERROR == LEDON) {
			blink_led(0, OFF, OFF); // LED RED and STEADY
			blink_led(1, ON, OFF);
		}
		if ((V.ihc_data0 & V.ihc_data1 & V.ihc_data2 & V.ihc_data3 & V.ihc_data4) && (V.ihc_d_abs <= IHC_CODE0_TUNE)) { // all good and in rough regulation
			// IHC Source OK, ALL GREEN and steady, ihc_data[0] is the key parameter
			blink_led(0, ON, OFF); // led #,on/off, blink
			blink_led(1, OFF, OFF); //     DISPLAY LEDS
			blink_led(2, ON, OFF); // [0..1]Cath V  X  X Cath I [4..5]
			blink_led(3, OFF, OFF); // [2..3]Fila V  X  X Fila I [6..7]
			blink_led(4, ON, OFF); //               X  X
			blink_led(5, OFF, OFF); //    Glitch     X  X Regulation Fine Mode
			blink_led(6, ON, OFF);
			blink_led(7, OFF, OFF);
			V.inreg = TRUE; // tighten the limits when in regulation
		} else {
			V.inreg = FALSE;
			blink_speed = TIMERFAST;
			// IHC Source out of regulation or IHC parameters out of range
			if (V.ihc_data3) { // green and blinking if this is IN range
				blink_led(0, ON, ON);
				blink_led(1, OFF, OFF);
				blink_speed -= 2500; // speed feedback
			} else { // red and blinking if this is OUT of range
				blink_led(0, OFF, ON);
				blink_led(1, ON, OFF);
			}
			if (V.ihc_data4) {
				blink_led(4, ON, ON);
				blink_led(5, OFF, OFF);
				blink_speed -= 2500;
			} else {
				blink_led(4, OFF, ON);
				blink_led(5, ON, OFF);
			}
			if (V.ihc_data1) {
				blink_led(2, ON, ON);
				blink_led(3, OFF, OFF);
				blink_speed -= 2500;
			} else {
				blink_led(2, OFF, ON);
				blink_led(3, ON, OFF);
			}
			if (V.ihc_data2) {
				blink_led(6, ON, ON);
				blink_led(7, OFF, OFF);
				blink_speed -= 2500;
			} else {
				blink_led(6, OFF, ON);
				blink_led(7, ON, OFF);
			}
			INTCONbits.GIEH = 0;
			timer0_off = blink_speed;
			INTCONbits.GIEH = 1;
		}
		V.ibs_block_done = FALSE;
		if ((!V.ihc_data0 & !V.ihc_data1 & !V.ihc_data2 & !V.ihc_data3 & !V.ihc_data4)) {
			GLITCH_ERROR = LEDOFF;
			V.stable = FALSE;
		}
	}
	return 0;
}

uint8_t do_config(void)
{
	INTCONbits.GIEH = 0;
	if (Read_b_eep(0) == '?') { // use default options
		V.fine = IHC_CODE0_FINE;
		Write_b_eep(0, 'D'); // write into EEPROM
	} else { // set FINE options.
		V.fine = IHC_CODE0_VFINE;
		Write_b_eep(0, '?'); // write into EEPROM
	}
	Busy_eep();
	INTCONbits.GIEH = 1;
	V.config = FALSE;
	GLITCH_ERROR = LEDOFF;
	return V.fine;
}

void init_ihcmon(void)
{
	ADCON1 = 0x7F; // all digital, no ADC
	/* interrupt priority ON */
	RCONbits.IPEN = 1;
	/* define I/O ports */
	IBSPORTA = IBSPORT_IOA;
	IBSPORTB = IBSPORT_IOB;

	LED0 = LEDON; // preset all LEDS
	LED1 = LEDON;
	LED2 = LEDON;
	LED3 = LEDON;
	LED4 = LEDON;
	LED5 = LEDON;
	LED6 = LEDON;
	LED7 = LEDON;
	FINE_REG = LEDON; // will stay ON if a bad data stream in present when booted
	GLITCH_ERROR = LEDON;
	Blink_Init();
	timer0_off = TIMERFAST; // blink fast
	OpenTimer0(TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_64); // led blinker
	WriteTimer0(timer0_off); //	start timer0 at ~1/2 second ticks
	OpenTimer1(TIMER_INT_ON & T1_16BIT_RW & T1_SOURCE_INT & T1_PS_1_4 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF); // aux work thread
	WriteTimer1(SAMPLEFREQ);
	/* Light-link data input */
	COMM_ENABLE = FALSE; // for PICDEM4 onboard RS-232, not used on custom board
	OpenUSART(USART_TX_INT_OFF &
		USART_RX_INT_ON &
		USART_ASYNCH_MODE &
		USART_EIGHT_BIT &
		USART_CONT_RX &
		USART_BRGH_HIGH, 259); // 10mhz osc HS		9600 baud
	BAUDCTLbits.BRG16 = 1;
	TXSTAbits.BRGH = 1;
	SPBRGH = 0;
	SPBRG = 259;
	/*      work int thread setup */
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
	/* setup the IHC stream parser */
	V.ibs_block_done = FALSE;
	V.inreg = FALSE;
	V.config = FALSE;
	V.fine = IHC_CODE0_FINE;
	if (Read_b_eep(0) == '?') V.fine = IHC_CODE0_VFINE;
	return V.fine;
}

void main(void)
{
	init_ihcmon();
	/* Loop forever */
	while (TRUE) { // busy work
		display_work(); // Show the status of the IHC controller and source
		if (V.config)
			do_config();
	}
}
