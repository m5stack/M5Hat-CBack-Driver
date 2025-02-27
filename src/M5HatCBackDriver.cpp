/*
 *SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 *SPDX-License-Identifier: MIT
 */

#include "M5HatCBackDriver.h"

bool M5HatCBackDriver::begin(TwoWire* wire, uint8_t addr)
{
    _wire = wire;
    _addr = addr;
    int error;
    _wire->beginTransmission(addr);
    error = _wire->endTransmission();
    if (error == 0) {
        return true;
    }
    return false;
}

bool M5HatCBackDriver::write1Byte(uint8_t address, uint8_t reg, uint8_t data)
{
    _wire->beginTransmission(address);
    _wire->write(reg);
    _wire->write(data);
    _wire->endTransmission();
    if (_wire->endTransmission() == 0) return true;
    return false;
}

bool M5HatCBackDriver::write2Byte(uint8_t address, uint8_t reg, uint16_t data)
{
    _wire->beginTransmission(address);
    _wire->write(reg);
    _wire->write(data >> 8);    // MSB
    _wire->write(data & 0xFF);  // LSB
    if (_wire->endTransmission() == 0) return true;
    return false;
}

bool M5HatCBackDriver::readBytes(uint8_t address, uint8_t reg, uint8_t count, uint8_t* dest)
{
    _wire->beginTransmission(address);  // Initialize the Tx buffer
    _wire->write(reg);                  // Put slave register address in Tx buffer
    uint8_t i = 0;
    if (_wire->endTransmission(false) == 0 && _wire->requestFrom(address, (uint8_t)count)) {
        while (_wire->available()) {
            dest[i++] = _wire->read();
        }
        return true;
    }
    return false;
}

/*******************************************************************************/

bool M5HatCBackDriver::setServoAngle(uint8_t ch, uint8_t angle)
{
    if (ch > 3) return false;
    uint8_t reg = ch;
    return write1Byte(_addr, reg, angle);
}

bool M5HatCBackDriver::setServoPulse(uint8_t ch, uint16_t width)
{
    if (ch > 3) return false;
    uint8_t reg = (2 * ch + 16);
    if (reg % 2 == 1 || reg > 32) return 1;
    return write2Byte(_addr, reg, width);
}

int M5HatCBackDriver::getServoAngle(uint8_t ch)
{
    uint8_t data = 0;
    uint8_t reg  = ch;
    if (readBytes(_addr, reg, 1, &data)) {
        return data;
    };
    return -1;
}

int M5HatCBackDriver::getServoPulse(uint8_t ch)
{
    uint8_t data[2];
    uint8_t reg = (2 * ch | 0x10);
    if (readBytes(_addr, reg, 2, data)) {
        return (data[0] << 8) + data[1];
    };
    return -1;
}

int M5HatCBackDriver::analogReadPortB()
{
    uint8_t data[2];
    if (readBytes(_addr, 0x20, 2, data)) {
        return (data[0] << 8) + data[1];
    };
    return -1;
}

bool M5HatCBackDriver::digitalWritePortB(uint8_t status)
{
    return write1Byte(_addr, 0x30, status);
}

int M5HatCBackDriver::digitalReadPortB()
{
    uint8_t data;
    if (readBytes(_addr, 0x31, 1, &data)) {
        return data;
    }
    return -1;
}
