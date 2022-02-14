/*
 * line.c
 *
 *  Created on: Sep 10, 2021
 *      Author: ermoz
 */

#include "line.h"

void Line_Init(Line_t *line, uint16_t *read_src, uint16_t threshold, Line_Polarity_t polarity) {
	line->read_src = read_src;
	line->threshold = threshold;
	line->polarity = polarity;
}

Line_Polarity_t Line_GetPolarity(Line_t *line) {
	return line->polarity;
}

void Line_SetPolarity(Line_t *line, Line_Polarity_t polarity) {
	line->polarity = polarity;
}

uint8_t Line_GetState(Line_t *line) {
	return (*line->read_src<line->threshold)^line->polarity;
}
