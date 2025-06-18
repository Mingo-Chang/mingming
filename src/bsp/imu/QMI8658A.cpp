#include "QMI8658A.h"
#include <Wire.h>

QMI8658A::QMI8658A()
    : acc_odr(QMI8658A_ACC_ODR_1000),
      gyro_odr(QMI8658A_GYRO_ODR_1000),
      acc_scale(QMI8658A_ACC_SCALE_2G),
      gyro_scale(QMI8658A_GYRO_SCALE_256DPS),
      acc_lpf(QMI8658A_LPF_13_37),
      gyro_lpf(QMI8658A_LPF_13_37),
      sensor_state(QMI8658A_STATE_DEFAULT),
      device_addr(0x6A), // 默认I2C地址
      reading_timestamp_us(0)
{
    memset(readings, 0, sizeof(readings));
}

QMI8658A::~QMI8658A() {}

bool QMI8658A::begin(uint8_t addr, uint32_t speed) {
    device_addr = addr;
    Wire.setClock(speed);

    // 检查芯片ID
    uint8_t id = readRegister(QMI8658A_WHO_AM_I);
    if (id != 0x05) {
        Serial0.println("[QMI8658A] WHO_AM_I check failed!");
        return false;
    }
    Serial0.println("[QMI8658A] WHO_AM_I check passed!");

    // 复位芯片
    writeRegister(QMI8658A_RESET, 0xB0); // 软件复位
    delay(10);

    // 配置寄存器
    writeRegister(QMI8658A_CTRL1, 0x40); // 地址自动增加
    writeRegister(QMI8658A_CTRL7, 0x03); // 使能加速度和陀螺仪
    writeRegister(QMI8658A_CTRL2, 0x95); // 加速度：4g，250Hz
    writeRegister(QMI8658A_CTRL3, 0xD5); // 陀螺仪：512dps，250Hz

    delay(10);
    return true;
}

void QMI8658A::reset() {
    writeRegister(QMI8658A_CTRL1, 0x80); // 软件复位
    delay(10);
}

bool QMI8658A::checkWhoAmI() {
    uint8_t id = readRegister(QMI8658A_WHO_AM_I);
    // 数据手册规定的WHO_AM_I值，假设为0x05
    return (id == 0x05);
}

void QMI8658A::setAccODR(QMI8658A_acc_odr_t odr) {
    acc_odr = odr;
    uint8_t reg = readRegister(QMI8658A_CTRL1);
    reg = (reg & ~QMI8658A_AODR_MASK) | (odr & QMI8658A_AODR_MASK);
    writeRegister(QMI8658A_CTRL1, reg);
}

void QMI8658A::setGyroODR(QMI8658A_gyro_odr_t odr) {
    gyro_odr = odr;
    uint8_t reg = readRegister(QMI8658A_CTRL2);
    reg = (reg & ~QMI8658A_GODR_MASK) | (odr & QMI8658A_GODR_MASK);
    writeRegister(QMI8658A_CTRL2, reg);
}

void QMI8658A::setAccScale(QMI8658A_acc_scale_t scale) {
    acc_scale = scale;
    uint8_t reg = readRegister(QMI8658A_CTRL1);
    reg = (reg & ~QMI8658A_ASCALE_MASK) | ((scale << QMI8658A_ASCALE_OFFSET) & QMI8658A_ASCALE_MASK);
    writeRegister(QMI8658A_CTRL1, reg);
}

void QMI8658A::setGyroScale(QMI8658A_gyro_scale_t scale) {
    gyro_scale = scale;
    uint8_t reg = readRegister(QMI8658A_CTRL2);
    reg = (reg & ~QMI8658A_GSCALE_MASK) | ((scale << QMI8658A_GSCALE_OFFSET) & QMI8658A_GSCALE_MASK);
    writeRegister(QMI8658A_CTRL2, reg);
}

