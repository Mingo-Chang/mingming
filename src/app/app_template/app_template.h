/**
 * @file app_template.h
 * @author Mingo
 * @brief App template for Mooncake
 * @version 0.1
 * @date 
 * @copyright Copyright (c) 2025
 */
#pragma once
#include "DigitalRainAnimation.hpp"
#include <mooncake.h>
#include "../../MeowKit.h"

using namespace mooncake;

namespace MOONCAKE::APPS
{
    /**
     * @brief AppTemplate 示例
     */
    class AppTemplate : public AppAbility {
    public:
        AppTemplate(DEVICES* device); // 新增构造参数
        void onOpen() override;
        void onRunning() override;
        void onClose() override;
    private:
        DEVICES* _device = nullptr; // 保存设备指针
        DigitalRainAnimation<Meow_LGFX> matrix_effect;
        // 不再需要 Meow_LGFX tft;，直接用 _device->Lcd
    };
}