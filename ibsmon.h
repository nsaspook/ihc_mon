#ifndef PAT_H_INCLUDED
#define PAT_H_INCLUDED
//	hardware defines

#include <stdint.h>

typedef struct V_data { // ISR used, mainly for non-atomic mod problems
	uint32_t clock_500hz;
	uint32_t clock_2hz;
	uint8_t clock_blinks;
	uint8_t num_blinks;
	uint8_t blink_lock : 1;
	uint8_t config : 1;
	uint8_t stable : 1;
	uint8_t boot_code : 1;
	uint8_t send_count, recv_count, pwm_volts;
} V_data;

typedef struct OUTBITS2 {
	uint8_t b0 : 1;
	uint8_t b1 : 1;
	uint8_t b2 : 1;
	uint8_t b3 : 1;
	uint8_t b4 : 1;
	uint8_t b5 : 1;
	uint8_t b6 : 1;
	uint8_t b7 : 1;
} OUTBITS_TYPE2;

union Obits2 {
	uint8_t out_byte;
	OUTBITS_TYPE2 out_bits;
};

typedef enum comm_type {
	CLEAR,
	INIT,
	SEND,
	RECV,
} comm_type;

typedef enum cmd_type {
	G_MODE = 0,
	G_ERROR,
	G_AUX,
	G_LAST,
} cmd_type;

union PWMDC {
	unsigned int lpwm;
	char bpwm[2];
};

#define TRUE	1
#define FALSE	0
#define	ON	1
#define	OFF	0
#define	LEDON	0   // logic low lights led
#define	LEDOFF	1
#define BOFF	0
#define BON	255

#define	TIMEROFFSET	34268			// timer0 16bit counter value for 1 second to overflow
#define	TIMERFAST	26600			// fast flash 2hz
#define	SAMPLEFREQ	0xf660			// timer1 500hz
#define	PWMFREQ		65			// timer2 pwm
#define PWMVOLTS	127

#define MAX_DATA        20
#define MAX_GLITCH      3
#define MAX_PARAMS      5
#define MAX_BLINKS	10
#define ERROR_BLINKS	MAX_BLINKS
#define BLINK_SPACE	8

#define IBSPORTA	TRISA
#define IBSPORTB	TRISB
#define IBSPORT_IOA	0b00001100		//
#define IBSPORT_IOB	0b00010010		// RS-232 receive on B4

#define DE		LATAbits.LATA0
#define RE_		LATAbits.LATA1
#define RE20A_ERROR	LATAbits.LATA2
#define SIG4		LATAbits.LATA3
#define SIG5		LATAbits.LATA6
#define LED1		LATBbits.LATB0
#define BOOT_FLAG  	LATBbits.LATB2 // debug
#define ANA_SIG		LATBbits.LATB3


#define LINK_COUNT      10
#define MAX_C_ERROR     3

//#define LOCAL_ECHO	1
#define TDELAY		3
#define RDELAY		2000
#define QDELAY		1
#define TODELAY		4

#define CC_DEACT	61	// 1.00 normal 61
#define CC_ACT		92	// 1.50
#define CC_MPPT		122	// 2.00
#define CC_EQUAL	150	// 2.50
#define CC_BOOST	177	// 3.00
#define CC_FLOAT	205	// 3.50
#define CC_LIMIT	230	// 4.00
#define CC_OFFLINE	255	// 4.40

void SetDCPWM1(uint16_t);
#endif 