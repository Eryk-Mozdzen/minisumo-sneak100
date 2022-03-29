/*
 * fight_states.c
 *
 *  Created on: Mar 22, 2022
 *      Author: emozdzen
 */

#include "fight_states.h"

/*	Enter	*/

void Fight_Start_Enter(void *data) {

}

void Fight_Explore_Enter(void *data) {

}

void Fight_AngleMeasurement_Enter(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	Encoder_Reset(&core_ptr->encoders[MOTOR_LF]);
	Encoder_Reset(&core_ptr->encoders[MOTOR_LB]);
	Encoder_Reset(&core_ptr->encoders[MOTOR_RF]);
	Encoder_Reset(&core_ptr->encoders[MOTOR_RB]);

	core_ptr->fight_data.flags.angle_complete = 0;
	core_ptr->fight_data.angle_value = 0;

	if(core_ptr->state.line[LINE_LL].state)
		core_ptr->fight_data.flags.angle_side = 1;
	else if(core_ptr->state.line[LINE_RR].state)
		core_ptr->fight_data.flags.angle_side = 0;
}

void Fight_LineManeuver_Enter(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	Encoder_Reset(&core_ptr->encoders[MOTOR_LF]);
	Encoder_Reset(&core_ptr->encoders[MOTOR_LB]);
	Encoder_Reset(&core_ptr->encoders[MOTOR_RF]);
	Encoder_Reset(&core_ptr->encoders[MOTOR_RB]);

	core_ptr->fight_data.flags.turn_complete = 0;
	core_ptr->fight_data.turn_back_counter = 0;
}

/*	Execute	*/

void Fight_Start_Execute(void *data) {

}

void Fight_Explore_Execute(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	Motor_SetVelocity(&core_ptr->motors[MOTOR_LF], -FIGHT_EXPLORE_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_LB], -FIGHT_EXPLORE_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RF],  FIGHT_EXPLORE_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RB],  FIGHT_EXPLORE_SPEED);
}

void Fight_AngleMeasurement_Execute(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	Motor_SetVelocity(&core_ptr->motors[MOTOR_LF], -FIGHT_ANGLE_MEAS_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_LB], -FIGHT_ANGLE_MEAS_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RF],  FIGHT_ANGLE_MEAS_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RB],  FIGHT_ANGLE_MEAS_SPEED);

	if(core_ptr->fight_data.flags.angle_side) {
		// left side

		if(core_ptr->state.line[LINE_LM].state) {
			core_ptr->fight_data.angle_distance = 0.f;
			core_ptr->fight_data.angle_distance -=Encoder_Reset(&core_ptr->encoders[MOTOR_LF]);
			core_ptr->fight_data.angle_distance -=Encoder_Reset(&core_ptr->encoders[MOTOR_LB]);
			core_ptr->fight_data.angle_distance +=Encoder_Reset(&core_ptr->encoders[MOTOR_RF]);
			core_ptr->fight_data.angle_distance +=Encoder_Reset(&core_ptr->encoders[MOTOR_RB]);
			core_ptr->fight_data.angle_distance /=4.f;

			core_ptr->fight_data.angle_distance /=ENCODER_CPR;
			core_ptr->fight_data.angle_distance /=MOTOR_GEAR_RATIO;
			core_ptr->fight_data.angle_distance *=(2*M_PI);
			core_ptr->fight_data.angle_distance *=WHEEL_RADIUS;

			core_ptr->fight_data.angle_value = M_PI - atan2(core_ptr->fight_data.angle_distance, LINE_SPACING);
			core_ptr->fight_data.flags.angle_complete = 1;
		}

	} else {
		// right side

		if(core_ptr->state.line[LINE_RM].state) {
			core_ptr->fight_data.angle_distance = 0.f;
			core_ptr->fight_data.angle_distance -=Encoder_Reset(&core_ptr->encoders[MOTOR_LF]);
			core_ptr->fight_data.angle_distance -=Encoder_Reset(&core_ptr->encoders[MOTOR_LB]);
			core_ptr->fight_data.angle_distance +=Encoder_Reset(&core_ptr->encoders[MOTOR_RF]);
			core_ptr->fight_data.angle_distance +=Encoder_Reset(&core_ptr->encoders[MOTOR_RB]);
			core_ptr->fight_data.angle_distance /=4.f;

			core_ptr->fight_data.angle_distance /=ENCODER_CPR;
			core_ptr->fight_data.angle_distance /=MOTOR_GEAR_RATIO;
			core_ptr->fight_data.angle_distance *=(2*M_PI);
			core_ptr->fight_data.angle_distance *=WHEEL_RADIUS;

			core_ptr->fight_data.angle_value = M_PI + atan2(core_ptr->fight_data.angle_distance, LINE_SPACING);
			core_ptr->fight_data.flags.angle_complete = 1;
		}
	}
}

