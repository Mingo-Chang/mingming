#pragma once

#include <Arduino.h>
#include "AudioTools.h"
#include "AudioTools/AudioLibs/I2SCodecStream.h"

// 可根据config.h统一管理引脚
#include "../config.h"

#define ES8311ADDR        0x18

class Audio
{
public:
    Audio();
    ~Audio();

    /**
     * @brief 初始化音频硬件（I2C/I2S/Codec）
     * @return true 成功
     * @return false 失败
     */
    bool init();

    /**
     * @brief 输出一帧正弦波（测试用）
     */
    void output();

private:
    bool _inited = false;
    AudioInfo _audio_info;
    SineWaveGenerator<int16_t> _sine_wave;
    GeneratedSoundStream<int16_t> _sound_stream;
    DriverPins _pins;
    AudioBoard* _audio_board = nullptr;
    I2SCodecStream* _i2s_out_stream = nullptr;
    StreamCopy* _copier = nullptr;
    TwoWire* _wire = nullptr;
};