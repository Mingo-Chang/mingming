#include "audio_es.h"
#include <PCA9557.h>

Audio::Audio()
    : _audio_info(44100, 2, 16),
      _sine_wave(32000),
      _sound_stream(_sine_wave)
{
    // 不再new TwoWire
    // _wire = new TwoWire(0);
}

Audio::~Audio()
{
    if (_audio_board) delete _audio_board;
    if (_i2s_out_stream) delete _i2s_out_stream;
    if (_copier) delete _copier;
    // 不再delete _wire
}

bool Audio::init()
{
    if (_inited) return true;

    AudioLogger::instance().begin(Serial0, AudioLogger::Warning);
    AudioDriverLogger.begin(Serial0, AudioDriverLogLevel::Warning);

    delay(2000);

    // 不再在此初始化I2C，只在devices或主程序初始化一次Wire

    // 配置I2C，直接传Wire对象
    _pins.addI2C(PinFunction::CODEC, HAL_PIN_I2C_SCL, HAL_PIN_I2C_SDA, ES8311ADDR, I2CSPEED , Wire);

    // 配置I2S（根据实际硬件修改）
    _pins.addI2S(PinFunction::CODEC, MCLKPIN, BCLKPIN, WSPIN, DOPIN, DIPIN);

    _pins.begin();

    // 初始化音频板（ES8311）
    _audio_board = new AudioBoard(AudioDriverES8311, _pins);
    _audio_board->begin();

    // 初始化I2S输出流
    _i2s_out_stream = new I2SCodecStream(*_audio_board);
    auto i2s_config = _i2s_out_stream->defaultConfig();
    i2s_config.copyFrom(_audio_info);
    _i2s_out_stream->begin(i2s_config);

    // 初始化正弦波发生器
    _sine_wave.begin(_audio_info, N_B4);

    // 拷贝器
    _copier = new StreamCopy(*_i2s_out_stream, _sound_stream);

    _inited = true;
    Serial0.println("[Audio] AudioKit init success!");
    return true;
}

void Audio::output()
{
    if (_inited && _copier) {
        _copier->copy();
    }
}