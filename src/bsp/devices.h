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
#include "audio/audio.hpp"
#include <PCA9557.h>

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

    void init();
    void printBspInfos();
};