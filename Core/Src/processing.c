/*
 * processing.c
 *
 *  Created on: Dec 29, 2020
 *      Author: Dang Nam
 */

#include "processing.h"
#include "font.h"
#include "stdlib.h"

extern Image_t next_screen_image;

/* Internal Function*/
static void proNewFrame(void);




/* Implementation */
void proClearAll(void) {
	proNewFrame();
	disUpdateScreen();
}

void proNewFrame(void) {
	next_screen_image.count_scroll = 0;
	next_screen_image.offset_idx = 0;
	next_screen_image.phase_send = 0;
	next_screen_image.width = 0;
	next_screen_image.time_scroll = 0;
	memset(next_screen_image.data_image, 0, LENGH_BUFF_IMAGE*sizeof(uint8_t));
}

void proAppendMatrix(uint8_t src_data, uint32_t width) {

}

void proAppendDigit(uint8_t number) {

}

void proAppendCharacter(uint8_t c) {

}

void proAppendLogo(void) {

}

void proAppendBlank(uint8_t width) {

}

void proAppendString(uint8_t *s) {

}
