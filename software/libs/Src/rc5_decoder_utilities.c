/*
 * rc5_decoder_utilities.c
 *
 *  Created on: Dec 30, 2021
 *      Author: ermoz
 */

#include "rc5_decoder.h"

void __rc5_emit1(void *decoder) {
	((DecoderRC5_t *)decoder)->message.frame |=(1<<(13 - ((DecoderRC5_t *)decoder)->bits_ready));
	((DecoderRC5_t *)decoder)->bits_ready++;
}

void __rc5_emit0(void *decoder) {
	((DecoderRC5_t *)decoder)->message.frame &=~(1<<(13 - ((DecoderRC5_t *)decoder)->bits_ready));
	((DecoderRC5_t *)decoder)->bits_ready++;
}

void __rc5_reset(void *decoder) {
	((DecoderRC5_t *)decoder)->message = (const RC5_Message_t){0};
	((DecoderRC5_t *)decoder)->bits_ready = 0;
}

uint8_t __rc5_get_short_space(void *decoder) {
	if(((DecoderRC5_t *)decoder)->state) {
		uint32_t time = ((DecoderRC5_t *)decoder)->counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_SHORT)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

uint8_t __rc5_get_short_pulse(void *decoder) {
	if(!((DecoderRC5_t *)decoder)->state) {
		uint32_t time = ((DecoderRC5_t *)decoder)->counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_SHORT)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

uint8_t __rc5_get_long_space(void *decoder) {
	if(((DecoderRC5_t *)decoder)->state) {
		uint32_t time = ((DecoderRC5_t *)decoder)->counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_LONG)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

uint8_t __rc5_get_long_pulse(void *decoder) {
	if(!((DecoderRC5_t *)decoder)->state) {
		uint32_t time = ((DecoderRC5_t *)decoder)->counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_LONG)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

