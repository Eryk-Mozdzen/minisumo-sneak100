/*
 * sneak100_core_def.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_DEF_H_
#define INC_CORE_DEF_H_

#include "line.h"
#include "motor.h"
#include "memory.h"
#include "encoder.h"
#include "display.h"
#include "proximity.h"
#include "bluetooth.h"
#include "rc5_decoder.h"

typedef enum {
	MOTOR_LF,
	MOTOR_LB,
	MOTOR_RF,
	MOTOR_RB
} Motor_Enum;

typedef enum {
	LINE_LL,
	LINE_LM,
	LINE_RM,
	LINE_RR
} Line_Enum;

typedef enum {
	PROXIMITY_LL,
	PROXIMITY_FL,
	PROXIMITY_FR,
	PROXIMITY_RR
} Proximity_Enum;

typedef enum {
	SETTINGS_MODE_MODULE,
	SETTINGS_MODE_BUTTON,
	SETTINGS_MODE_NUM,
	SETTINGS_MODE_INVALID
} Settings_Mode_t;

typedef enum {
	SETTINGS_DYHLO_BLACK,
	SETTINGS_DYHLO_WHITE,
	SETTINGS_DYHLO_AUTO,
	SETTINGS_DYHLO_NUM,
	SETTINGS_DYHLO_INVALID
} Settings_Dyhlo_t;

typedef enum {
	SETTINGS_STRATEGY_AGRESSIVE,
	SETTINGS_STRATEGY_DEFENSIVE,
	SETTINGS_STRATEGY_PASSIVE,
	SETTINGS_STRATEGY_NUM,
	SETTINGS_STRATEGY_INVALID
} Settings_Strategy_t;

typedef enum {
	CORE_STATE_IDLE,
	CORE_STATE_READY,
	CORE_STATE_PROGRAM,
	CORE_STATE_RUN,
	CORE_STATE_STOP
} CoreState_t;

typedef struct {
	Settings_Mode_t mode;
	Settings_Dyhlo_t dyhlo_color;
	Settings_Strategy_t strategy;
} RobotSettings_t;

typedef struct {
	uint8_t dyhlo_id;
	CoreState_t core_state;
} RobotFightData_t;

typedef struct {
	struct {
		uint16_t position_raw;
		float position;
		float velocity;
		float power;
	} motor[4];

	struct {
		uint16_t value;
		uint16_t threshold;
		uint8_t polarity;
		uint8_t state;
	} line[4];

	uint8_t proximity[4];

	float temperature;
	float battery;
	Bluetooth_Status_t bluetooth;

	struct {
		RC5_Message_t message;
		uint8_t expired;
	} rc5;
} RobotState_t;

typedef struct {
	Motor_t motors[4];
	Encoder_t encoders[4];
	Line_t lines[4];
	Proximity_t proximity[4];
	Memory_t memory;
	Display_t display;
	DecoderRC5_t decoder_rc5;
	Bluetooth_t bluetooth;

	FiniteStateMachine_t fsm;
	struct {
		uint16_t program_blink_counter;
		uint8_t program_select : 1;
		uint8_t button_start : 1;
		uint8_t button_stop : 1;
	} interface_flag;
	uint8_t update_request;

	RobotState_t state;
	RobotSettings_t settings;
	RobotFightData_t fight_data;
} Sneak100_t;

#endif
