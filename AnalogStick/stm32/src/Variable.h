#pragma once
#include "SerialTransfer.h"

#define pwm_1 PB6
#define pwm_2 PB7
#define pwm_3 PB8
#define pwm_4 PB9

#define mux_1 PA2
#define mux_2 PA3
#define mux_3 PA4
#define mux_4 PA5

#define SPEED 2048

struct STRUCT
{
    int LY, LX, rX, rY;
    bool arUp, arDw, arRt, arLt;
};

extern STRUCT receivedData;
extern SerialTransfer myTransfer;
