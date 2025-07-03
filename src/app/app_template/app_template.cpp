/**
 * @file app_template.cpp
 * @author Mingo
 * @brief App template implementation for Mooncake
 * @version 0.1
 * @date 2025-06-03
 * @copyright Copyright (c) 2025
 */

#include "app_template.h"
#include <iostream>

namespace MOONCAKE::APPS
{
    AppTemplate::AppTemplate(DEVICES* device)
        : _device(device)
    {
        setAppInfo().name = "AppTemplate";
    }

    void AppTemplate::onOpen()
    {
        _device->Lcd.init();
        _device->Lcd.fillScreen(TFT_BLACK);
        matrix_effect.init(&_device->Lcd);
        matrix_effect.setup(
        10 /* Line Min */, 
        30,  /* Line Max */
        5,  /* Speed Min */
        25,  /* Speed Max */
        30  /* Screen Update Interval */);  
    }

    void AppTemplate::onRunning()
    {
        matrix_effect.loop();
    }

    void AppTemplate::onClose()
    {
        // 重置动画对象，释放其内部资源
        matrix_effect = DigitalRainAnimation<Meow_LGFX>();

        // 清空屏幕，防止残影
        if (_device && _device->Lcd.width() > 0 && _device->Lcd.height() > 0) {
            _device->Lcd.fillScreen(TFT_BLACK);
        }

        // 可选：如有其它资源需释放，可在此处添加
    }
}
