/*
 * ppm_encoder.h
 *
 *  Created on: Jul 13, 2017
 *      Author: Arthur
 */

#ifndef PPM_ENCODER_PPM_ENCODER_H_
#define PPM_ENCODER_PPM_ENCODER_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "../cg_src/r_cg_macrodriver.h"

#define PPM_ENCODER_CHANNEL_NUM 8
#define PPM_ENCODER_DEFFAULT_CH_VAL 1000

#define channel_val_MIN 1016
#define channel_val_MID 1520
#define channel_val_MAX 2021
#define channel_val_RANGE 1000
#define channel_percent(x) channel_val_MIN + channel_val_RANGE/100*(x)

typedef struct
{
    uint16_t ch_val[PPM_ENCODER_CHANNEL_NUM];
    uint16_t idle_val;
}ppm_data_t;

extern void ppm_encoder_init(void);
extern bool ppm_data_shadow_one_step(void);
extern void ppm_data_shadow_update(void);
extern void ppm_encoder_set_data(ppm_data_t *ppm_data);
extern void set_ppm(uint16_t roll_val,uint16_t pitch_val,uint16_t throttle_val,uint16_t yaw_val,uint16_t mode_val,uint16_t Emergency);
extern void CMT0_IntHandler(void);

#endif /* PPM_ENCODER_PPM_ENCODER_H_ */
