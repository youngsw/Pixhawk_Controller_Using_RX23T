/*
 * matrix_key.h
 *
 *  Created on: Jul 26, 2017
 *      Author: Arthur
 */

#ifndef MATRIX_KEY_MATRIX_KEY_H_
#define MATRIX_KEY_MATRIX_KEY_H_

#include <stdint.h>
#include <stdbool.h>
#include "../cg_src/r_cg_macrodriver.h"
#include "../cg_src/r_cg_userdefine.h"

extern bool delayms(uint16_t time);

extern void R_Keyboard_Init(void);
extern uint8_t read_one_number(void);

#endif /* MATRIX_KEY_MATRIX_KEY_H_ */
