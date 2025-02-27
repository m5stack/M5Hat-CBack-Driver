/*
 *SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 *SPDX-License-Identifier: MIT
 */

#ifndef _M5_HAT_CBACK_DRIVER_H_
#define _M5_HAT_CBACK_DRIVER_H_

#include "Arduino.h"
#include "Wire.h"

#define M5_HAT_CBACK_DRIVER_I2C_ADDR 0x38

class M5HatCBackDriver {
private:
private:
    TwoWire* _wire;
    uint8_t _addr;
    bool write1Byte(uint8_t address, uint8_t reg, uint8_t data);
    bool write2Byte(uint8_t address, uint8_t reg, uint16_t data);
    bool readBytes(uint8_t address, uint8_t reg, uint8_t count, uint8_t* dest);

public:
    /**
     * @brief Initializes the Hat Back Driver with I2C Bus communication parameters.
     *
     * @param wire wire Pointer to a TwoWire object, defaults to TwoWire(0)
     * @param addr device i2c addr, defaults to 0x38
     * @return bool True if the device was successfully initialized, otherwise False.
     */
    bool begin(TwoWire* wire = &Wire, uint8_t addr = M5_HAT_CBACK_DRIVER_I2C_ADDR);

    /**
     * @brief Set the Servo Angle
     *
     * @param ch 0-3
     * @param angle  0-180 degree
     * @return bool True write success, otherwise False
     */
    bool setServoAngle(uint8_t ch, uint8_t angle);

    /**
     * @brief Set the Servo Pulse
     *
     * @param ch 0-3
     * @param width 500-2500us
     * @return bool True write success, otherwise False
     */
    bool setServoPulse(uint8_t ch, uint16_t width);

    /**
     * @brief Get the Servo Angle
     *
     * @param ch 0-3
     * @return int error: -1, angle: 0-180 degree
     */
    int getServoAngle(uint8_t ch);

    /**
     * @brief Get the Servo Pulse
     *
     * @param ch 0-3
     * @return int error: -1, pulse: 500-2500us
     */
    int getServoPulse(uint8_t ch);

    /**
     * @brief Read the Grove Port B Analog Input Value
     *
     * @return int error: -1, analog value: 0-4095
     */
    int analogReadPortB();

    /**
     * @brief Write the Grove Port B Digital Output Value
     *
     * @param status
     * @return bool True write success, otherwise False
     */
    bool digitalWritePortB(uint8_t status);

    /**
     * @brief Read the Grove Port B Digital Input Value
     *
     * @return int error: -1, low: 0, high: 1
     */
    int digitalReadPortB();
};
#endif
