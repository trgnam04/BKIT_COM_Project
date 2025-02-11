/*
 * Application_Layer.h
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#ifndef INC_APPLICATION_LAYER_H_
#define INC_APPLICATION_LAYER_H_

#include "data_type.pb.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_common.h"
#include "MsgProcessing_Layer.h"



uint16_t BKIT_Init();
uint16_t BKIT_SendMessage(const sensor_data_t* data);
uint16_t BKIT_ReceiveMessage(sensor_data_t* data);

uint16_t BKIT_SendKey(uint32_t* slave_address, uint8_t* key_type, uint8_t* key, size_t* key_length);
uint16_t BKIT_ReceiveKey(uint8_t* key, size_t* key_length);
uint16_t BKIT_UpdateSecurityKey();


#endif /* INC_APPLICATION_LAYER_H_ */
