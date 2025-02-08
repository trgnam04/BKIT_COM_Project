/*
 * global.h
 *
 *  Created on: Feb 8, 2025
 *      Author: nguye
 */

#ifndef INC_DATA_TYPE_H_
#define INC_DATA_TYPE_H_

#include "stdint.h"

struct sensor_data_t
{
	uint32_t sensor_id;
	uint32_t function_code;
	uint64_t data;
};

#endif /* INC_DATA_TYPE_H_ */
