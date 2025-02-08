/*
 * Application_Layer.c
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#include "Application_Layer.h"

uint16_t BKIT_Init()
{
	return 0;
}

uint16_t BKIT_SendMessage(const sensor_data_t* data)
{
	// Duplicate sensor id
	uint32_t sensor_id = data->sensor_id;

	// Serialize
	uint8_t buffer[sensor_data_t_size]; // Use the defined max size
	pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

	bool status = pb_encode(&ostream, &sensor_data_t_msg, data);

	if (!status) {
		// ERROR CODE: 0xFFFE
		return 0xFFFE;
	}
	size_t message_length = ostream.bytes_written;

	// Call message processing layer functions
	return 0;
}

uint16_t BKIT_ReceiveMessage(sensor_data_t* data)
{
	return 0;
}

uint16_t BKIT_UpdateSecurityKey()
{
	return 0;
}
