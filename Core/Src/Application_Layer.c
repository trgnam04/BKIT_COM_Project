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
		return ERR_DATA_SERIALIZE;
	}
	size_t message_length = ostream.bytes_written;

	// Call message processing layer functions
	uint8_t function_code = FC_DATA;
	uint16_t retval = MSGPROCESSING_SendMessage(&sensor_id, &function_code, buffer, &message_length);
	return retval;
}

uint16_t BKIT_ReceiveMessage(sensor_data_t* data)
{
	uint8_t message[MAX_MESSAGE_SIZE];
	size_t message_length;
	MSGPROCESSING_ReceiveMessage(message, &message_length);

	// De-serialize
	pb_istream_t istream = pb_istream_from_buffer(message, message_length);
	bool status = pb_decode(&istream, &sensor_data_t_msg, data);
	if(!status){
		// ERROR: De-serialize fail
		return ERR_DATA_DESERIALIZE;
	};
	return 0;
}

uint16_t BKIT_SendKey(uint32_t* slave_address,uint8_t* key_type,uint8_t* key,size_t* key_length)
{
	uint8_t function_code = HMAC_KEY;
	switch(*key_type){
	case HMAC_KEY:
		function_code = FC_HMAC_KEY;
		break;
	case AES_KEY:
		function_code = FC_AES_KEY;
		break;
	default:
		break;
	}
	uint16_t retval = MSGPROCESSING_SendMessage(slave_address, &function_code, key, key_length);
	return retval;
};
uint16_t BKIT_ReceiveKey(uint8_t* key, size_t* key_length)
{
	// return key for user (if needed)
	uint16_t retval = MSGPROCESSING_ReceiveMessage(key, key_length);
	if(retval == KEY_SAVED){
		// TODO
	}else{
		// TODO: ERROR
	};
	return 0;
};
uint16_t BKIT_UpdateSecurityKey()
{
	return 0;
}
