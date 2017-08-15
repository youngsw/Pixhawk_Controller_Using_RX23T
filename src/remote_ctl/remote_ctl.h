/*
 * remote_ctl.h
 *
 *  Created on: Jul 27, 2017
 *      Author: Arthur
 */

#ifndef REMOTE_CTL_REMOTE_CTL_H_
#define REMOTE_CTL_REMOTE_CTL_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "../cg_src/r_cg_macrodriver.h"
#include "../cg_src/r_cg_userdefine.h"
#include "../mission_ctl/mission_ctl.h"
#include "../sonar/sonar.h"
#include "../camera/camera.h"

extern bool mission_start;
extern bool is_alarm;
extern bool sci5_trans;

extern void remote_ctl_init(void);
extern void IRQ0_IntHandler(void);
extern void IRQ1_IntHandler(void);
extern void CMT3_IntHandler(void);
extern void SCI5_TransIntHandler(void);
#endif /* REMOTE_CTL_REMOTE_CTL_H_ */
