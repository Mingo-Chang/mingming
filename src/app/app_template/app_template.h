/**
 * @file app_template.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <cstdio>
#include <mooncake.h>
#include <Arduino.h>

namespace mooncake::APPS
{
    /**
     * @brief Template
     *
     */
    class AppTemplate : public mooncake::AppAbility
    {
    public:
        AppTemplate()
        {
            printf("[AppTemplate] on construct\n");
            setAppInfo().name = "模板应用";
        }
        ~AppTemplate()
        {
            printf("[AppTemplate] on deconstruct\n");
        }
        void onCreate() override
        {
            printf("[AppTemplate] on create\n");
        }
        void onOpen() override
        {
            printf("[AppTemplate] on open\n");
        }
        void onRunning() override
        {
            printf("[AppTemplate] on running\n");

                uint32_t _last_tick = 0;
                if (millis() - _last_tick >= 1000) {
                    _last_tick = 0;
                    
                }

                // 检查按键B退出
                if (1) {
                    

                }
        }
        void onSleeping() override
        {
            printf("[AppTemplate] on sleeping\n");
        }
        void onClose() override
        {
            printf("[AppTemplate] on close\n");
        }
        void onDestroy() override
        {
            printf("[AppTemplate] on destroy\n");
        }
    };
} 