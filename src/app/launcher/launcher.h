/**
 * @file launcher.h
 * @author Mingo
 * @brief
 * @version 0.1
 * @date 2025-06-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <string>
#include <cstdint>
#include <mooncake.h>
using namespace mooncake;
#include "bsp/devices.h"
#include <memory>
#if __cplusplus <= 201103L
namespace std {template <typename T, typename... Args> std::unique_ptr<T> make_unique(Args&&... args) {return std::unique_ptr<T>(new T(std::forward<Args>(args)...));}}
#endif

extern int selected_app_index;

namespace MOONCAKE
{
    namespace APPS
    {

        /* Structure to hold device status */
        struct DeviceStatus_t
        {
            bool updated = false;
            bool autoScreenOff = false;
            bool sdCardInserted = false;
            bool powerDetection = false;
            bool clockRTC  = false;
            uint8_t brightness = 127;
            uint32_t autoScreenOffTime = 20000;
        };
        static DeviceStatus_t _device_status;

        class Launcher
        {
        private:
            struct Data_t
            {
                // Clock
                std::string clock;
                uint32_t clock_update_count = 0;
                const uint32_t clock_update_interval = 1000;
                char string_buffer[10];

                // Menu
                // const uint32_t menu_update_interval = 0;
                // App open and close anim
                
            };
            Data_t _data;
            // void _update_clock(bool updateNow = false);
            // void _create_menu();
            // void _update_menu();
            // void _destroy_menu();
            // void _play_app_anim(bool open); 
            
            std::unique_ptr<Mooncake> _mooncake = nullptr;
            DEVICES *_device = nullptr;

        public:
             inline Launcher(DEVICES* device) {  _device = device; }
             void onCreate();
             void onloop();
             void onDestroy();

        public:
            void updateDeviceStatus();
            void updateAPPManager();

        };
    }
} // namespace MOONCAKE::APPS