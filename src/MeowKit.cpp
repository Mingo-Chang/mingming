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

    /* Init lvgl */
    lv_init();
    lv_port_disp_init(&_device->Lcd);
    lv_port_indev_init(&_device->ctp);

    /* Init ui */
    ui_init();

}

void MeowKit::Loop() 
{ 
    lv_timer_handler();delay(5); 
}

void MeowKit::Destroy()
{

}
