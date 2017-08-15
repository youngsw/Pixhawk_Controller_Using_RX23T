/*
 * delay.c
 *
 *  Created on: Jul 27, 2017
 *      Author: Arthur
 */
#include "delay.h"

uint8_t time_flag = 0;
uint16_t time_count = 0;

void CMT1_Init(void)
{
    R_CMT1_Start();
}

bool delayms(uint16_t time)
{
    time_flag = 1;
    while(time_count != time);
    time_flag = 0;
    time_count = 0;
    return true;
}

void CMT1_IntHandler(void)
{
    time_count += time_flag;
}
