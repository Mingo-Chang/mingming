#pragma once
#include <PCA9557.h>
#include "lvgl.h"
#include "ui/ui.h"
#include <mooncake.h>
#include "bsp/devices.h"
#include "bsp/porting/lv_port_disp.h"
#include "bsp/porting/lv_port_indev.h"
#include "bsp/imu/QMI8658A.h"


class MeowKit
{
    private:
        DEVICES* _device;
        QMI8658A* _imu = nullptr; // IMU sensor
    public:
        void Setup();
        void Loop();
        void Destroy();
};