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
} Motor_EnumTypeDef;

typedef enum {
	LINE_LL,
	LINE_LM,
	LINE_RM,
	LINE_RR
} LineEnumtypeDef;

typedef enum {
	PROXIMITY_LL,
	PROXIMITY_FL,
	PROXIMITY_FR,
	PROXIMITY_RR
} Proximity_EnumTypeDef;

typedef enum {
	SETTINGS_MODE_MODULE,
	SETTINGS_MODE_BUTTON,
	SETTINGS_MODE_RC_RC5,
	SETTINGS_MODE_RC_BLUETOOTH,
	SETTINGS_MODE_NUM
} Settings_Mode_EnumTypeDef;

typedef enum {
	SETTINGS_DYHLO_BLACK,
	SETTINGS_DYHLO_WHITE,
	SETTINGS_DYHLO_AUTO,
	SETTINGS_DYHLO_NUM
} Settings_Dyhlo_EnumTypeDef;

typedef enum {
	SETTINGS_STRATEGY_AGRESSIVE,
	SETTINGS_STRATEGY_DEFENSIVE,
	SETTINGS_STRATEGY_PASSIVE,
	SETTINGS_STRATEGY_NUM
} Settings_Strategy_EnumTypeDef;

typedef struct {
	Settings_Mode_EnumTypeDef mode;
	Settings_Dyhlo_EnumTypeDef dyhlo;
	Settings_Strategy_EnumTypeDef strategy;
} RobotSettings_StructTypeDef;

#endif /* INC_CORE_DEF_H_ */
