/*
 * OLED.h
 *
 *  Created on: Jul 28, 2017
 *      Author: Arthur
 */

#ifndef OLED_OLED_H_
#define OLED_OLED_H_


#include <stdint.h>
#include <stdbool.h>
#include "../cg_src/r_cg_macrodriver.h"

#define     BRIGHTNESS      0xCF        //亮度
#define     X_WIDTH         128         //宽度
#define     Y_WIDTH         64          //长度
#define     PAGE            8           //页数
#define     MAX_CHAR_POSX   X_WIDTH-6   //字符宽度需要-6
#define     MAX_CHAR_POSY   Y_WIDTH-6   //字符长度需要-6
#define     DC_PIN          PA3         //pin27
#define     RST_PIN         PB1         //pin25

extern uint8_t dest_height;
extern uint8_t mission;

extern void SPI0_TransmitHandler(void);
extern void oled_init(void);
extern void oled_CLS(void);
extern void oled_P6x8Char(unsigned char x,unsigned char y,unsigned char ch);
extern void oled_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
extern void oled_PrintValueC(unsigned char x, unsigned char y, int8_t data);
extern void oled_PrintValueI(unsigned char x, unsigned char y, int data);
extern void oled_PrintValueFP(unsigned char x, unsigned char y, unsigned int data, unsigned char num);
extern void oled_PrintValueF(unsigned char x, unsigned char y, float data, unsigned char num);
extern void display_mission_info(void);
extern void display_mission_executing(uint8_t y);
#endif /* OLED_OLED_H_ */
