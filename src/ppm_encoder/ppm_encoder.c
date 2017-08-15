/*
 * ppm_encoder.c
 *
 *  Created on: Jul 13, 2017
 *      Author: Arthur
 */

#include "ppm_encoder.h"

////unit: us
//#define PPM_ENCODER_RESOLUTION 1
//unit: us
#define PPM_ENCODER_TOTAL_CH_VAL 20000
#define PPM_ENCODER_NEG_CH_VAL 500
//calculate arr value
#define CAL_ARR(ch_val) (ch_val * ppm_period_us)
//gpio configure

//timer configure


typedef enum
{
    PPM_STATE_CH_NEG,
    PPM_STATE_CH_POS,
    PPM_STATE_IDLE_NEG,
    PPM_STATE_IDLE_POS,
    PPM_STATE_STOP,
}ppm_state_e;

//gpio cache
//static bool ppm_gpio_next_val;

//timer period per us, this will be calculated when initialization
static uint32_t ppm_period_us = 1;
static bool first_time = true;
//ppm data buffer,  used to save user setting
#define PPM_DATA_BUF_NUM 2
static ppm_data_t ppm_data_buf[PPM_DATA_BUF_NUM];
static uint32_t ppm_data_buf_index;

//ppm data shadow buffer,  used to encode ppm
static ppm_data_t ppm_data_shadow;
static ppm_state_e ppm_shadow_state;
static uint32_t ppm_shadow_ch_idx;

static ppm_data_t ppm_data;

static void ppm_gpio_init(void);
static void ppm_gpio_negative(void);
static void ppm_gpio_positive(void);
static void ppm_gpio_set_next(bool is_pos);
static void ppm_timer_config(void);
static void ppm_data_calculate_idle(ppm_data_t *ppm_data);
static void ppm_data_set_default(ppm_data_t *ppm_data);
static void ppm_data_buf_init(void);
static void ppm_data_shadow_init(void);
void ppm_data_shadow_update(void);
bool ppm_data_shadow_one_step(void);

void ppm_encoder_init(void)
{
    ppm_data_buf_init();
    ppm_data_shadow_init();
    ppm_gpio_init();
    ppm_timer_config();
}

static void ppm_gpio_init(void)
{
    ppm_gpio_set_next(true);
}

static void ppm_gpio_negative(void)
{
    PORTD.PODR.BIT.B3 = 0;
}

static void ppm_gpio_positive(void)
{
    PORTD.PODR.BIT.B3 = 1;
}

static void ppm_gpio_set_next(bool is_pos)
{
    if(is_pos)
    {
        ppm_gpio_positive();
    }
    else
    {
        ppm_gpio_negative();
    }
}

static void ppm_timer_config(void)
{
    ppm_period_us = 0x05U;
    CMT0.CMCOR = CAL_ARR(PPM_ENCODER_TOTAL_CH_VAL);
}

void ppm_encoder_set_data(ppm_data_t *ppm_data)
{
    memcpy(ppm_data_buf + ppm_data_buf_index, ppm_data, sizeof(ppm_data_t));
    ppm_data_calculate_idle(ppm_data_buf + ppm_data_buf_index);
    ppm_data_buf_index++;
    if(ppm_data_buf_index >= PPM_DATA_BUF_NUM)
    {
        ppm_data_buf_index = 0;
    }
}

static void ppm_data_calculate_idle(ppm_data_t *ppm_data)
{
    uint32_t j;
    uint16_t idle_val = PPM_ENCODER_TOTAL_CH_VAL;
    for(j = 0; j < PPM_ENCODER_CHANNEL_NUM; j++)
    {
        idle_val -= PPM_ENCODER_NEG_CH_VAL;
        idle_val -= ppm_data->ch_val[j];
    }
    idle_val -= PPM_ENCODER_NEG_CH_VAL;
    ppm_data->idle_val = idle_val;
}


static void ppm_data_set_default(ppm_data_t *ppm_data)
{
    uint32_t i;
    for(i = 0; i < PPM_ENCODER_CHANNEL_NUM; i++)
    {
        ppm_data->ch_val[i] = PPM_ENCODER_DEFFAULT_CH_VAL;
    }
    ppm_data_calculate_idle(ppm_data);
}

