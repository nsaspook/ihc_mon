/* 
 * File:   ihc_vector.h
 * Author: root
 *
 * Created on October 22, 2017, 4:25 PM
 */

#ifndef IHC_VECTOR_H
#define	IHC_VECTOR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <p18f1320.h>
#include <timers.h>
#include <stdlib.h>
#include <usart.h>
#include <stdio.h>
#include <EEP.h>
#include "ibsmon.h"

	extern volatile struct V_data V;
	extern volatile uint8_t ibs_stream_file, ibs_stream_file_prev;
	extern volatile uint16_t timer0_off, link_count;

#ifdef	__cplusplus
}
#endif

#endif	/* IHC_VECTOR_H */

