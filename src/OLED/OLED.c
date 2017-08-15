/*
 * OLED.c
 *
 *  Created on: Jul 28, 2017
 *      Author: Arthur
 */

#include "OLED.h"

static /* define ASCII table from space(0x20(32)). */

unsigned char *mission_info[] = {"Mission","Dest_Height","# Executing #"};

const unsigned char F6x8[][6] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // space
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [ 91
    { 0x00, 0x02, 0x04 ,0x08, 0x10, 0x20 },   // \ 92
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horizontal lines
};

#define     OLED_RST_H      PORTB.PODR.BIT.B1 = 1
#define     OLED_RST_L      PORTB.PODR.BIT.B1 = 0
#define     OLED_DC_H       PORTA.PODR.BIT.B3 = 1
#define     OLED_DC_L       PORTA.PODR.BIT.B3 = 0

bool SPI0_flag = true;
static uint32_t temp_buf = 0;

/* private functions declaration. */
static void OLED_WB(uint8_t data);
static void OLED_WrDat(unsigned char dat);
static void OLED_WrCmd(unsigned char cmd);
static void oled_Set_Pos(unsigned char x, unsigned char y);
static void oled_Set_AddressingMode(unsigned char d);
static void oled_Set_StartLine(unsigned char d);
static void oled_Set_ContrastControl(unsigned char d);
static void oled_Set_Charge_Pump(unsigned char d);
static void oled_Set_Segment_Remap(unsigned char d);
static void oled_Set_Entire_Display(unsigned char d);
static void oled_Set_Inverse_Display(unsigned char d);
static void oled_Set_Multiplex_Ratio(unsigned char d);
static void oled_Set_Display_On_Off(unsigned char d);
static void oled_Set_Common_Remap(unsigned char d);
static void oled_Set_Display_Offset(unsigned char d);
static void oled_Set_Display_Clock(unsigned char d);
static void oled_Set_Precharge_Period(unsigned char d);
static void oled_Set_Common_Config(unsigned char d);
static void oled_Set_VCOMH(unsigned char d);

void OLED_delayus(uint16_t _time)
{
    uint8_t temp_i;
    for(; _time > 0; _time --)
        for(temp_i = 0; temp_i < 3; temp_i++)
            ;
}

static void OLED_WB(uint8_t data)
{
    temp_buf = 0;
    temp_buf = (uint32_t)data;
    SPI0_flag = false;
    R_RSPI0_Send(&temp_buf, 1);
    while(!SPI0_flag);
    OLED_delayus(8);
}

static void OLED_WrDat(uint8_t data)
{
    OLED_DC_H;
    OLED_WB(data);
}

static void OLED_WrCmd(uint8_t cmd)
{
    OLED_DC_L;
    OLED_WB(cmd);
}

/* OLED private functions. */
static void oled_Set_Pos(unsigned char x, unsigned char y)
{
    /* PAGE addressing mode */
    OLED_WrCmd(0xb0+(y&0x07));/* set page start address */
    OLED_WrCmd(x&0x0f);/* set lower nibble of the column address */
    OLED_WrCmd(((x&0xf0)>>4)|0x10); /* set higher nibble of the column address */
}

static void oled_Set_AddressingMode(unsigned char d)
{
    OLED_WrCmd(0x20);           // Set Memory Addressing Mode
    OLED_WrCmd(d);          // Default => 0x02
                            // 0x00 => Horizontal Addressing Mode
                            // 0x01 => Vertical Addressing Mode
                            // 0x02 => Page Addressing Mode
}

static void oled_Set_StartLine(unsigned char d)
{
    OLED_WrCmd(0x40|d);     // Set Display Start Line
                            // Default => 0x40 (0x00)
}

static void oled_Set_ContrastControl(unsigned char d)
{
    OLED_WrCmd(0x81);           // Set Contrast Control
    OLED_WrCmd(d);          // Default => 0x7F
}

