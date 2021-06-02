/*
 * display.h
 *
 *  Created on: Dec 23, 2020
 *      Author: Dang Nam
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "stm32f1xx_hal.h"

#define HEIGH_SCREEN 16
#define WIDTH_SCREEN 64

#define LENGH_BUFF_IMAGE WIDTH_SCREEN*4

typedef struct Image {
	uint8_t 	width;
	uint8_t 	offset_idx;
	uint8_t 	data_image[LENGH_BUFF_IMAGE];
	double 		time_scroll;
	uint32_t 	count_scroll;
	uint8_t		data_send_1[32];
	uint8_t		data_send_2[32];
	uint8_t		data_send_3[32];
	uint8_t		data_send_4[32];
	uint8_t		phase_send;
}Image_t;

void disUpdateScreen(void);
void disConvertDataSend(Image_t *image);
void disRefreshScreen(Image_t *image);

#endif /* INC_DISPLAY_H_ */
