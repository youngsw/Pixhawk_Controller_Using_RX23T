/*
 * mission_control.c
 *
 *  Created on: Jul 27, 2017
 *      Author: Arthur
 */

#include "mission_ctl.h"

bool mission_start = false;

void arm(uint16_t flight_mode)
{
//    delayms(5000);
    set_ppm(channel_val_MID,channel_val_MID,channel_val_MIN,channel_val_MAX,flight_mode,Emergency_OFF);
    delayms(3000);
    set_ppm(channel_val_MID,channel_val_MID,channel_val_MIN,channel_val_MID,flight_mode,Emergency_OFF);
    delayms(1000);
}

void disarm(void)
{
    set_ppm(channel_val_MID,channel_val_MID,channel_val_MIN,channel_val_MID,Stabilize,Emergency_ON);
}

void is_Emergency(void)
{
    mission_start = false;
    set_ppm(channel_val_MID,channel_val_MID,channel_val_MIN,channel_val_MID,Stabilize,Emergency_ON);
    LEDR = LED_ON;
    while(1);
}

void read_dest_height(void)
{
    bool end_of_input = false;
    while(!end_of_input)
    {
reinput:
        dest_height = 100;
        dest_height = read_one_number() * 100 + read_one_number() * 10 + read_one_number();
confirm:switch(read_one_number())
        {
        case 0x2A:
            goto reinput;
        case 0x23:
            end_of_input = true;
            break;
        default:
            goto confirm;
        }
    }
}

void alt_hold(void)
{
    while(!mission_start);
    display_mission_executing(3);
    arm(Alt_Hold);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(20),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(55),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(60),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    while(sonar_height * 100 < dest_height)
    {
        if (sonar_height > 0.25)
        {
            start_PID_X = true;
            start_PID_Y = true;
        }
        set_ppm(0,0,(channel_percent(61) + 2 * (dest_height - sonar_height * 100)),channel_val_MID,Alt_Hold,Emergency_OFF);
    }
    set_ppm(0,0,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    start_PID_H = true;
    delayms(10000);
    start_PID_H = false;
    while(sonar_height > 0.1)
    {
        set_ppm(0,0,channel_percent(39),channel_val_MID,Alt_Hold,Emergency_OFF);
        if(sonar_height < 0.4)
        {
            set_ppm(0,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
            break;
        }
    }
    while(sonar_height > 0.1)
        set_ppm(0,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
    start_PID_X = false;
    start_PID_Y = false;
    disarm();
}

void fix_car(void)
{
    while(!mission_start);
    display_mission_executing(3);
    arm(Alt_Hold);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(20),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(55),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(60),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    while(sonar_height * 100 < dest_height)
    {
        if (sonar_height > 0.25)
        {
            start_PID_X = true;
            set_ppm(0,(channel_val_MID - channel_val_RANGE*4/100),0,channel_val_MID,Alt_Hold,Emergency_OFF);
        }
        set_ppm(0,0,(channel_percent(61) + 2 * (dest_height - sonar_height * 100)),channel_val_MID,Alt_Hold,Emergency_OFF);
    }
    set_ppm(0,0,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    start_PID_H = true;

    delayms(1300);
    SET_FIX_GREEN;
    start_PID_Y = true;

    delayms(10000);
    start_PID_H = false;
    while(sonar_height > 0.1)
    {
        set_ppm(0,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
        if(sonar_height < 0.6)
        {
            set_ppm(0,(channel_val_MID - channel_val_RANGE*8/100),0,0,Alt_Hold,Emergency_OFF);
            break;
        }
    }
    start_PID_X = false;
    start_PID_Y = false;
    while(sonar_height > 0.2)
        set_ppm(0,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
    while(sonar_height > 0.1)
        set_ppm(channel_val_MID,channel_val_MID,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
    disarm();
}

void chase_car(void)
{
    while(!mission_start);
    display_mission_executing(3);
    arm(Alt_Hold);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(20),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(55),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(60),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    while(sonar_height * 100 < dest_height)
    {
        if (sonar_height > 0.25)
        {
            start_PID_X = true;
            set_ppm(0,(channel_val_MID - channel_val_RANGE*4/100),0,channel_val_MID,Alt_Hold,Emergency_OFF);
        }
        set_ppm(0,0,(channel_percent(61) + 2 * (dest_height - sonar_height * 100)),channel_val_MID,Alt_Hold,Emergency_OFF);
    }
    set_ppm(0,0,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    start_PID_H = true;

    delayms(1300);
    SET_FIX_GREEN;
    start_PID_Y = true;

    while(!is_drop);
    LEDB = LED_ON;
    delayms(6000);
    start_PID_H = false;
    while(sonar_height > 0.1)
    {
        set_ppm(0,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
        if(sonar_height < 0.6)
        {
            set_ppm(0,(channel_val_MID + channel_val_RANGE*8/100),0,0,Alt_Hold,Emergency_OFF);
            break;
        }
    }
    start_PID_X = false;
    start_PID_Y = false;
    while(sonar_height > 0.2)
        set_ppm(0,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
    while(sonar_height > 0.1)
        set_ppm(channel_val_MID,channel_val_MID,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
    disarm();
}

void stunt(void)
{
    while(!mission_start);
    display_mission_executing(3);
    arm(Alt_Hold);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(20),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(55),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    set_ppm(channel_val_MID,channel_val_MID,channel_percent(60),channel_val_MID,Alt_Hold,Emergency_OFF);
    delayms(500);
    while(sonar_height * 100 < dest_height)
    {
        if (sonar_height > 0.25)
        {
            start_PID_X = true;
            start_PID_Y = true;
        }
        set_ppm(0,0,(channel_percent(61) + 2 * (dest_height - sonar_height * 100)),channel_val_MID,Alt_Hold,Emergency_OFF);
    }
    SET_FIX_GREEN;
    set_ppm(0,0,channel_percent(50),channel_val_MID,Alt_Hold,Emergency_OFF);
    start_PID_H = true;
    while(!is_drop);
    delayms(8000);
    start_PID_H = false;
    while(sonar_height > 0.1)
    {
        set_ppm(0,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
        if(sonar_height < 0.5)
        {
            set_ppm(0,(channel_val_MID + channel_val_RANGE*8/100),0,0,Alt_Hold,Emergency_OFF);
            break;
        }
    }
    start_PID_X = false;
    start_PID_Y = false;
    while(sonar_height > 0.1)
        set_ppm(channel_val_MID,0,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
    while(sonar_height > 0.1)
        set_ppm(channel_val_MID,channel_val_MID,channel_percent(35),channel_val_MID,Alt_Hold,Emergency_OFF);
    disarm();

}

void mission_select(void)
{
    mission = 0;
reget:
    mission = read_one_number();
    switch(mission)
    {
    case 0x41:
        delayms(500);
        read_dest_height();
        break;

    case 0x42:
        delayms(500);
        read_dest_height();
        break;

    case 0x43:
        delayms(500);
        read_dest_height();
        break;

    case 0x44:
        delayms(500);
        read_dest_height();
        break;

    default:
        goto reget;
    }
}

void mission_execute(void)
{
    switch(mission)
    {
    case 0x41:
        LEDB = LED_ON;
        alt_hold();
        break;

    case 0x42:
        LEDB = LED_ON;
        fix_car();
        break;

    case 0x43:
        LEDB = LED_ON;
        chase_car();
        break;

    case 0x44:
        LEDB = LED_ON;
        stunt();
        break;
    }
}
