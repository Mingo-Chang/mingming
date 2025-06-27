#include "PCF8563.h"
#include <Wire.h>


bool PCF8563::begin() {
    TwoWire* wire = static_cast<TwoWire*>(_wire);
    wire->beginTransmission(_addr);
    return (wire->endTransmission() == 0);
}

bool PCF8563::getTime(RTC_Time &time) {
    TwoWire* wire = static_cast<TwoWire*>(_wire);
    wire->beginTransmission(_addr);
    wire->write(0x02); // 起始寄存器：VL_seconds
    if (wire->endTransmission(false) != 0) return false;
    wire->requestFrom(_addr, (uint8_t)7);

    uint8_t sec = wire->read() & 0x7F;
    uint8_t min = wire->read() & 0x7F;
    uint8_t hour = wire->read() & 0x3F;
    uint8_t day = wire->read() & 0x3F;
    uint8_t weekday = wire->read() & 0x07;
    uint8_t month = wire->read() & 0x1F;
    uint8_t year = wire->read();

    time.sec = bcd2dec(sec);
    time.min = bcd2dec(min);
    time.hour = bcd2dec(hour);
    time.day = bcd2dec(day);
    time.weekday = bcd2dec(weekday);
    time.month = bcd2dec(month);
    time.year = 2000 + bcd2dec(year);

    return true;
}

bool PCF8563::setTime(const RTC_Time &time) {
    TwoWire* wire = static_cast<TwoWire*>(_wire);
    wire->beginTransmission(_addr);
    wire->write(0x02); // 起始寄存器
    wire->write(dec2bcd(time.sec) & 0x7F);
    wire->write(dec2bcd(time.min) & 0x7F);
    wire->write(dec2bcd(time.hour) & 0x3F);
    wire->write(dec2bcd(time.day) & 0x3F);
    wire->write(dec2bcd(time.weekday) & 0x07);
    wire->write(dec2bcd(time.month) & 0x1F);
    wire->write(dec2bcd(time.year % 100));
    return (wire->endTransmission() == 0);
}

uint8_t PCF8563::bcd2dec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

uint8_t PCF8563::dec2bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}