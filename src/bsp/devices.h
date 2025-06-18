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
#include <PCA9557.h>

class DEVICES
{
private:

public:
    CTP         ctp;
    LGFX        Lcd;
    Button   button;
    QMI8658A    imu;
    PCA9557      io;
    SDMMC_SD     sd;


    void init();
    void printBspInfos();
};