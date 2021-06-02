/*
 * display.c
 *
 *  Created on: Dec 23, 2020
 *      Author: Dang Nam
 */

#include "display.h"
#include "main.h"
#include "stdlib.h"
#include "string.h"
#include "gpio.h"

extern SPI_HandleTypeDef hspi1;

Image_t screen_image;
Image_t next_screen_image;

void disUpdateScreen(void) {
	memcpy(&screen_image, &next_screen_image, sizeof(Image_t));
	disConvertDataSend(&screen_image);
}

void disConvertDataSend(Image_t *image) {
	// Xoa het mang send
	memset(image->data_send_1, 0, 32*sizeof(uint8_t));
	memset(image->data_send_2, 0, 32*sizeof(uint8_t));
	memset(image->data_send_3, 0, 32*sizeof(uint8_t));
	memset(image->data_send_4, 0, 32*sizeof(uint8_t));

	// Theo phase_send, bat tung bit len
	for (uint8_t col_group = 0; col_group < 8; col_group++) {
		// 1 col_group has 4 byte
		for (uint8_t col = 0; col < 8; col++) {
			// 8 col <=> 8 bit
			// phase 1
			(image->data_send_1[col_group*4    ]) |= ((image->data_image[col_group*16 + col + 1]) & (0x10 << 0));
			(image->data_send_1[col_group*4 + 1]) |= ((image->data_image[col_group*16 + col + 1]) & (0x01 << 0));
			(image->data_send_1[col_group*4 + 2]) |= ((image->data_image[col_group*16 + col    ]) & (0x10 << 0));
			(image->data_send_1[col_group*4 + 3]) |= ((image->data_image[col_group*16 + col    ]) & (0x01 << 0));
			// phase 2
			(image->data_send_2[col_group*4    ]) |= ((image->data_image[col_group*16 + col + 1]) & (0x10 << 1));
			(image->data_send_2[col_group*4 + 1]) |= ((image->data_image[col_group*16 + col + 1]) & (0x01 << 1));
			(image->data_send_2[col_group*4 + 2]) |= ((image->data_image[col_group*16 + col    ]) & (0x10 << 1));
			(image->data_send_2[col_group*4 + 3]) |= ((image->data_image[col_group*16 + col    ]) & (0x01 << 1));
			// phase 3
			(image->data_send_3[col_group*4    ]) |= ((image->data_image[col_group*16 + col + 1]) & (0x10 << 2));
			(image->data_send_3[col_group*4 + 1]) |= ((image->data_image[col_group*16 + col + 1]) & (0x01 << 2));
			(image->data_send_3[col_group*4 + 2]) |= ((image->data_image[col_group*16 + col    ]) & (0x10 << 2));
			(image->data_send_3[col_group*4 + 3]) |= ((image->data_image[col_group*16 + col    ]) & (0x01 << 2));
			// phase 4
			(image->data_send_4[col_group*4    ]) |= ((image->data_image[col_group*16 + col + 1]) & (0x10 << 3));
			(image->data_send_4[col_group*4 + 1]) |= ((image->data_image[col_group*16 + col + 1]) & (0x01 << 3));
			(image->data_send_4[col_group*4 + 2]) |= ((image->data_image[col_group*16 + col    ]) & (0x10 << 3));
			(image->data_send_4[col_group*4 + 3]) |= ((image->data_image[col_group*16 + col    ]) & (0x01 << 3));
		}
	}
}

void disRefreshScreen(Image_t *image) {
	uint8_t *pData;
	// Off led
	HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);
	// Select row
	if (image->phase_send == 0) {
		pData = image->data_send_1;
		HAL_GPIO_WritePin(A_138_GPIO_Port, A_138_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_138_GPIO_Port, B_138_Pin, GPIO_PIN_RESET);
	} else if (image->phase_send == 1) {
		pData = image->data_send_2;
		HAL_GPIO_WritePin(A_138_GPIO_Port, A_138_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_138_GPIO_Port, B_138_Pin, GPIO_PIN_RESET);
	} else if (image->phase_send == 2) {
		pData = image->data_send_3;
		HAL_GPIO_WritePin(A_138_GPIO_Port, A_138_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_138_GPIO_Port, B_138_Pin, GPIO_PIN_SET);
	} else if (image->phase_send == 2) {
		pData = image->data_send_4;
		HAL_GPIO_WritePin(A_138_GPIO_Port, A_138_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_138_GPIO_Port, B_138_Pin, GPIO_PIN_SET);
	}
	// Transfer
	HAL_SPI_Transmit(&hspi1, pData, 32, 1);
	// Latch
	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET);
	// On led
	HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET);
	// Next phase
	image->phase_send = (image->phase_send + 1) % 4;
}
