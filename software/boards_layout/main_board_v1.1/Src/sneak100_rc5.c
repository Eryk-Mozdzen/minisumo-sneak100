/*
 * sneak100_rc5.c
 *
 *  Created on: Jan 27, 2022
 *      Author: emozdzen
 */

#include "sneak100_rc5.h"

DecoderRC5_t decoder_rc5;

void SNEAK100_RC5_Init() {

	DecoderRC5_Init(&decoder_rc5, &htim7, RECEIVER_OUT_GPIO_Port, RECEIVER_OUT_Pin);

}
