/**
 * @file hal_rachel.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "../hal.h"

class HAL_MeowKit : public HAL
{
private:
    std::array<uint8_t, 11> _gamepad_key_map;
    std::array<bool, 11> _key_state_list;


private:
    void _power_init();
    void _disp_init();
    void _disp_logo();
    void _fs_init();
    void _i2c_init();
    void _rtc_init();
    void _imu_init();
    void _spk_init();
    void _sdcard_init();
    void _gamepad_init();
    void _adjust_sys_time();
    void _system_config_init();
    void _sum_up();

public:
    //HAL_Rachel() : _i2c_bus(nullptr), _rtc(nullptr), _imu(nullptr)
    // _spk(nullptr)
    // {
    // }
    // ~HAL_Rachel()
    // {
    //     // delete _rtc;
    //     // delete _imu;
    //     // delete _i2c_bus;
    //     // delete _spk;
    // }

    inline std::string type() override { return "Rachel"; }

    inline void init() override
    {
        _power_init();
        _disp_init();
        _gamepad_init();
        _spk_init();
        _i2c_init();
        _rtc_init();
        _imu_init();
        _fs_init();
        _sdcard_init();
        _system_config_init();
        _sum_up();
    }

    void reboot() override;
    void loadTextFont24() override;
    void loadTextFont16() override;
    void loadLauncherFont24() override;

    //bool getButton(GAMEPAD::GamePadButton_t button) override;
    void powerOff() override;
    void setSystemTime(tm dateTime) override;
    void updateImuData() override;
    void beep(float frequency, uint32_t duration) override;
    void beepStop() override;
    void setBeepVolume(uint8_t volume) override;
    void loadSystemConfig() override;
    void saveSystemConfig() override;
};