/*
 * line.h
 *
 *  Created on: Sep 10, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTS_INC_LINE_H_
#define SNEAK100_ABSTRACTS_INC_LINE_H_

#include <stdint.h>

typedef enum {
	LINE_POLARITY_BLACK,
	LINE_POLARITY_WHITE,
	LINE_POLARITY_AUTO
} Line_Polarity_t;

typedef struct {
	uint16_t *read_src;
	uint16_t threshold;
	Line_Polarity_t polarity;
} Line_t;

void Line_Init(Line_t *, uint16_t *, uint16_t, Line_Polarity_t);

Line_Polarity_t Line_GetPolarity(Line_t *);
void Line_SetPolarity(Line_t *, Line_Polarity_t);
uint8_t Line_GetState(Line_t *);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_LINE_H_ */
