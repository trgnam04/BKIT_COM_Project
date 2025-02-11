/*
 * MsgProcessing_Layer.h
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#ifndef INC_MSGPROCESSING_LAYER_H_
#define INC_MSGPROCESSING_LAYER_H_

#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "cmox_crypto.h" // for AES
#include "usart.h"

#define MAX_MESSAGE_SIZE 1024 // byte
#define HEADER_SIZE 3 // byte
#define MAX_PACKAGE_SIZE (MAX_MESSAGE_SIZE + HEADER_SIZE)

#define FC_DATA 0x01 // data function code
#define FC_AES_KEY 0x02
#define FC_HMAC_KEY 0x03

#define KEY_SAVED 0x06 // if recv key correct

#define HMAC_KEY 0x04
#define AES_KEY 0x05

// ERROR define temp
#define ERR_HW_TRANSMIT 		0xFFFE // hw transmit fail
#define ERR_AES_ENCRYPT 		0xFFFD // aes encrypt fail
#define ERR_SHA2_COMPUTE 		0xFFFC // sha256 compute tag fail
#define ERR_MSG_OVERFLOW 		0xFFFB // message recv overflow
#define ERR_HW_RECEIVE			0xFFFA // hw receive fail
#define ERR_DATA_MISSING		0xFFF9 // Data missing when transfer
#define ERR_DATA_CHANGED		0xFFF8 // Data has been changed, hash fail
#define ERR_AES_DECRYPT			0xFFF7 // aes decrypt fail
#define ERR_DATA_SERIALIZE		0xFFF6 // nanopb serialize fail
#define ERR_DATA_DESERIALIZE	0xFFF6 // nanopb deserialize fail

uint16_t MSGPROCESSING_SendMessage(uint32_t* salve_address, uint8_t* function_code, uint8_t* message, size_t* message_length);
uint16_t MSGPROCESSING_ReceiveMessage(uint8_t* message, size_t* message_length);

#endif /* INC_MSGPROCESSING_LAYER_H_ */
