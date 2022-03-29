/*
 * fight_def.h
 *
 *  Created on: Mar 22, 2022
 *      Author: emozdzen
 */

#ifndef INC_FIGHT_DEF_H_
#define INC_FIGHT_DEF_H_

typedef enum {
	FIGHT_STATE_START,
	FIGHT_STATE_EXPLORE,
	FIGHT_STATE_ANGLE_MEASUREMENT,
	FIGHT_STATE_LINE_MANEUVER
} Fight_State_t;

#endif
