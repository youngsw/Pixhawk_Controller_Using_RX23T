/*
 * camera.h
 *
 *  Created on: Jul 31, 2017
 *      Author: Arthur
 */

#ifndef CAMERA_CAMERA_H_
#define CAMERA_CAMERA_H_

#include <stdint.h>
#include <stdbool.h>
#include "../cg_src/r_cg_macrodriver.h"
#include "../remote_ctl/remote_ctl.h"
#include "../sonar/sonar.h"

#define CAMERA_W    160
#define CAMERA_H    120
#define CAMERA_STX  0xFF
#define ALARM_STX   0xFD
#define ALARM_END   0xFE

#define CAMERA_MID_X    80
#define CAMERA_MID_Y    60

extern uint8_t g5_rx_char;
extern volatile uint8_t get_x, get_y;

extern void SCI5_IntHandler(void);

#endif /* CAMERA_CAMERA_H_ */
