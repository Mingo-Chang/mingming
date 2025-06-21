#pragma once
#include <Arduino.h>

// PCF8563 I2C地址
#define PCF8563_ADDR 0x51

struct RTC_Time {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t weekday;
    uint8_t month;
    uint16_t year; // 4位年份
};

class PCF8563 {
public:
    // 只声明为void*，不直接依赖TwoWire类型
    PCF8563(void* wire, uint8_t addr = PCF8563_ADDR);

    bool begin();
    bool getTime(RTC_Time &time);
    bool setTime(const RTC_Time &time);

private:
    void* _wire;    // 实际使用时需强转为TwoWire*
    uint8_t _addr;

    uint8_t bcd2dec(uint8_t val);
    uint8_t dec2bcd(uint8_t val);
};