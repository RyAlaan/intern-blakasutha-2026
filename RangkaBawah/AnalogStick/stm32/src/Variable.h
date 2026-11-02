#pragma once
#include "SerialTransfer.h"

#define pwm_1 PB9
#define pwm_2 PB8
#define pwm_3 PB7
#define pwm_4 PB6

#define mux_1 PA5
#define mux_2 PA2
#define mux_3 PA3
#define mux_4 PA4

#define SPEED 2048

struct STRUCT
{
    int LY, LX, rX, rY;
    bool arUp, arDw, arRt, arLt;
};

extern STRUCT receivedData;
extern SerialTransfer myTransfer;
