#pragma once

int deadzone(int val, int threshold = 10)
{
  return abs(val) < threshold ? 0 : val;
}

int mapJoystick(int raw, int center = 132)
{
  if (raw == center)
    return 0;
  if (raw < center)
    return map(raw, 0, center, -127, 0);
  else
    return map(raw, center, 255, 0, 127);
}