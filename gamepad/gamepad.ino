/**
 * Simple HID gamepad, 32 buttons + 2x 3 axis + 8 position hat
 * author: chegewara
 */


#include "hidgamepad.h"
#if CFG_TUD_HID
HIDgamepad gamepad;

int count = 0;

void setup()
{
    Serial.begin(115200);
    gamepad.begin();
}

void loop()
{
    if (0 == count)
      Serial.write("gamepad in loop()\n");
    delay(1000);
    if(!digitalRead(0)){
        // 32 buttons
        if (2 > count)
          Serial.write("setting button map\n");
        for (size_t i = 0; i < 32; i++)
        {
            // buttons send map of buttons represented by bits
            gamepad.buttons(1<<i);
            delay(100);
        }
        
        // hat 8 positions
        if (2 > count)
          Serial.write("9(?) hat positions\n");
        for (size_t i = 0; i < 9; i++)
        {
            gamepad.hat(i);
            delay(100);
        }

        if (2 > count)
          Serial.write("sendAll zeros\n");
        gamepad.sendAll(0, 0, 0, 0, 0, 0, 0, 0);
        // x, y, z
        if (2 > count)
          Serial.write("joystick1\n");
        gamepad.joystick1(100, -100, 50);
        delay(1000);
        gamepad.joystick1(-100, 100, -50);
        delay(1000);
        // Rx, Ry, Rz
        if (2 > count)
          Serial.write("joystick2\n");
        gamepad.joystick2(100, -100, 50);
        delay(1000);
        gamepad.joystick2(-100, 100, -50);
        delay(1000);
        // Button Map |  X | Y | Z | Rx | Ry | Rz | hat
        if (2 > count)
          Serial.write("sendAll f's\n");
        gamepad.sendAll(0xffffffff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 5);
        delay(1000);
        if (2 > count)
          Serial.write("sendAll zeros\n");
        gamepad.sendAll(0, 0, 0, 0, 0, 0, 0, 0);
    }
    else if (2 == count)
      Serial.write("!digitalRead(0) == false\n");
    count++;
    if (100 < count)
      count = 0;
}

#endif
