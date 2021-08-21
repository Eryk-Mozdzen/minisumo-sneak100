/*
 * math_tools.h
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_UTILITIES_INC_MATH_TOOLS_H_
#define SNEAK100_UTILITIES_INC_MATH_TOOLS_H_

#include <stdint.h>

#define MIN(__A__, __B__) (((__A__)<=(__B__)) ? (__A__) : (__B__))
#define MAX(__A__, __B__) (((__A__)>=(__B__)) ? (__A__) : (__B__))

void swap(uint16_t *, uint16_t *);

#endif /* SNEAK100_UTILITIES_INC_MATH_TOOLS_H_ */
