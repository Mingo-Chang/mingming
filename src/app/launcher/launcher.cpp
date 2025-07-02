#include "launcher.h"
#include <core/lv_obj.h>
#include "bsp/porting/lv_port_disp.h"
#include "bsp/porting/lv_port_indev.h"
#include "ui/src/ui.h"
#include "../app.h"

namespace MOONCAKE
{
    namespace APPS
    {
        void Launcher::updateAPPManager()
        {
            if (selected_app_index >= 0) 
            {
                //std::cout<<"App Index open:"<<selected_app_index<<std::endl;
                //_mooncake->closeApp(0);
                // 打开app
                _mooncake->openApp(selected_app_index);
                _mooncake->update();
                
                //运行app
                if (_mooncake->getAppCurrentState(selected_app_index) == AppAbility::State_t::StateRunning)
                {
                    while (1)
                    {
                        
                        _mooncake->update();
                        if (_device->button.B.pressed())
                        {
                            _mooncake->closeApp(selected_app_index); // 正确关闭
                            break;
                        }
                    }
                }

                //关闭app
                if (_mooncake->getAppCurrentState(selected_app_index) == AppAbility::State_t::StateGoClose) 
                {
                    //_mooncake->closeApp(selected_app_index);
                    _mooncake->update();
                    
                }
                selected_app_index = -1;
                //_lvglWrapp->enable();
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
            
            /* Init lvgl */
            lv_init();
            lv_port_disp_init(&_device->Lcd);
            lv_port_indev_init(&_device->ctp);

            /* Init ui */
            ui_init();

            _mooncake = std::make_unique<mooncake::Mooncake>();
            MeowKit_app_install_callback(_mooncake.get());
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


