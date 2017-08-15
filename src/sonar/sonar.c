/*
 * sonar.c
 *
 *  Created on: Aug 6, 2017
 *      Author: Arthur
 */

#include "sonar.h"

volatile float sonar_height = 0;
static bool First_Int = true;
uint16_t MTU5_Count = 0;

void Calculate_Height(void)
{
    sonar_height = MTU5_Count / 5000000.0 / 2 * 340;      //units: m
}

void MTU5_IntHandler(void)
{
    if(First_Int)
    {
        MTU5_Count = 0;
        MTU5.TGRU = 0x0000;
    }

    if(!First_Int)
    {
        MTU5_Count = MTU5.TGRU;
        Calculate_Height();
    }
    First_Int = !First_Int;
}
