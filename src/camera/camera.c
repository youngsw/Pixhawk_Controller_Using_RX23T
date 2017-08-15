/*
 * camera.c
 *
 *  Created on: Jul 31, 2017
 *      Author: Arthur
 */

#include "camera.h"

uint8_t g5_rx_char;
bool start_receive = false;
volatile uint8_t get_x = CAMERA_MID_X, get_y = CAMERA_MID_Y;

void SCI5_IntHandler(void)
{
    static uint8_t i = 0;
    if (g5_rx_char == ALARM_STX && is_alarm == false && sonar_height > 0.5 && sonar_height < 1.5)
    {
        is_alarm = true;
    }
    if ((g5_rx_char == ALARM_END && is_alarm == true) || sonar_height < 0.5 || sonar_height > 1.5)
    {
        is_alarm = false;
    }
    if (g5_rx_char == CAMERA_STX)
    {
        start_receive = true;
        goto END;
    }
    if (start_receive)
    {
        i++;
        if (i == 1)
        {
            if (g5_rx_char < CAMERA_W)
            {
                get_x = g5_rx_char;
            }
            else
            {
                i = 0;
                start_receive = false;
                goto END;
            }
        }
        if (i == 2)
        {
            if (g5_rx_char < CAMERA_H)
            {
                get_y = g5_rx_char;
            }
            i = 0;
            start_receive = false;
        }
    }
END:
    R_SCI5_Serial_Receive(&g5_rx_char, 1);
}