void QMI8658A::setAccLPF(QMI8658A_lpf_t lpf) {
    acc_lpf = lpf;
    uint8_t reg = readRegister(QMI8658A_CTRL5);
    reg = (reg & ~QMI8658A_ALPF_MASK) | ((lpf << QMI8658A_ALPF_OFFSET) & QMI8658A_ALPF_MASK);
    writeRegister(QMI8658A_CTRL5, reg);
}

void QMI8658A::setGyroLPF(QMI8658A_lpf_t lpf) {
    gyro_lpf = lpf;
    uint8_t reg = readRegister(QMI8658A_CTRL6);
    reg = (reg & ~QMI8658A_GLPF_MASK) | ((lpf << QMI8658A_GLPF_OFFSET) & QMI8658A_GLPF_MASK);
    writeRegister(QMI8658A_CTRL6, reg);
}

void QMI8658A::setState(QMI8658A_state_t state) {
    sensor_state = state;
    // 可根据实际需求实现状态切换
}

void QMI8658A::writeRegister(uint8_t addr, uint8_t data) {
    Wire.beginTransmission(device_addr);
    Wire.write(addr);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t QMI8658A::readRegister(uint8_t addr) {
    Wire.beginTransmission(device_addr);
    Wire.write(addr);
    Wire.endTransmission(false);
    Wire.requestFrom(device_addr, (uint8_t)1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0;
}

void QMI8658A::writeCTRL9(uint8_t command) {
    writeRegister(QMI8658A_CTRL9, command);
}

void QMI8658A::updateSensor() {
    Wire.beginTransmission(device_addr);
    Wire.write(QMI8658A_AX_L);
    Wire.endTransmission(false);
    Wire.requestFrom(device_addr, (uint8_t)12);

    for (int i = 0; i < 6; ++i) {
        uint8_t l = Wire.read();
        uint8_t h = Wire.read();
        readings[i] = (int16_t)((h << 8) | l);

        // 调试输出
        Serial0.print("Reg["); Serial0.print(i); Serial0.print("]: ");
        Serial0.print("L=0x"); Serial0.print(l, HEX);
        Serial0.print(" H=0x"); Serial0.print(h, HEX);
        Serial0.print(" Val="); Serial0.println(readings[i]);
    }
    reading_timestamp_us = micros();
}

void QMI8658A::updateIfNeeded() {
    // 可根据刷新周期自动更新
    if ((micros() - reading_timestamp_us) > QMI8658A_REFRESH_DELAY) {
        updateSensor();
    }
}

void QMI8658A::getRawReadings(int16_t* buf) {
    updateIfNeeded();
    memcpy(buf, readings, sizeof(readings));
}

float QMI8658A::getAccX() {
    updateIfNeeded();
    float scale = 2.0f; // 默认2g
    switch (acc_scale) {
        case QMI8658A_ACC_SCALE_2G: scale = 2.0f; break;
        case QMI8658A_ACC_SCALE_4G: scale = 4.0f; break;
        case QMI8658A_ACC_SCALE_8G: scale = 8.0f; break;
        case QMI8658A_ACC_SCALE_16G: scale = 16.0f; break;
    }
    return readings[0] * (scale * 9.80665f * QMI8658A_SIXTEENBIT_SCALER);
}

float QMI8658A::getAccY() {
    updateIfNeeded();
    float scale = 2.0f;
    switch (acc_scale) {
        case QMI8658A_ACC_SCALE_2G: scale = 2.0f; break;
        case QMI8658A_ACC_SCALE_4G: scale = 4.0f; break;
        case QMI8658A_ACC_SCALE_8G: scale = 8.0f; break;
        case QMI8658A_ACC_SCALE_16G: scale = 16.0f; break;
    }
    return readings[1] * (scale * 9.80665f * QMI8658A_SIXTEENBIT_SCALER);
}

float QMI8658A::getAccZ() {
    updateIfNeeded();
    float scale = 2.0f;
    switch (acc_scale) {
        case QMI8658A_ACC_SCALE_2G: scale = 2.0f; break;
        case QMI8658A_ACC_SCALE_4G: scale = 4.0f; break;
        case QMI8658A_ACC_SCALE_8G: scale = 8.0f; break;
        case QMI8658A_ACC_SCALE_16G: scale = 16.0f; break;
    }
    return readings[2] * (scale * 9.80665f * QMI8658A_SIXTEENBIT_SCALER);
}

float QMI8658A::getGyroX() {
    updateIfNeeded();
    float scale = 256.0f; // 默认256dps
    switch (gyro_scale) {
        case QMI8658A_GYRO_SCALE_16DPS: scale = 16.0f; break;
        case QMI8658A_GYRO_SCALE_32DPS: scale = 32.0f; break;
        case QMI8658A_GYRO_SCALE_64DPS: scale = 64.0f; break;
        case QMI8658A_GYRO_SCALE_128DPS: scale = 128.0f; break;
        case QMI8658A_GYRO_SCALE_256DPS: scale = 256.0f; break;
        case QMI8658A_GYRO_SCALE_512DPS: scale = 512.0f; break;
        case QMI8658A_GYRO_SCALE_1024DPS: scale = 1024.0f; break;
        case QMI8658A_GYRO_SCALE_2048DPS: scale = 2048.0f; break;
    }
    return readings[3] * (scale * QMI8658A_SIXTEENBIT_SCALER);
}

float QMI8658A::getGyroY() {
    updateIfNeeded();
    float scale = 256.0f;
    switch (gyro_scale) {
        case QMI8658A_GYRO_SCALE_16DPS: scale = 16.0f; break;
        case QMI8658A_GYRO_SCALE_32DPS: scale = 32.0f; break;
        case QMI8658A_GYRO_SCALE_64DPS: scale = 64.0f; break;
        case QMI8658A_GYRO_SCALE_128DPS: scale = 128.0f; break;
        case QMI8658A_GYRO_SCALE_256DPS: scale = 256.0f; break;
        case QMI8658A_GYRO_SCALE_512DPS: scale = 512.0f; break;
        case QMI8658A_GYRO_SCALE_1024DPS: scale = 1024.0f; break;
        case QMI8658A_GYRO_SCALE_2048DPS: scale = 2048.0f; break;
    }
    return readings[4] * (scale * QMI8658A_SIXTEENBIT_SCALER);
}

float QMI8658A::getGyroZ() {
    updateIfNeeded();
    float scale = 256.0f;
    switch (gyro_scale) {
        case QMI8658A_GYRO_SCALE_16DPS: scale = 16.0f; break;
        case QMI8658A_GYRO_SCALE_32DPS: scale = 32.0f; break;
        case QMI8658A_GYRO_SCALE_64DPS: scale = 64.0f; break;
        case QMI8658A_GYRO_SCALE_128DPS: scale = 128.0f; break;
        case QMI8658A_GYRO_SCALE_256DPS: scale = 256.0f; break;
        case QMI8658A_GYRO_SCALE_512DPS: scale = 512.0f; break;
        case QMI8658A_GYRO_SCALE_1024DPS: scale = 1024.0f; break;
        case QMI8658A_GYRO_SCALE_2048DPS: scale = 2048.0f; break;
    }
    return readings[5] * (scale * QMI8658A_SIXTEENBIT_SCALER);
}

float QMI8658A::getTemperature() {
    // 读取温度寄存器
    uint8_t temp_l = readRegister(QMI8658A_TEMP_L);
    uint8_t temp_h = readRegister(QMI8658A_TEMP_H);
    int16_t raw = (int16_t)((temp_h << 8) | temp_l);
    // 数据手册温度转换公式，假设为：Temp(°C) = raw / 256 + 25
    return raw / 256.0f + 25.0f;
}