/*
 * Serial_Debug.c
 *
 *  Created on: Feb 6, 2025
 *      Author: ADMIN
 */

#include "Serial_Debug.h"

uint8_t receive_buffer = 0;
uint8_t msg[256];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1){
		HAL_UART_Transmit(&huart1, &receive_buffer, 1, 100);

		HAL_UART_Receive_IT(&huart1, &receive_buffer, 1);
	}
}

void initSD(void){
	HAL_UART_Receive_IT(&huart1, &receive_buffer, 1);
}

void uprintf(char *str) {
	HAL_UART_Transmit(&huart1, (void*) msg, sprintf((void*) msg, "%s", str), 10);
}
