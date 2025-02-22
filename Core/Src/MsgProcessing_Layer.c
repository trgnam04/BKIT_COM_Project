/*
 * MsgProcessing_Layer.c
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */
#include "MsgProcessing_Layer.h"

unsigned char key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
unsigned char hmac_key[6] = {1, 2, 3, 4, 5, 6};
unsigned char iv[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

// TEST DATA
// message: xinchao
// uint8_t data[100] = {0x30, 0x01, 0x6F, 0x38, 0x4F, 0x10, 0x77, 0xA6, 0xAA, 0x5F, 0x88, 0x03, 0xA9, 0x9A, 0xB9, 0x2B, 0xEC, 0xDE, 0xE6, 0x6B, 0x1A, 0xF8, 0xD7, 0x57, 0x08, 0x43, 0x46, 0x77, 0x0B, 0x39, 0x5D, 0x3C, 0x82, 0xD4, 0xFE, 0xD0, 0xCE, 0x20, 0x34, 0x01, 0xC7, 0x0E, 0xFA, 0xC2, 0x75, 0x4C, 0x8E, 0x23, 0x51, 0xD9};
// size_t data_size = 100;
uint16_t MSGPROCESSING_SendMessage(uint32_t* salve_address, uint8_t * function_code, uint8_t* message, size_t* message_length)
{

	// Send without encrypt (send key)
	if(*function_code != FC_DATA){
		uint16_t package_size = HEADER_SIZE + *message_length;
		uint8_t package[package_size];
		package[0] = (package_size & 0xFFFF0000) >> 8;
		package[1] = (package_size & 0x0000FFFF) >> 0;
		package[2] = *function_code;
		memcpy(HEADER_SIZE + package, message, *message_length);
		// TODO: call HW to transmit
		// if hw fail return ERR_HW_TRANSMIT_FAIL
		return 0;
	};
	// AES
	uint8_t aes_out[*message_length + 16]; // 16 la max padding trong CBC mode
	uint8_t sha2_out[CMOX_SHA256_SIZE];
	size_t aes_outlen, sha2_outlen;

//	char uart_message[50] = {0};
//	for (size_t i = 0; i < *message_length; i++) {
//	    char hexStr[6]; // Buffer to hold "0xXX " (5 characters + null terminator)
//	    sprintf(hexStr, "0x%02X ", message[i]);
//	    HAL_UART_Transmit(&huart2, (uint8_t*)hexStr, strlen(hexStr), HAL_MAX_DELAY);
//	}
//	sprintf(uart_message, "Message length: %u", (unsigned int)*message_length);
//	HAL_UART_Transmit(&huart2, (uint8_t*)uart_message, strlen(uart_message), HAL_MAX_DELAY);

	// padding message
	uint8_t padded_mesage[*message_length + 16];
	size_t padded_message_length = add_pkcs7_padding(message, *message_length, padded_mesage, 16);

	cmox_cipher_retval_t aes_retval = cmox_cipher_encrypt(
			CMOX_AESFAST_CBC_ENC_ALGO,
			padded_mesage, padded_message_length, // input
			key, CMOX_CIPHER_128_BIT_KEY, // key
			iv, sizeof(iv),
			aes_out, &aes_outlen // output
		);

	if(aes_retval != CMOX_CIPHER_SUCCESS || aes_outlen % 16 != 0){
		// ERROR: Encrypt fail
		return ERR_AES_ENCRYPT;
	};

	// SHA256
	cmox_mac_retval_t sha2_retval = cmox_mac_compute(
			CMOX_HMAC_SHA256_ALGO,
			aes_out, aes_outlen, 		// input
			hmac_key , sizeof(hmac_key), // secret key
			NULL, 0,
			sha2_out, CMOX_SHA256_SIZE, // output (tag)
			&sha2_outlen
		);
	if(sha2_retval != CMOX_MAC_SUCCESS){
		// ERROR: Hash fail
		return ERR_SHA2_COMPUTE;
	}

	// error detector
	if(aes_outlen + sha2_outlen >= MAX_MESSAGE_SIZE){
		// ERROR: Message overflow
		return ERR_MSG_OVERFLOW;
	};

	// concatenate header + data >> package
	uint16_t package_size = HEADER_SIZE + aes_outlen + sha2_outlen;
	uint8_t package[package_size];
	package[0] = (package_size & 0xFFFF0000) >> 8;
	package[1] = (package_size & 0x0000FFFF) >> 0;
	package[2] = *function_code;
	memcpy(HEADER_SIZE + package, aes_out, aes_outlen);
	memcpy(HEADER_SIZE + package + aes_outlen, sha2_out, sha2_outlen);

	// call hardware layer to transmit output
	// TODO
	HAL_UART_Transmit(&huart2, package, package_size, 1000);
	return 0;
};
uint16_t MSGPROCESSING_ReceiveMessage(uint8_t* message, size_t* message_length)
{
//	uint8_t recv_package[MAX_PACKAGE_SIZE];
//	uint16_t recv_package_size;
	// TODO: call BKIT_HW_RECEIVE to get raw data
	// check receive state
	uint8_t recv_package[] = {
	    0x00, 0x33, 0x01, 0x62, 0x9E, 0x25, 0xC4, 0x12, 0x5B, 0x8B, 0x3B, 0x13,
	    0x31, 0x48, 0x33, 0x7E, 0xCA, 0x54, 0x12, 0x6A, 0x3C, 0xF3, 0x8F, 0xAA,
	    0xCE, 0xF5, 0x63, 0xAE, 0xBC, 0xBF, 0x76, 0x20, 0x32, 0xDF, 0xBF, 0x46,
	    0x73, 0x14, 0x1D, 0x66, 0x45, 0x09, 0x2C, 0xB3, 0x14, 0xDB, 0x90, 0x6C,
	    0xFF, 0x73, 0xB1
	};
	uint16_t recv_package_size = sizeof(recv_package);

	if(!0){
		// ERROR: receive fail
		return ERR_HW_RECEIVE;
	}
	// check received length
	if(recv_package_size < HEADER_SIZE){
		// ERROR: Data missing when transfer
		return ERR_DATA_MISSING;
	}
	uint16_t calc_package_size = recv_package[0];
	calc_package_size = (calc_package_size << 8) & recv_package[1];
	if(calc_package_size != recv_package_size){
		// ERROR: Data missing when transfer
		return ERR_DATA_MISSING;
	}

	// Check function code
	uint8_t function_code = recv_package[2];
	if(function_code != FC_DATA){
		// TODO: No decode, save key to register
		*message_length = recv_package_size - HEADER_SIZE;
		memcpy(message, recv_package + HEADER_SIZE, *message_length);

		return 0; // code to confirm with higher layer that key have saved
	}

	// parse data
	uint8_t recv_sha2_tag[CMOX_SHA256_SIZE]; // receive sha2_tag
	memcpy(recv_sha2_tag, recv_package + (recv_package_size - CMOX_SHA256_SIZE), CMOX_SHA256_SIZE);
	size_t aes_cipher_size = recv_package_size - CMOX_SHA256_SIZE - HEADER_SIZE;
	uint8_t aes_cipher[aes_cipher_size];
	memcpy(aes_cipher, recv_package + HEADER_SIZE, aes_cipher_size);

	// SHA256
	uint8_t calc_sha2_tag[CMOX_SHA256_SIZE];
	size_t calc_sha2_outlen;
	cmox_mac_retval_t calc_sha2_retval = cmox_mac_compute(
			CMOX_HMAC_SHA256_ALGO,
			aes_cipher, aes_cipher_size, 		// input
			hmac_key, sizeof(hmac_key), // secret key
			NULL, 0,
			calc_sha2_tag, CMOX_SHA256_SIZE, // output (tag)
			&calc_sha2_outlen
		);
	if(calc_sha2_retval != CMOX_MAC_SUCCESS){
		// ERROR: Hash fail
		return ERR_SHA2_COMPUTE;
	};

	// check hash
	if(memcmp(calc_sha2_tag,recv_sha2_tag, CMOX_SHA256_SIZE) != 0){
		// ERROR: hash fail, data has been changed
		return ERR_DATA_CHANGED;
	};

	// AES decrypt message
	size_t decrypt_len;
	cmox_cipher_retval_t aes_retval = cmox_cipher_decrypt(
			CMOX_AESFAST_CBC_DEC_ALGO,
			aes_cipher, aes_cipher_size, // input: cipher text
			key, CMOX_CIPHER_128_BIT_KEY, // key
			NULL, 0,
			message, &decrypt_len
		);
	if(aes_retval != CMOX_CIPHER_SUCCESS){
		// ERROR: Decrypt fail
		return ERR_AES_DECRYPT;
	};
	// successful
	*message_length = remove_pkcs7_padding(message, decrypt_len);
	HAL_UART_Transmit(&huart2, message, *message_length, HAL_MAX_DELAY);
	return 0;
};

