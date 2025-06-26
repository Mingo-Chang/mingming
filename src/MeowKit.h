#pragma once
#include <PCA9557.h>
#include "lvgl.h"
#include "ui/ui.h"
#include <mooncake.h>
#include "bsp/devices.h"
#include "bsp/porting/lv_port_disp.h"
#include "bsp/porting/lv_port_indev.h"
#include "bsp/imu/QMI8658A.h"
#include <cstdio>
#include <mooncake.h>

using namespace mooncake;


class MeowKit
{
    private:
        DEVICES* _device = nullptr; // Bsp devices
    public:
        void Setup();
        void Loop();
        void Destroy();
};