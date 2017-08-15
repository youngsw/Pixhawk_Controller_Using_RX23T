/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_main.c
* Version      : Code Generator for RX23T V1.00.04.02 [29 Nov 2016]
* Device(s)    : R5F523T5AxFM
* Tool-Chain   : CCRX
* Description  : This file implements main function.
* Creation Date: 2017/8/12
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_icu.h"
#include "r_cg_port.h"
#include "r_cg_mtu3.h"
#include "r_cg_cmt.h"
#include "r_cg_rspi.h"
#include "r_cg_sci.h"
/* Start user code for include. Do not edit comment generated here */
#include "../ppm_encoder/ppm_encoder.h"
#include "../mavlink_receive/mavlink_receive.h"
#include "../matrix_key/matrix_key.h"
#include "../mission_ctl/mission_ctl.h"
#include "../remote_ctl/remote_ctl.h"
#include "../delay/delay.h"
#include "../OLED/OLED.h"
#include "../camera/camera.h"
#include "../PID_control/PID_control.h"
#include "../sonar/sonar.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
bool is_alarm = false;
bool is_drop = false;
float current_height;
float Roll,Pitch,Yaw;
uint8_t dest_height = 0;
uint8_t mission = 0;
unsigned char *start_program[] = {"OLED initialized","Begin In 3 Second","Input Dest Info:"};
/* End user code. Do not edit comment generated here */


static void R_MAIN_UserInit(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    set_ppm(channel_val_MID,channel_val_MID,channel_val_MIN,channel_val_MID,Stabilize,Emergency_ON);
    oled_P6x8Str(0,0,start_program[0]);
    oled_P6x8Str(0,1,start_program[1]);
    delayms(3000);
    oled_P6x8Str(0,2,start_program[2]);
    mission_select();
    display_mission_info();
    mission_execute();

    while (1U)
    {
        ;
    }
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    R_CMT0_Start();         //Level 15
    ppm_encoder_init();
    CMT1_Init();            //Level 15
    R_RSPI0_Start();        //Level 15
    oled_init();
    R_MTU3_C5_Start();      //Level 14
    PID_Init();
    R_CMT2_Start();         //Level 14
    R_CMT3_Start();         //Level 14
    R_ASYNC_Init();         //Level 14
    R_Keyboard_Init();
    remote_ctl_init();      //Level 14
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
