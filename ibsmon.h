#ifndef PAT_H_INCLUDED
#define PAT_H_INCLUDED
//	hardware defines

#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pic18f1320.h>
#include "ihc_vector.h"

#define TICK60		240 // 240 for 60 seconds
#define TICKWIDTH	18 // 19 for about 250ms
#define TICKWIDTH_LONG	72

#define	TIMERFAST	26636	// tick timer, fine tune this to calibrate 60 second ticks, 26636 = 119.99926 seconds
#define	SAMPLEFREQ	00001	// tick duration time block

#define IBSPORTA	TRISA
#define IBSPORTB	TRISB
#define IBSPORT_IOA	0b00010000		//
#define IBSPORT_IOB	0b00010000		//

#define LED0		LATAbits.LATA2		// pin 6 pulse signal
#define LED1		LATAbits.LATA1		// pin 2 pulse signal
#define ANA_SIG		LATBbits.LATB3		// pulse coupled through 22uf cap, short across cap for ttl level pulse
#define LED		LATBbits.LATB0		// onboard led flasher
#define CLOCK		LATBbits.LATB2		// calibration clock output
#define WSEL		PORTBbits.RB4		// pulse width selection bit

#endif 