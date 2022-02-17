/*
 * sneak100_core_def.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_DEF_H_
#define INC_CORE_DEF_H_

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
	SETTINGS_MODE_RC_RC5,
	SETTINGS_MODE_RC_BLUETOOTH,
	SETTINGS_MODE_NUM
} Settings_Mode_t;

typedef enum {
	SETTINGS_DYHLO_BLACK,
	SETTINGS_DYHLO_WHITE,
	SETTINGS_DYHLO_AUTO,
	SETTINGS_DYHLO_NUM
} Settings_Dyhlo_t;

typedef enum {
	SETTINGS_STRATEGY_AGRESSIVE,
	SETTINGS_STRATEGY_DEFENSIVE,
	SETTINGS_STRATEGY_PASSIVE,
	SETTINGS_STRATEGY_NUM
} Settings_Strategy_t;

typedef struct {
	Settings_Mode_t mode;
	Settings_Dyhlo_t dyhlo;
	Settings_Strategy_t strategy;
} RobotSettings_t;

typedef struct {
	struct {
		uint16_t position_raw;
		float position;
		float velocity;
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
		uint8_t seen;
	} rc5;
} RobotState_t;

#endif
