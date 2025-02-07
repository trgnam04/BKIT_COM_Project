/*
 * Serial_Debug.h
 *
 *  Created on: Feb 6, 2025
 *      Author: ADMIN
 */

#ifndef INC_SERIAL_DEBUG_H_
#define INC_SERIAL_DEBUG_H_

#include "usart.h"
#include <stdio.h>
#include "string.h"

void initSD(void);
void uprintf(char* str);

#endif /* INC_SERIAL_DEBUG_H_ */
