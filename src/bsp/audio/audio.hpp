/**
 * @file audio.hpp
 * @brief ESP32-S3 AudioKit 驱动BSP模板
 * @author
 * @version 0.1
 * @date 2024-06-20
 */

#pragma once
#include <Arduino.h>
#include "AudioKitHAL.h"

// I2S
#define PIN_I2S_AUDIO_KIT_MCLK 38
#define PIN_I2S_AUDIO_KIT_BCK 14
#define PIN_I2S_AUDIO_KIT_WS 13
#define PIN_I2S_AUDIO_KIT_DATA_OUT 45
#define PIN_I2S_AUDIO_KIT_DATA_IN -1

// I2C
#define I2C_MASTER_SCL_IO 1     
#define I2C_MASTER_SDA_IO 2    


class Audio : public AudioKit {
private:
    bool _inited = false;
    AudioKitConfig _cfg;

public:
    Audio() = default;
    ~Audio() = default;

    /**
     * @brief 初始化 AudioKit，默认输出模式并设置正弦波发生器
     * @return true 初始化成功
     * @return false 初始化失败
     */
    inline bool init() {
        if (_inited) return true;
        LOGLEVEL_AUDIOKIT = AudioKitInfo;
        // 获取默认配置
        _cfg = defaultConfig(KitOutput);


        if (!begin(_cfg)) {
            Serial0.println("[Audio] AudioKit init failed!");
            return false;
        }
        Serial0.println("[Audio] AudioKit init success!");
        _inited = true;
        return true;
    }

    inline bool isInited() const { return _inited; }
};