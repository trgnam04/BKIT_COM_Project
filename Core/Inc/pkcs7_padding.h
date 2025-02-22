/*
 * pkcs7_padding.h
 *
 *  Created on: Feb 22, 2025
 *      Author: nguye
 */

#ifndef INC_PKCS7_PADDING_H_
#define INC_PKCS7_PADDING_H_

#include <main.h>
#include <stddef.h>
#include <stdio.h>
size_t add_pkcs7_padding(const uint8_t *input, size_t input_len, uint8_t *output, size_t block_size);
size_t remove_pkcs7_padding(uint8_t *data, size_t data_len);

#endif /* INC_PKCS7_PADDING_H_ */