static void oled_Set_Charge_Pump(unsigned char d)
{
    OLED_WrCmd(0x8D);           // Set Charge Pump
    OLED_WrCmd(0x10|d);     // Default => 0x10
                            // 0x10 (0x00) => Disable Charge Pump
                            // 0x14 (0x04) => Enable Charge Pump
}

static void oled_Set_Segment_Remap(unsigned char d)
{
    OLED_WrCmd(0xA0|d);     // Set Segment Re-Map
                            // Default => 0xA0
                            // 0xA0 (0x00) => Column Address 0 Mapped to SEG0
                            // 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

static void oled_Set_Entire_Display(unsigned char d)
{
    OLED_WrCmd(0xA4|d);     // Set Entire Display On / Off
                            // Default => 0xA4
                            // 0xA4 (0x00) => Normal Display
                            // 0xA5 (0x01) => Entire Display On
}

static void oled_Set_Inverse_Display(unsigned char d)
{
    OLED_WrCmd(0xA6|d);     // Set Inverse Display On/Off
                            // Default => 0xA6
                            // 0xA6 (0x00) => Normal Display
                            // 0xA7 (0x01) => Inverse Display On
}

static void oled_Set_Multiplex_Ratio(unsigned char d)
{
    OLED_WrCmd(0xA8);           // Set Multiplex Ratio
    OLED_WrCmd(d);          // Default => 0x3F (1/64 Duty)
}

static void oled_Set_Display_On_Off(unsigned char d)
{
    OLED_WrCmd(0xAE|d);     // Set Display On/Off
                            // Default => 0xAE
                            // 0xAE (0x00) => Display Off
                            // 0xAF (0x01) => Display On
}

static void oled_Set_Common_Remap(unsigned char d)
{
    OLED_WrCmd(0xC0|d);     // Set COM Output Scan Direction
                            // Default => 0xC0
                            // 0xC0 (0x00) => Scan from COM0 to 63
                            // 0xC8 (0x08) => Scan from COM63 to 0
}

static void oled_Set_Display_Offset(unsigned char d)
{
    OLED_WrCmd(0xD3);           // Set Display Offset
    OLED_WrCmd(d);          // Default => 0x00
}

static void oled_Set_Display_Clock(unsigned char d)
{
    OLED_WrCmd(0xD5);           // Set Display Clock Divide Ratio / Oscillator Frequency
    OLED_WrCmd(d);          // Default => 0x80
                            // D[3:0] => Display Clock Divider
                            // D[7:4] => Oscillator Frequency
}

static void oled_Set_Precharge_Period(unsigned char d)
{
    OLED_WrCmd(0xD9);           // Set Pre-Charge Period
    OLED_WrCmd(d);          // Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
                            // D[3:0] => Phase 1 Period in 1~15 Display Clocks
                            // D[7:4] => Phase 2 Period in 1~15 Display Clocks
}

static void oled_Set_Common_Config(unsigned char d)
{
    OLED_WrCmd(0xDA);           // Set COM Pins Hardware Configuration
    OLED_WrCmd(0x02|d);     // Default => 0x12 (0x10)
                            // Alternative COM Pin Configuration
                            // Disable COM Left/Right Re-Map
}

static void oled_Set_VCOMH(unsigned char d)
{
    OLED_WrCmd(0xDB);           // Set VCOMH Deselect Level
    OLED_WrCmd(d);          // Default => 0x20 (0.77*VCC)
}

void SPI0_TransmitHandler(void)
{
    SPI0_flag = true;
}

void oled_init(void)
{
    OLED_DC_L;
    OLED_RST_L;
    OLED_delayus(50000);
    OLED_delayus(50000);
    OLED_RST_H;

    oled_Set_Display_On_Off(0x00);           // Display Off (0x00/0x01)
    oled_Set_Display_Clock(0x80);           // Set Clock as 100 Frames/Sec
    oled_Set_Multiplex_Ratio(0x3F);         // 1/64 Duty (0x0F~0x3F)
    oled_Set_Display_Offset(0x00);          // Shift Mapping RAM Counter (0x00~0x3F)
    oled_Set_StartLine(0x00);               // Set Mapping RAM Display Start Line (0x00~0x3F)
    oled_Set_Charge_Pump(0x04);             // Enable Embedded DC/DC Converter (0x00/0x04)
    oled_Set_AddressingMode(0x02);          // Set Page Addressing Mode (0x00/0x01/0x02)
    oled_Set_Segment_Remap(0x01);           // Set SEG/Column Mapping     0x00左右反置 0x01正常
    oled_Set_Common_Remap(0x08);            // Set COM/Row Scan Direction 0x00上下反置 0x08正常
    oled_Set_Common_Config(0x10);           // Set Sequential Configuration (0x00/0x10)
    oled_Set_ContrastControl(0xCF);         // Set SEG Output Current
    oled_Set_Precharge_Period(0xF1);        // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    oled_Set_VCOMH(0x40);                   // Set VCOM Deselect Level
    oled_Set_Entire_Display(0x00);          // Disable Entire Display On (0x00/0x01)
    oled_Set_Inverse_Display(0x00);         // Disable Inverse Display On (0x00/0x01)
    oled_Set_Display_On_Off(0x01);          // Display On (0x00/0x01)
    oled_CLS();                             // Clear Screen
    oled_Set_Pos(0,0);
}

/* clear the screen(fill with black). */
void oled_CLS(void)
{
    /********************更新显存到OLED**********************/
    unsigned char y,x;

    for(y=0;y<8;y++)
    {
        OLED_WrCmd(0xb0+y);      //0xb0+0~7表示页0~页7?
        OLED_WrCmd(0x00);        //0x00+0~16表示将128列分成16组其地址在某组中的第几列
        OLED_WrCmd(0x10);        //0x10+0~16表示将128列分成16组其地址所在第几组
        for(x=0;x<128;x++)
            OLED_WrDat(0x00);    //fill screen with 0(black), so the screen is cleared.
    }
    OLED_delayus(50000);
}

/* display a 6*8 standard ASCII character. */
void oled_P6x8Char(unsigned char x,unsigned char y,unsigned char ch)
{
    unsigned char c = 0, i = 0;

    c = ch - 32;
    if (x > 122) {
        x = 0;
        y++;
    }
    oled_Set_Pos(x, y);
    for(i = 0; i < 6; i++) {
        OLED_WrDat(F6x8[c][i]);
    }
}

/* display a set of 6*8 standard ASCII chars. */
void oled_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
    unsigned char c = 0, i = 0, j = 0;
    while (ch[j] != '\0') {
        c = ch[j] - 32;
        if (x > 122) {
            x=0;
            y++;
        }
        oled_Set_Pos(x, y);
        for(i = 0; i < 6; i++) {
            OLED_WrDat(F6x8[c][i]);
        }
        x += 6;
        j++;
    }
}

