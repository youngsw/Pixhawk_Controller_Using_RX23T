/*
 * matrix_key.c
 *
 *  Created on: Jul 26, 2017
 *      Author: Arthur
 */
#include "matrix_key.h"

uint8_t keyboard[] = {0x01,0x02,0x03,0x41,
                      0x04,0x05,0x06,0x42,
                      0x07,0x08,0x09,0x43,
                      0x2A,0x00,0x23,0x44
};
void R_Keyboard_Init(void)
{
    PORT2.PODR.BIT.B3 = 1;
    PORT3.PODR.BIT.B0 = 1;
    PORT3.PODR.BIT.B1 = 1;
    PORT3.PODR.BIT.B2 = 1;
}

void R_PORT_Row_Write(uint8_t row_val)
{
    switch(row_val)
    {
    case 0x00:
        PORT2.PODR.BIT.B3 = 0;
        PORT3.PODR.BIT.B0 = 1;
        PORT3.PODR.BIT.B1 = 1;
        PORT3.PODR.BIT.B2 = 1;
        break;
    case 0x01:
        PORT2.PODR.BIT.B3 = 1;
        PORT3.PODR.BIT.B0 = 0;
        PORT3.PODR.BIT.B1 = 1;
        PORT3.PODR.BIT.B2 = 1;
        break;
    case 0x02:
        PORT2.PODR.BIT.B3 = 1;
        PORT3.PODR.BIT.B0 = 1;
        PORT3.PODR.BIT.B1 = 0;
        PORT3.PODR.BIT.B2 = 1;
        break;
    case 0x03:
        PORT2.PODR.BIT.B3 = 1;
        PORT3.PODR.BIT.B0 = 1;
        PORT3.PODR.BIT.B1 = 1;
        PORT3.PODR.BIT.B2 = 0;
        break;
    default:
        break;
    }
}

uint8_t R_PORT_Col_Read(void)
{
    uint8_t Col = 0;
    Col = PORT7.PIDR.BYTE & 0x35;       //00110101
    switch(Col)
    {
    case 0x34:                          //00110100
        Col = 1;
        break;
    case 0x31:                          //00110001
        Col = 2;
        break;
    case 0x25:                          //00100101
        Col = 3;
        break;
    case 0x15:                          //00010101
        Col = 4;
        break;
    default:
        Col = 0;
        break;
    }
    return Col;
}

uint8_t read_one_number(void)
{
    uint8_t i = 0;
    uint8_t row_val = 0;
    uint8_t col_val = 0;
    while(1)
    {
        LEDG = LED_ON;
        row_val = i%4;
        R_PORT_Row_Write(row_val);
        col_val = R_PORT_Col_Read();
        if(col_val)
        {
            delayms(200);
            LEDG = LED_OFF;
            if(col_val == R_PORT_Col_Read())
            {
                /* wait for button is loosen. */
                while(R_PORT_Col_Read() == col_val);
                LEDG = LED_ON;
                delayms(500);
                LEDG = LED_OFF;
                delayms(500);
                break;
            }
        }
        i++;
    }
    return keyboard[row_val*4 + col_val - 1];

}
