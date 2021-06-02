/*
 * processing.h
 *
 *  Created on: Dec 29, 2020
 *      Author: Dang Nam
 */

#ifndef INC_PROCESSING_H_
#define INC_PROCESSING_H_

#include "display.h"
#include "stm32f1xx_hal.h"

// Cac ham xu li de ghep lai thanh mang su that
// Copy va bo byte dau ra
// Hieu ung chay chu: chi quyet dinh thoi giam scrool la dc


void proClearAll(void);
void proAppendMatrix(uint8_t src_data, uint32_t width);
void proAppendDigit(uint8_t number);
void proAppendCharacter(uint8_t c);
void proAppendLogo(void);
void proAppendBlank(uint8_t width);
void proAppendString(uint8_t *s);

// Function: append char to image
// Function: append string to image
// Dua vao vi tri abc tinh index trong mang ABC

// Function: append digit
// Function: append digit nhieu so
// Dua vao vi tri 0 tinh index trong mang 0

// Function: append a symbol

// Function: append a element: bat ke la so hay chu, append 1 mang

// Function: nap Logo to image

#endif /* INC_PROCESSING_H_ */
