#ifndef PAT_H_INCLUDED
#define PAT_H_INCLUDED
//	hardware defines

#ifdef INTTYPES
#include <stdint.h>
#else
#define INTTYPES
/*unsigned types*/
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
/*signed types*/
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed long int32_t;
typedef signed long long int64_t;
#endif

typedef struct V_data { // ISR used, mainly for non-atomic mod problems
	uint32_t clock_100hz;
	uint32_t clock_2hz;
	uint8_t config : 1;
	uint8_t stable : 1;
	uint8_t send_count, recv_count,pwm_volts;
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
	INIT,
	SEND,
	RECV,
} comm_type;

#define TRUE	1
#define FALSE	0
#define	ON	1
#define	OFF	0
#define	LEDON	0   // logic low lights led
#define	LEDOFF	1

#define	TIMEROFFSET	34268			// timer0 16bit counter value for 1 second to overflow
#define	TIMERFAST	61000			// fast flash 2hz
#define	SAMPLEFREQ	0xe7b2			// timer1 100hz
#define	PWMFREQ		65			    // timer2 pwm
#define PWMVOLTS    127

#define MAX_DATA        16
#define MAX_GLITCH      3
#define MAX_PARAMS      5

#define IBSPORTA	TRISA
#define IBSPORTB	TRISB
#define IBSPORT_IOA	0b00000000		//
#define IBSPORT_IOB	0b00010010		// RS-232 receive on B4

#define DE		LATAbits.LATA0
#define RE_		LATAbits.LATA1
#define FINE_REG  	LATBbits.LATB2
#define ANA_SIG		LATBbits.LATB3
#define LED1		LATBbits.LATB0

#define LINK_COUNT      10
#define MAX_C_ERROR     3
#endif 