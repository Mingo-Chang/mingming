/**
 * @file 
 * @author 
 * @brief
 * @version 
 * @date 
 *
 * @copyright
 *
 */
#pragma once
#include "porting/touch.hpp"
#include "porting/display.hpp"
#include "button/button.hpp"
#include "imu/QMI8658A.h"
#include "sd/sd.hpp"
#include "audio/audio_es.h" 
#include "rtc/pcf8563.h"
#include <PCA9557.h>
#include <BleMouse.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>

class DEVICES
{
private:

public:
    CTP         ctp;
    LGFX        Lcd;
    Button   button;
    QMI8658A    imu;
    SDMMC_SD     sd;
    PCA9557      io;
    Audio     audio;
    BleMouse bleMouse;
    PCF8563     pcf;

    DEVICES() : io(0x19, &Wire), pcf(PCF8563_ADDR,&Wire) {}
    ~DEVICES() {}   
    /**
     * @brief 初始化设备
     * 
     */
    void init();
    int getBatteryPercent();
};