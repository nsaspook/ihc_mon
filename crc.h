/* 
 * File:   crc.h
 * Author: root
 *
 * Created on March 12, 2020, 9:37 AM
 */

#ifndef CRC_H
#define	CRC_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "ibsmon.h"

	uint16_t crc16(volatile uint8_t *, uint16_t);
	uint8_t _modbus_rtu_send_msg_pre(volatile uint8_t *, uint16_t);


#ifdef	__cplusplus
}
#endif

#endif	/* CRC_H */