/* display a char of 3 bits. */
void oled_PrintValueC(unsigned char x, unsigned char y, int8_t data)
{
    unsigned char i, j, k;
    if(data < 0) {
        oled_P6x8Char(x, y, '-');
        data = -data;
    } else {
        oled_P6x8Char(x,y,'+');
    }
    i = data / 100;
    j = (data % 100) / 10;
    k = data % 10;
    oled_P6x8Char(x+6, y, i+48);
    oled_P6x8Char(x+12, y, j+48);
    oled_P6x8Char(x+18, y, k+48);
}

/* display a integer of 5 bits. */
void oled_PrintValueI(unsigned char x, unsigned char y, int data)
{
    unsigned char i, j, k, l, m;
    if(data < 0) {
        oled_P6x8Char(x, y, '-');
        data = -data;
    } else {
        oled_P6x8Char(x, y, '+');
    }

    l  = data / 10000;
    m = (data % 10000) / 1000;
    i = (data % 1000) / 100;
    j = (data % 100) / 10;
    k = data % 10;
    oled_P6x8Char(x+6, y, l+48);
    oled_P6x8Char(x+12, y, m+48);
    oled_P6x8Char(x+18, y, i+48);
    oled_P6x8Char(x+24, y, j+48);
    oled_P6x8Char(x+30, y, k+48);
}

