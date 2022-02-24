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
#include "button.h"
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
} Core_Motor_t;

typedef enum {
	LINE_LL,
	LINE_LM,
	LINE_RM,
	LINE_RR
} Core_Line_t;

typedef enum {
	PROXIMITY_LL,
	PROXIMITY_FL,
	PROXIMITY_FR,
	PROXIMITY_RR
} Core_Proximity_t;

typedef enum {
	BUTTON_L,
	BUTTON_C,
	BUTTON_R
} Core_Button_t;

typedef enum {
	SETTINGS_MODE_MODULE,
	SETTINGS_MODE_BUTTON,
	SETTINGS_MODE_NUM,
	SETTINGS_MODE_INVALID
} Core_SettingsMode_t;

typedef enum {
	SETTINGS_DYHLO_BLACK,
	SETTINGS_DYHLO_WHITE,
	SETTINGS_DYHLO_AUTO,
	SETTINGS_DYHLO_NUM,
	SETTINGS_DYHLO_INVALID
} Core_SettingsDyhlo_t;

typedef enum {
	SETTINGS_STRATEGY_AGRESSIVE,
	SETTINGS_STRATEGY_DEFENSIVE,
	SETTINGS_STRATEGY_PASSIVE,
	SETTINGS_STRATEGY_NUM,
	SETTINGS_STRATEGY_INVALID
} Core_SettingsStrategy_t;

typedef enum {
	CORE_STATE_IDLE,
	CORE_STATE_READY,
	CORE_STATE_PROGRAM,
	CORE_STATE_RUN,
	CORE_STATE_STOP
} Core_State_t;

typedef struct {
	Core_SettingsMode_t mode;
	Core_SettingsDyhlo_t dyhlo_color;
	Core_SettingsStrategy_t strategy;
} Core_Settings_t;

typedef struct {
	uint8_t dyhlo_id;
	Core_State_t core_save_state;
} Core_FightData_t;

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
	Core_State_t core_curr_state;
	Bluetooth_Status_t bluetooth;

	struct {
		RC5_Message_t message;
		uint8_t expired;
	} rc5;
} Core_StateData_t;

typedef struct {
	Motor_t motors[4];
	Encoder_t encoders[4];
	Line_t lines[4];
	Proximity_t proximity[4];
	Button_t buttons[3];
	Memory_t memory;
	Display_t display;
	DecoderRC5_t decoder_rc5;
	Bluetooth_t bluetooth;

	FiniteStateMachine_t fsm;
	struct {
		uint16_t program_blink_counter;
		uint32_t start_time;

		uint8_t program_select : 1;
		uint8_t button_start : 1;
		uint8_t button_stop : 1;
	} interface_flag;
	uint8_t update_request;

	Core_StateData_t state;
	Core_Settings_t settings;
	Core_FightData_t fight_data;
} Sneak100_Core_t;

#endif
