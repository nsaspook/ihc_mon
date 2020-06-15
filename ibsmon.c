// PIC18F1320 Configuration Bit Settings

// 'C' source line config statements
#include <xc.h>

// CONFIG1H
#pragma config OSC = HSPLL         // Oscillator Selection bits (HS oscillator,(clock frequency = FOSC1 * 4))
#pragma config FSCM = ON        // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset enabled)
// BORV = No Setting

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled, RA5 input pin disabled)

// CONFIG4L
#pragma config STVR = OFF        // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Low-Voltage ICSP Enable bit (Low-Voltage ICSP DISenabled)

// CONFIG5L
#pragma config CP0 = OFF         // Code Protection bit (Block 0 (00200-000FFFh) code-protected)
#pragma config CP1 = OFF         // Code Protection bit (Block 1 (001000-001FFFh) code-protected)

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
 * 60 second timer pulse
 * 1.0
 */

#include "ibsmon.h"

void init_tick60(void);
extern volatile uint8_t tw;

const char *build_date = __DATE__, *build_time = __TIME__, build_version[5] = "1.0";

void init_tick60(void)
{
	uint16_t tmp;

	ADCON1 = 0x7F; // all digital, no ADC
	INTCON = 0;
	INTCON2 = 0;
	PIE1 = 0;
	/* interrupt priority ON */
	RCONbits.IPEN = 1;
	/* define I/O ports */
	IBSPORTA = IBSPORT_IOA;
	IBSPORTB = IBSPORT_IOB;
	LATA = 0;
	LATB = 0;
	INTCON2bits.RBPU = false; // WSEL input pull-up

	//OpenTimer0(TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_64);
	T0CON = 0b10000101;
	tmp = TIMERFAST >> 8;
	TMR0H = tmp;
	tmp = TIMERFAST & 0xFF;
	TMR0L = tmp;
	//OpenTimer1(TIMER_INT_ON & T1_16BIT_RW & T1_SOURCE_INT & T1_PS_1_4 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF);
	T1CON = 0b1011101;
	tmp = SAMPLEFREQ >> 8;
	TMR1H = tmp;
	tmp = SAMPLEFREQ & 0xFF;
	TMR1L = tmp;


	INTCONbits.TMR0IE = 1; // enable int
	INTCON2bits.TMR0IP = 1; // make it high level
	PIE1bits.TMR1IE = 1; // enable int
	IPR1bits.TMR1IP = 1; // make it high level

	/* Enable all high priority interrupts */
	INTCONbits.PEIE = 1;
	INTCONbits.GIEH = 1;
}

void main(void)
{
	init_tick60();
	/* Loop forever */
	while (true) { // busy work
		if (WSEL) {
			tw = TICKWIDTH;
		} else {
			tw = TICKWIDTH_LONG;
		}
	}
}