void Fight_LineManeuver_Execute(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	if(core_ptr->fight_data.turn_back_counter++<5) {
		Motor_SetVelocity(&core_ptr->motors[MOTOR_LF], FIGHT_LINE_BACK_SPEED);
		Motor_SetVelocity(&core_ptr->motors[MOTOR_LB], FIGHT_LINE_BACK_SPEED);
		Motor_SetVelocity(&core_ptr->motors[MOTOR_RF], -FIGHT_LINE_BACK_SPEED);
		Motor_SetVelocity(&core_ptr->motors[MOTOR_RB], -FIGHT_LINE_BACK_SPEED);

		Encoder_Reset(&core_ptr->encoders[MOTOR_LF]);
		Encoder_Reset(&core_ptr->encoders[MOTOR_LB]);
		Encoder_Reset(&core_ptr->encoders[MOTOR_RF]);
		Encoder_Reset(&core_ptr->encoders[MOTOR_RB]);

		return;
	}

	/*uint8_t side = core_ptr->fight_data.angle_value<M_PI;

	Motor_SetVelocity(&core_ptr->motors[MOTOR_LF], -3.f*(side ? 1.f : -1.f));
	Motor_SetVelocity(&core_ptr->motors[MOTOR_LB], -3.f*(side ? 1.f : -1.f));
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RF],  3.f*(side ? -1.f : 1.f));
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RB],  3.f*(side ? -1.f : 1.f));

	float wheel_dist = 0.f;
	wheel_dist +=Encoder_GetPosition(&core_ptr->encoders[MOTOR_LF]);
	wheel_dist +=Encoder_GetPosition(&core_ptr->encoders[MOTOR_LB]);
	wheel_dist +=Encoder_GetPosition(&core_ptr->encoders[MOTOR_RF]);
	wheel_dist +=Encoder_GetPosition(&core_ptr->encoders[MOTOR_RB]);
	wheel_dist /=4.f;

	wheel_dist *=(2*M_PI);

	if() {
		core_ptr->fight_data.flags.turn_complete = 1;
	}*/

	Motor_SetVelocity(&core_ptr->motors[MOTOR_LF], -FIGHT_LINE_TURN_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_LB], -FIGHT_LINE_TURN_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RF], -FIGHT_LINE_TURN_SPEED);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RB], -FIGHT_LINE_TURN_SPEED);

	float wheel_dist = 0.f;
	wheel_dist +=fabs(Encoder_GetPosition(&core_ptr->encoders[MOTOR_LF]));
	wheel_dist +=fabs(Encoder_GetPosition(&core_ptr->encoders[MOTOR_LB]));
	wheel_dist +=fabs(Encoder_GetPosition(&core_ptr->encoders[MOTOR_RF]));
	wheel_dist +=fabs(Encoder_GetPosition(&core_ptr->encoders[MOTOR_RB]));
	wheel_dist /=4.f;

	wheel_dist *=(2*M_PI);

	if(core_ptr->fight_data.angle_value<wheel_dist*WHEEL_ROT_TO_CHASSIE_ROT_CONST) {
		core_ptr->fight_data.flags.turn_complete = 1;
	}
}

/*	Exit	*/

void Fight_Start_Exit(void *data) {

}

void Fight_Explore_Exit(void *data) {

}

void Fight_AngleMeasurement_Exit(void *data) {

}

void Fight_LineManeuver_Exit(void *data) {

}
