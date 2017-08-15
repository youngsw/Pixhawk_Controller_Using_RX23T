/*
 * sonar.h
 *
 *  Created on: Aug 6, 2017
 *      Author: Arthur
 */

#ifndef SONAR_SONAR_H_
#define SONAR_SONAR_H_

#include <stdint.h>
#include <stdbool.h>
#include "../cg_src/r_cg_macrodriver.h"

extern volatile float sonar_height;

extern void MTU5_IntHandler(void);

#endif /* SONAR_SONAR_H_ */
