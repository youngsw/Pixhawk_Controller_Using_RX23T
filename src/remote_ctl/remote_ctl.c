/*
 * remote_ctl.c
 *
 *  Created on: Jul 27, 2017
 *      Author: Arthur
 */

#include "remote_ctl.h"

char Alarm_On[] = {0xef,0xe1};
char Alarm_Off[] = {0xef,0xe0};

char str[] = {'0','0','0','\t','0','0','0','\t','0','0','0','\n'};

uint8_t sonar = 0;
bool sci5_trans = false;

void SCI5_TransIntHandler(void)
{
    sci5_trans = true;
}

void remote_ctl_init(void)
{
    R_ICU_IRQ0_Start();
    R_ICU_IRQ1_Start();
}

void IRQ0_IntHandler(void)
{
    mission_start = true;
    LEDB = LED_OFF;
}

void IRQ1_IntHandler(void)
{
    setpsw_i();
    is_Emergency();
}

void hex_to_char(uint8_t hex_1, uint8_t hex_2, float height)
{
    sonar = (uint8_t)(height * 100);
    str[0] = hex_1 / 100 + 48;
    str[1] = (hex_1 % 100) / 10 + 48;
    str[2] = hex_1 % 10 + 48;
    str[4] = hex_2 / 100 + 48;
    str[5] = (hex_2 % 100) / 10 + 48;
    str[6] = hex_2 % 10 + 48;
    str[8] = sonar / 100 + 48;
    str[9] = (sonar % 100) / 10 + 48;
    str[10] = sonar % 10 + 48;
}

void CMT3_IntHandler(void)
{
    static uint8_t alarm_count = 0;
    setpsw_i();
    hex_to_char(get_x,get_y,sonar_height);
    R_SCI5_Serial_Send(str,12);
    while(!sci5_trans);
    sci5_trans = false;
    if(alarm_count / 10)
    {
        if(is_alarm)
        {
            R_SCI5_Serial_Send(Alarm_On,2);
            while(!sci5_trans);
            PORT4.PODR.BIT.B2 = ~PORT4.PIDR.BIT.B2;     //ALARM_LED_GPIO
            PORT4.PODR.BIT.B4 = ~PORT4.PIDR.BIT.B4;     //BUZZER_GPIO
        }
        if(!is_alarm)
        {
            R_SCI5_Serial_Send(Alarm_Off,2);
            while(!sci5_trans);
            PORT4.PODR.BIT.B2 = 0;
            PORT4.PODR.BIT.B4 = 0;
        }
        alarm_count = 0;
    }
    alarm_count++;
}
