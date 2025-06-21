#include "QMI8658A.h"
#include <math.h>
#include <Wire.h>

QMI8658A::QMI8658A() : _addr(QMI8658A_I2C_ADDR) {}

bool QMI8658A::begin(uint8_t addr) {
    _addr = addr;

    // 读取WHO_AM_I
    uint8_t id = readRegister(QMI8658A_WHO_AM_I);
    uint8_t tryCount = 10;
    while (id != 0x05 && tryCount--) {
        delay(100);
        id = readRegister(QMI8658A_WHO_AM_I);
    }
    if (id != 0x05) {
        Serial.println("[QMI8658A] WHO_AM_I check failed!");
        return false;
    }
    Serial.println("[QMI8658A] WHO_AM_I check passed!");

    // 初始化寄存器
    writeRegister(QMI8658A_RESET, 0xB0);  // 复位
    delay(10);
    writeRegister(QMI8658A_CTRL1, 0x40);  // 地址自动增加
    writeRegister(QMI8658A_CTRL7, 0x03);  // 使能加速度和陀螺仪
    writeRegister(QMI8658A_CTRL2, 0x95);  // ACC 4g 250Hz
    writeRegister(QMI8658A_CTRL3, 0xD5);  // GYRO 512dps 250Hz
    delay(10);

    return true;
}

void QMI8658A::reset() {
    writeRegister(QMI8658A_RESET, 0xB0);
    delay(10);
}

bool QMI8658A::readRawData(QMI8658A_Data* data) {
    // 检查数据是否准备好
    uint8_t status = readRegister(QMI8658A_STATUS0);
    if ((status & 0x03) == 0) {
        return false;
    }

    uint8_t buf[12] = {0};
    readMultiple(QMI8658A_AX_L, buf, 12);

    data->acc_x = (int16_t)((buf[1] << 8) | buf[0]);
    data->acc_y = (int16_t)((buf[3] << 8) | buf[2]);
    data->acc_z = (int16_t)((buf[5] << 8) | buf[4]);
    data->gyr_x = (int16_t)((buf[7] << 8) | buf[6]);
    data->gyr_y = (int16_t)((buf[9] << 8) | buf[8]);
    data->gyr_z = (int16_t)((buf[11] << 8) | buf[10]);
    return true;
}

void QMI8658A::readAngle(QMI8658A_Data* data) {
    if (!readRawData(data)) return ;

    // 计算倾角，单位为度
    float ax = (float)data->acc_x;
    float ay = (float)data->acc_y;
    float az = (float)data->acc_z;

    float temp;
    temp = ax / sqrt(ay * ay + az * az);
    data->AngleX = atan(temp) * 57.29578f;
    temp = ay / sqrt(ax * ax + az * az);
    data->AngleY = atan(temp) * 57.29578f;
    temp = sqrt(ax * ax + ay * ay) / az;
    data->AngleZ = atan(temp) * 57.29578f;
}

// --- I2C底层操作 ---
uint8_t QMI8658A::readRegister(uint8_t reg) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_addr, (uint8_t)1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0;
}

void QMI8658A::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void QMI8658A::readMultiple(uint8_t reg, uint8_t* buf, uint8_t len) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_addr, len);
    for (uint8_t i = 0; i < len && Wire.available(); ++i) {
        buf[i] = Wire.read();
    }
}