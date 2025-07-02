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

    _launcher = std::make_unique<Launcher>(_device);
    _launcher->onCreate();

    // /* Init lvgl */
    // lv_init();
    // lv_port_disp_init(&_device->Lcd);
    // lv_port_indev_init(&_device->ctp);

    // /* Init ui */
    // ui_init();

    
}

void MeowKit::Loop() 
{ 
    
    // lv_timer_handler();  // 处理 LVGL
    // delay(5);  // 延时，防止 CPU 占用过高
    // GetMooncake().update();  // Mooncake 状态调度
    _launcher->onloop();

}

void MeowKit::Destroy()
{
    if (_device != nullptr)
        {
            delete _device;
            _device = nullptr;
            /* code */
        }
}
