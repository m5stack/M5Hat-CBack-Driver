/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * @Hardwares: StickC/StickC-Plus/StickC-Plus2 + Hat CBack Driver
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5Hat-CBack-Driver:https://github.com/m5stack/M5Hat-CBack-Driver
 */

#include <M5Unified.h>
#include "M5HatCBackDriver.h"

M5HatCBackDriver driver;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    Wire.begin(0, 26);
    M5.Display.setFont(&fonts::FreeMonoBold9pt7b);
    M5.Display.setRotation(1);
    while (!driver.begin(&Wire, M5_HAT_CBACK_DRIVER_I2C_ADDR)) {
        M5.Display.fillScreen(YELLOW);
        Serial.println("Hat CBack Driver Init Fail");
        M5.Display.setCursor(0, 0);
        M5.Display.println("Hat CBack Driver Init Fail");
        delay(1000);
    };
    M5.Display.setCursor(0, 0);
    M5.Display.fillScreen(GREEN);
    Serial.println("Hat CBack Driver Init OK");
    M5.Display.println("Hat CBack Driver Init OK");
    M5.Display.println("Start Control Servo");
}

void loop()
{
    for (int i = 0; i <= 3; i++) {   // channel 0-3
        driver.setServoAngle(i, 0);  // 0-180 degree
        // driver.setServoPulse(i,500); // 500-2500us
        delay(200);
    }
    for (int i = 0; i <= 3; i++) {     // channel 0-3
        driver.setServoAngle(i, 180);  // 0-180 degree
        // driver.setServoPulse(i,2500);  // 500-2500us
        delay(200);
    }
    driver.digitalWritePortB(1);
    delay(1000);
    driver.digitalWritePortB(0);
    Serial.print("PortB Analog Read: ");
    Serial.println(driver.analogReadPortB());
}
