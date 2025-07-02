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
    AppTemplate::AppTemplate()
    {
        setAppInfo().name = "AppTemplate";
    }

    void AppTemplate::onOpen()
    {
        tft.init();
        tft.fillScreen(TFT_BLACK);
        matrix_effect.init(&tft);
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
        // 可选：添加关闭时的清理代码
    }
}
