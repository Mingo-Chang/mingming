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

    /* Create launcher */
    _launcher = std::unique_ptr<Launcher>(new Launcher(_device));
    _launcher->onCreate();
    
}

void MeowKit::Loop() 
{    
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
