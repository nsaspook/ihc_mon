#ifndef PAT_H_INCLUDED
#define PAT_H_INCLUDED
//	hardware defines

#include <stdint.h>

#define TRUE	1
#define FALSE	0
#define	ON	1
#define	OFF	0
#define TICK60		240 // 240 for 60 seconds
#define TICKWIDTH	20 // 20 for about 250ms

#define	TIMERFAST	26500			// tick timer
#define	SAMPLEFREQ	00001			// tick duration



#define IBSPORTA	TRISA
#define IBSPORTB	TRISB
#define IBSPORT_IOA	0b00010000		//
#define IBSPORT_IOB	0b00000000		//

#define LED0		LATAbits.LATA2
#define LED1		LATAbits.LATA1
#define ANA_SIG		LATBbits.LATB3
#define LED		LATBbits.LATB0

#endif 