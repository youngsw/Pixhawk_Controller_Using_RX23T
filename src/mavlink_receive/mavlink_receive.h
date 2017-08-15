/*
 * mavlink_receive.h
 *
 *  Created on: Jul 14, 2017
 *      Author: Arthur
 */

#ifndef MAVLINK_RECEIVE_MAVLINK_RECEIVE_H_
#define MAVLINK_RECEIVE_MAVLINK_RECEIVE_H_

#include <stdint.h>
#include <stdbool.h>
#include "../cg_src/r_cg_macrodriver.h"
#include "../cg_src/r_cg_userdefine.h"
#include "../mission_ctl/mission_ctl.h"

#define MAVLINK_STX  0xFE
#define MSG_SONAR_LENGTH 8
#define MSG_SONAR_ID     173
#define MSG_HEIGHT_LENGTH 16

#define MSG_ATTITUDE_LENGTH 28
#define MSG_ATTITUDE_ID  30
#define MSG_ANGLE_LENGTH 36

#define pi 3.1415926

extern bool mission_start;

extern uint8_t Height_Buffer[20];
extern uint8_t Angle_Buffer[40];
extern uint8_t Rx_Buffer_height[20];
extern uint8_t Rx_Buffer_angle[40];
extern uint8_t rx_buffer;

extern uint8_t g1_rx_char;

extern bool start_receive_height;
extern bool start_receive_angle;
extern bool is_Height;
extern bool is_Angle;

extern bool is_drop;

extern float current_height;
extern float angle[3];
extern float Roll,Pitch,Yaw;

//void calculate_angle(float * angle);
//void calculate_height(float *height);
void SCI1_IntHandler(void);

#endif /* MAVLINK_RECEIVE_MAVLINK_RECEIVE_H_ */
