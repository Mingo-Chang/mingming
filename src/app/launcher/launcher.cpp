#include "launcher.h"
#include <core/lv_obj.h>
#include "bsp/porting/lv_port_disp.h"
#include "bsp/porting/lv_port_indev.h"
#include "ui/src/ui.h"
#include "app/app.h"

namespace MOONCAKE
{
    namespace APPS
    {
        void Launcher::updateAPPManager()
        {
            if (selected_app_index >= 0)
            {
                auto state = _mooncake->getAppCurrentState(selected_app_index);

                if (state == AppAbility::State_t::StateGoOpen)
                {
                    _mooncake->openApp(selected_app_index);
                    _mooncake->update();
                }
                else if (state == AppAbility::State_t::StateRunning)
                {
                    _mooncake->update();
                    // 检查按键退出
                    if (_device->button.B.pressed())
                    {
                        _mooncake->closeApp(selected_app_index);
                    }
                }
                else if (state == AppAbility::State_t::StateGoClose)
                {
                    _mooncake->update();
                    selected_app_index = -1;
                    // 可选：恢复 launcher UI
                    // ui_init();
                }
            }
        }

        void Launcher::updateDeviceStatus()
        {
            /* Device status manage */
            if (_device_status.updated)
            {
                _device_status.updated = false;
                /* Update brightness */
                //_device->Lcd.setBrightness(m_deviceStatus.brightness);
            }

            /* If hit auto screen off time  */
            // if (_device_status.autoScreenOff && (lv_disp_get_inactive_time(NULL) > _device_status.autoScreenOffTime))
            // {
            //     _device->Lcd.setBrightness(0);
            //     sleep_mode();
            //     _device->Button.B.begin();
            //     _device->Lcd.setBrightness(_device_status.brightness);

            //     /* Reset auto screen off time counting */
            //     lv_disp_trig_activity(NULL);
            // }

            if (_device_status.powerDetection)
            {
                /* code */
            }

            if (_device_status.sdCardInserted)
            {
                /* code */
            }

            if (_device_status.clockRTC)
            {
                /* code */
            }
        }

        void Launcher::onCreate()
        {
            //_device->init();
            // /* Init lvgl */
            // lv_init();
            // lv_port_disp_init(&_device->Lcd);
            // lv_port_indev_init(&_device->ctp);

            // /* Init ui */
            // ui_init();

            _mooncake = std::make_unique<mooncake::Mooncake>();
            MeowKit_app_install_callback(_mooncake.get(), _device);
        }
          
        void Launcher::onloop()
        {
            lv_timer_handler();  // 处理 LVGL
            delay(5);  // 延时，防止 CPU 占用过高
            updateDeviceStatus();
            updateAPPManager();
        }
         
        void Launcher::onDestroy()
        {

        }
    }
}