static void ppm_data_buf_init(void)
{
    uint32_t i;
    ppm_data_buf_index = 0;
    for(i = 0; i < PPM_DATA_BUF_NUM; i++)
    {
        ppm_data_set_default(ppm_data_buf + i);
    }
}

static void ppm_data_shadow_init(void)
{
    ppm_data_shadow_update();
}

void ppm_data_shadow_update(void)
{
    uint32_t i;
    for(i = 0; i < PPM_DATA_BUF_NUM; i++)
    {
        if(i != ppm_data_buf_index)
        {
            memcpy(&ppm_data_shadow, ppm_data_buf + i, sizeof(ppm_data_t));
            break;
        }
    }

    if(i == PPM_DATA_BUF_NUM)
    {
        //impossible
        ppm_data_set_default(&ppm_data_shadow);
    }
    ppm_shadow_state = PPM_STATE_CH_NEG;
    ppm_shadow_ch_idx = 0;
}


static void handle_negative(void)
{
    //ppm_gpio_negative();
    ppm_gpio_set_next(false);
    CMT0.CMCOR = CAL_ARR(PPM_ENCODER_NEG_CH_VAL);
    ppm_shadow_state = PPM_STATE_CH_POS;

}

static void handle_positive(void)
{
    //ppm_gpio_positive();
    ppm_gpio_set_next(true);
    CMT0.CMCOR = CAL_ARR(ppm_data_shadow.ch_val[ppm_shadow_ch_idx]);
    ppm_shadow_ch_idx++;
    if(ppm_shadow_ch_idx >= PPM_ENCODER_CHANNEL_NUM)
    {
        ppm_shadow_state = PPM_STATE_IDLE_NEG;
    }
    else
    {
        ppm_shadow_state = PPM_STATE_CH_NEG;
    }

}

static void handle_idle_neg(void)
{
    //ppm_gpio_negative();
    ppm_gpio_set_next(false);
    CMT0.CMCOR = CAL_ARR(PPM_ENCODER_NEG_CH_VAL);
    ppm_shadow_state = PPM_STATE_IDLE_POS;
}

static void handle_idle_pos(void)
{
    ppm_gpio_set_next(true);
    CMT0.CMCOR = CAL_ARR(ppm_data_shadow.idle_val);
}


bool ppm_data_shadow_one_step(void)
{
    bool should_update = false;

    switch(ppm_shadow_state)
    {
        case PPM_STATE_CH_NEG:
            handle_negative();
            break;
        case PPM_STATE_CH_POS:
            handle_positive();
            break;
        case PPM_STATE_IDLE_NEG:
            handle_idle_neg();
            break;
        case PPM_STATE_IDLE_POS:
            handle_idle_pos();
            //ppm_shadow_state = PPM_STATE_STOP;
            should_update = true;
            break;
        default:
            //impossible
            break;
    }

    return should_update;
}

void set_ppm(uint16_t roll_val,uint16_t pitch_val,uint16_t throttle_val,uint16_t yaw_val,uint16_t mode_val,uint16_t Emergency_val)
{
    if(roll_val)
        ppm_data.ch_val[0]=roll_val - 500;
    if(pitch_val)
        ppm_data.ch_val[1]=pitch_val - 500;
    if(throttle_val)
        ppm_data.ch_val[2]=throttle_val - 500;
    if(yaw_val)
        ppm_data.ch_val[3]=yaw_val - 500;
    if(mode_val)
        ppm_data.ch_val[4]=mode_val - 500;
    ppm_data.ch_val[5]=520;
    ppm_data.ch_val[6]=520;
    if(Emergency_val)
        ppm_data.ch_val[7]=Emergency_val - 500;
    ppm_encoder_set_data(&ppm_data);
}


void CMT0_IntHandler(void)
{
    if(first_time)
    {
        first_time = false;
        return;
    }

    if(ppm_data_shadow_one_step())
    {
        ppm_data_shadow_update();
    }
}
