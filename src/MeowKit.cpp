/**
 * @file rachel.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "MeowKit.h"


// using namespace mooncake;
// static Mooncake* _mooncake = nullptr;

void MeowKit::Setup()
{
    printf("Rachel Setup");
    /* Create bsp */
    _device = new DEVICES;
    if (_device == NULL) {
        printf("[ChappieUI] bsp create failed\n");
    }

    /* Init device */
    _device->init();

    // 初始化IMU
    //_device->imu.begin(); 

    /* Init lvgl */
    // lv_init();
    // lv_port_disp_init(&_device->Lcd);
    // lv_port_indev_init(&_device->ctp);

    /* Init ui */
    // ui_init();
}

void MeowKit::Loop() 
{ 
    // lv_timer_handler();delay(5); 

    // QMI8658A_Data _data;
    
    // if (_device->imu.readRawData(&_data)) {
        
    //     _device->imu.readAngle(&_data);
    //     printf("IMU Angle:%f, %f, %f\n", 
    //            _data.AngleX, _data.AngleY, _data.AngleZ);
    // } else {
    //     printf("Failed to read IMU data\n");
    // }

    // delay(10); 
}

void MeowKit::Destroy()
{

}
