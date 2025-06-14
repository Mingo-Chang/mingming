/**
 * @file hal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <mooncake.h>
#include "hal.h"

HAL* HAL::_hal = nullptr;

HAL* HAL::Get() { return _hal; }

bool HAL::Check() { return _hal != nullptr; }

bool HAL::Inject(HAL* hal)
{
    if (_hal != nullptr)
    {
        printf("HAL already exist");
        return false;
    }

    if (hal == nullptr)
    {
        printf("invalid HAL ptr");
        return false;
    }

    hal->init();
    printf("HAL injected, type: {}", hal->type());

    _hal = hal;

    return true;
}

void HAL::Destroy()
{
    if (_hal == nullptr)
    {
        printf("HAL not exist");
        return;
    }

    delete _hal;
    _hal = nullptr;
}



// Cpp sucks
tm* HAL::getLocalTime()
{
    time(&_time_buffer);
    return localtime(&_time_buffer);
}


void HAL::updateSystemFromConfig()
{
    // Brightness
    _display->setBrightness(_config.brightness);

    // Volume
    setBeepVolume(_config.volume);
}