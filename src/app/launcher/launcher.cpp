#include "launcher.h"
#include <core/lv_obj.h>
#include "bsp/porting/lv_port_disp.h"
#include "bsp/porting/lv_port_indev.h"
#include "ui/src/ui.h"
#include "app/app.h"
#include <memory>
#include <iostream>

namespace MOONCAKE
{
    namespace APPS
    {
        void Launcher::updateAPPManager()
        {
            if (selected_app_index >= 0) 
            {
                _lvgl_inited = false;
                std::cout<<"App Index open:"<<selected_app_index<<std::endl;
                //_mooncake->closeApp(0);

                /* Delete Launcher screen and reaplace with an empty one */
                // lv_disp_load_scr(lv_obj_create(NULL));
                // lv_obj_del(ui_Apps_Menu); 

                _mooncake->openApp(selected_app_index);
                _mooncake->update();
                std::cout<<"open press:"<<selected_app_index<<std::endl;
                
                // if (_mooncake->getAppCurrentState(selected_app_index) == AppAbility::State_t::StateGoOpen)
                // {
                //     _mooncake->openApp(selected_app_index);
                //     _mooncake->update();
                // }
                //运行app
                if (_mooncake->getAppCurrentState(selected_app_index) == AppAbility::State_t::StateRunning)
                {
                    //esp_task_wdt_reset(); // 喂狗
                    while(1)
                    {
                        //unsigned long lastTime = 0;
                        _mooncake->update();
                        // if (millis() - lastTime > 1000) {
                        //     doPeriodicTask();
                        //     lastTime = millis();
                        // }
                        // esp_task_wdt_reset();
                        vTaskDelay(5); // 释放CPU控制权
                        if (_device->button.B.pressed())
                        {
                            //关闭app
                            //_mooncake->appAbilityManager()->closeAppAbility(selected_app_index);
                            //_mooncake->appAbilityManager()->destroyAbility(selected_app_index);
                            std::cout<<"bb press:"<<selected_app_index<<std::endl;

                            _mooncake->closeApp(selected_app_index);
                            _mooncake->update();
                            //selected_app_index = -1;
                            // _mooncake->update();
                            selected_app_index = -1;
                            onRestart();
                            //_ui_screen_change(&ui_Apps_Menu, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Apps_Menu_screen_init);
                            //_lvglWrapp->enable();
                            _lvgl_inited = true;
                            break;
                        }
                    }
                 
                }

                //关闭app
                if (_mooncake->getAppCurrentState(selected_app_index) == AppAbility::State_t::StateGoClose) 
                {
                    //_mooncake->closeApp(selected_app_index);
                    _mooncake->update();
                    std::cout<<"close:"<<selected_app_index<<std::endl;
                }
           

                //  while(1)
                //  {
                //     onloop();  // 处理 LVGL
                //     if (_device->button.B.pressed())
                //     {
                //         break;
                //     }
                //  }
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
            lv_deinit();
            lv_init();
            lv_port_disp_init(&_device->Lcd);
            lv_port_indev_init(&_device->ctp);

            /* Init ui */
            ui_init();

            _mooncake = std::make_unique<mooncake::Mooncake>();
            MeowKit_app_install_callback(_mooncake.get(),_device);

            _lvgl_inited = true;
        }

        void Launcher::onRestart()
        {
            //lvgl.disable();
            std::cout<<"3333333333333:"<<selected_app_index<<std::endl;
            lv_deinit();
            delay(100); // 等待 LVGL 资源释放
            lv_init();
            lv_port_disp_init(&_device->Lcd);
            lv_port_indev_init(&_device->ctp);

            /* Init ui */
            ui_init();

            std::cout<<"444444444444:"<<selected_app_index<<std::endl;
           // lvgl.enable();
        }
          
        void Launcher::onloop()
        {
            updateDeviceStatus();
            updateAPPManager();
            if (_lvgl_inited)
            {
                //std::cout<<"123123:"<<selected_app_index<<std::endl;
                lv_timer_handler();  // 处理 LVGL
                delay(5);  // 延时，防止 CPU 占用过高
                //std::cout<<"444443322211:"<<selected_app_index<<std::endl;
            }

        }
         
        void Launcher::onDestroy()
        {

        }
    }
}


