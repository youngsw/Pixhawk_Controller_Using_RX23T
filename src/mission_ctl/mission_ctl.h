/*
 * mission.h
 *
 *  Created on: Jul 27, 2017
 *      Author: Arthur
 */

#ifndef MISSION_CTL_MISSION_CTL_H_
#define MISSION_CTL_MISSION_CTL_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../cg_src/r_cg_macrodriver.h"
#include "../cg_src/r_cg_userdefine.h"

#include "../OLED/OLED.h"
#include "../delay/delay.h"
#include "../matrix_key/matrix_key.h"
#include "../ppm_encoder/ppm_encoder.h"
#include "../PID_control/PID_control.h"
#include "../sonar/sonar.h"
#include "../camera/camera.h"

extern uint8_t mission;
extern uint8_t dest_height;
extern float current_height;
extern bool is_alarm;
extern bool is_drop;

enum {
    Stabilize = 1020,
    Alt_Hold = 1520,
    Land = 2020,
};

enum {
    Emergency_ON = 2020,
    Emergency_OFF = 1020,
};

extern bool is_alarm;

extern void is_Emergency(void);
extern void mission_select(void);
extern void mission_execute(void);
#endif /* MISSION_CTL_MISSION_CTL_H_ */
