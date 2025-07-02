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
        AppTemplate();
        void onOpen() override;
        void onRunning() override;
        void onClose() override;
    private:
        DigitalRainAnimation<Meow_LGFX> matrix_effect;
        Meow_LGFX tft;
    };
}