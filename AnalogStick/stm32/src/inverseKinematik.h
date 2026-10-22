#pragma once
#include "Variable.h"

float inverseKinematik(int x, int y, int r, int sudut)
{
    return ((-x * sin(sudut * DEG_TO_RAD)) + (y * cos(sudut * DEG_TO_RAD)) + (r * SPEED));
}