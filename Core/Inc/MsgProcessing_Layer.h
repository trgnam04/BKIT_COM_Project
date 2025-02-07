/*
 * MsgProcessing_Layer.h
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#ifndef INC_MSGPROCESSING_LAYER_H_
#define INC_MSGPROCESSING_LAYER_H_

extern enum{
	BKIT_COM_OK 		= 	0x00U,
	BKIT_COM_ERROR		=	0x01U,	// Transmit in HW layer fail
	BKIT_COM_BUSY		=	0x02U,	// Waiting for message
	BKIT_COM_TIMEOUT	=	0x03U,
	BKIT_COM_FAIL		=	0x04U	// Wrong Message or Missing Message
} BKIT_COM_StateTypedef;

#endif /* INC_MSGPROCESSING_LAYER_H_ */
