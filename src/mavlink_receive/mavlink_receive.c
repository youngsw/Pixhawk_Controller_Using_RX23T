/*
 * mavlink_receive.c
 *
 *  Created on: Jul 14, 2017
 *      Author: Arthur
 */

#include "mavlink_receive.h"
#include <stdint.h>
#include <stdbool.h>

union {
    float sub_float;
    uint8_t buf[4];
} uchar_float;

union{
    float sub_float;
    uint8_t buf[4];
} float_uchar;

uint8_t Height_Buffer[20];
uint8_t Angle_Buffer[40];
uint8_t Rx_Buffer_height[20];
uint8_t Rx_Buffer_angle[40];
uint8_t rx_buffer = 23;

uint8_t g1_rx_char;

bool start_receive_height = false;
bool start_receive_angle = false;
bool is_Height = false;
bool is_Angle = false;

float angle[3];

static float uchar_to_float(uint8_t *buffer)
{
    uchar_float.buf[0] = *(buffer);
    uchar_float.buf[1] = *(buffer+1);
    uchar_float.buf[2] = *(buffer+2);
    uchar_float.buf[3] = *(buffer+3);
    return(uchar_float.sub_float);
}

void calculate_height(float *height)
{
    *height=uchar_to_float(Height_Buffer+6);


    return;

}

void calculate_angle(float * angle)
{
    Roll = uchar_to_float(Angle_Buffer+10)/(2*pi)*360.0;
    Pitch = uchar_to_float(Angle_Buffer+14)/(2*pi)*360.0;
    Yaw = uchar_to_float(Angle_Buffer+18)/(2*pi)*360.0+360;

    Yaw=Yaw > 360 ? Yaw-360 : Yaw;


    angle[0]=Roll;
    angle[1]=Pitch;
    angle[2]=Yaw;

    return;
}

//void SCI1_IntHandler(void)
//{
//    static uint8_t i = 0,j = 0;
//    if ( g1_rx_char == MAVLINK_STX)
//    {
//        i=0,j=0;
//        start_receive_height = 1;
//        start_receive_angle= 1;
//    }
//    if(start_receive_height == 1)
//    {
//        Rx_Buffer_height[i++]=g1_rx_char;
//        if(i == MSG_HEIGHT_LENGTH && Rx_Buffer_height[1] == MSG_SONAR_LENGTH && Rx_Buffer_height[5] == MSG_SONAR_ID && Rx_Buffer_height[15] != 0 )
//        {
//            memcpy(Height_Buffer,Rx_Buffer_height,MSG_HEIGHT_LENGTH);
//            is_Height = true;
//        }
//
//        if( i >= MSG_HEIGHT_LENGTH )
//        {
//            i = 0;
//            start_receive_height = 0;
//            memset(Rx_Buffer_height,0,20);
//        }
//    }
//    if(start_receive_angle == 1)
//    {
//        Rx_Buffer_angle[j++] = g1_rx_char;
//        if(j == MSG_ANGLE_LENGTH && Rx_Buffer_angle[1] == MSG_ATTITUDE_LENGTH && Rx_Buffer_angle[5] == MSG_ATTITUDE_ID && Rx_Buffer_angle[35] != 0 )
//        {
//            memcpy(Angle_Buffer,Rx_Buffer_angle,MSG_ANGLE_LENGTH);
//            is_Angle = true;
//        }
//
//        if(j >= MSG_ANGLE_LENGTH)
//        {
//            j = 0;
//            start_receive_angle =0;
//            memset(Rx_Buffer_angle,0,40);
//        }
//    }
//    if(is_Height)
//    {
//        LEDR = LED_ON;
//        is_Height=false;
//        calculate_height(&current_height);
//        LEDR = LED_OFF;
//    }//height calculate end
//    if(is_Angle)
//    {
//        is_Angle=false;
//        calculate_angle(angle);
//    }   //angle calculate end
//    R_SCI1_Serial_Receive((uint8_t *)&g1_rx_char, 1);
//}

void SCI1_IntHandler(void)
{
    setpsw_i();
    switch(g1_rx_char)
    {
    case 0xab:
        mission_start = true;
        LEDB = LED_OFF;
        break;
    case 0xac:
        is_Emergency();
        break;
    case 0xad:
        is_drop = true;
        break;
    default:
        break;
    }
    R_SCI1_Serial_Receive((uint8_t *)&g1_rx_char, 1);
}