/* display the decimals of a float. */
void oled_PrintValueFP(unsigned char x, unsigned char y, unsigned int data, unsigned char num)
{
    unsigned char m, i, j, k;
    oled_P6x8Char(x, y, '.');
    m = data / 1000;
    i = (data % 1000) / 100;
    j = (data % 100) / 10;
    k = data % 10;
    switch (num) {
    case 1:
        oled_P6x8Char(x+6, y, k+48);
        break;
    case 2:
        oled_P6x8Char(x+6, y, j+48);
        oled_P6x8Char(x+12, y, k+48);
        break;
    case 3:
        oled_P6x8Char(x+6, y, i+48);
        oled_P6x8Char(x+12, y, j+48);
        oled_P6x8Char(x+18, y, k+48);
        break;
    case 4:
        oled_P6x8Char(x+6, y, m+48);
        oled_P6x8Char(x+12, y, i+48);
        oled_P6x8Char(x+18, y, j+48);
        oled_P6x8Char(x+24, y, k+48);
        break;
    }
}

/* display a float with 5 bits of decimals. */
void oled_PrintValueF(unsigned char x, unsigned char y, float data, unsigned char num)
{
   unsigned char l, m, i, j, k;  //万千百十个
   unsigned char databiti = 6; //整数位数
   unsigned int tempdataui = 0;
   int tempdataii = (int)data; //整数部分
   long int tempdatalp = (long int)((data - (int)data) * 10000); //取小数位后4位

   //整数部分显示
   if(data < 0.0000001)
       oled_P6x8Char(x, y, '-');
   else
       oled_P6x8Char(x, y, '+');
   if(tempdataii < 0) tempdataii = -tempdataii;  //去掉整数部分负号
   tempdataui = tempdataii;
   l = tempdataui / 10000;
   m = (tempdataui % 10000) / 1000;
   i = (tempdataui % 1000) / 100;
   j = (tempdataui % 100) / 10;
   k = tempdataui % 10;
   if (l != 0) { //五位
       oled_P6x8Char(x+6,y,l+48);
       oled_P6x8Char(x+12,y,m+48);
       oled_P6x8Char(x+18,y,i+48);
       oled_P6x8Char(x+24,y,j+48);
       oled_P6x8Char(x+30,y,k+48);
   } else if(m != 0) { //四位
       databiti = 5;
       oled_P6x8Char(x+6,y,m+48);
       oled_P6x8Char(x+12,y,i+48);
       oled_P6x8Char(x+18,y,j+48);
       oled_P6x8Char(x+24,y,k+48);
   } else if(i != 0) { //三位
       databiti = 4;
       oled_P6x8Char(x+6,y,i+48);
       oled_P6x8Char(x+12,y,j+48);
       oled_P6x8Char(x+18,y,k+48);
   } else if(j != 0) { //两位
       databiti = 3;
       oled_P6x8Char(x+6,y,j+48);
       oled_P6x8Char(x+12,y,k+48);
   } else {
       databiti = 2;
       oled_P6x8Char(x+6,y,k+48);
   }
   if(tempdatalp < 0)tempdatalp = -tempdatalp;    //去掉小数部分负号
   switch(num) {
       case 0: break;
       case 1: oled_PrintValueFP(x + databiti*6, y, (unsigned int)(tempdatalp / 1000), num); break;
       case 2: oled_PrintValueFP(x + databiti*6, y, (unsigned int)(tempdatalp / 100), num); break;
       case 3: oled_PrintValueFP(x + databiti*6, y, (unsigned int)(tempdatalp / 10), num); break;
       case 4: oled_PrintValueFP(x + databiti*6, y, (unsigned int)(tempdatalp), num); break;
   }
}

void display_mission_info(void)
{
    oled_CLS();
    oled_P6x8Str(0,0,mission_info[0]);
    oled_P6x8Char(122,0,mission);
    oled_P6x8Str(0,1,mission_info[1]);
    oled_PrintValueC(104,1,dest_height);
}

void display_mission_executing(uint8_t y)
{
    oled_P6x8Str(25,y,mission_info[2]);
}
