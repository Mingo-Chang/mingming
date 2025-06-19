#pragma once

#include <Arduino.h>

// QMI8658A I2C地址
#define QMI8658A_I2C_ADDR 0x6A

// QMI8658A寄存器地址
enum QMI8658A_Reg {
    QMI8658A_WHO_AM_I        = 0x00,
    QMI8658A_REVISION_ID     = 0x01,
    QMI8658A_CTRL1           = 0x02,
    QMI8658A_CTRL2           = 0x03,
    QMI8658A_CTRL3           = 0x04,
    QMI8658A_CTRL4           = 0x05,
    QMI8658A_CTRL5           = 0x06,
    QMI8658A_CTRL6           = 0x07,
    QMI8658A_CTRL7           = 0x08,
    QMI8658A_CTRL8           = 0x09,
    QMI8658A_CTRL9           = 0x0A,
    QMI8658A_CATL1_L         = 0x0B,
    QMI8658A_CATL1_H         = 0x0C,
    QMI8658A_CATL2_L         = 0x0D,
    QMI8658A_CATL2_H         = 0x0E,
    QMI8658A_CATL3_L         = 0x0F,
    QMI8658A_CATL3_H         = 0x10,
    QMI8658A_CATL4_L         = 0x11,
    QMI8658A_CATL4_H         = 0x12,
    QMI8658A_FIFO_WTM_TH     = 0x13,
    QMI8658A_FIFO_CTRL       = 0x14,
    QMI8658A_FIFO_SMPL_CNT   = 0x15,
    QMI8658A_FIFO_STATUS     = 0x16,
    QMI8658A_FIFO_DATA       = 0x17,
    QMI8658A_STATUSINT       = 0x2D,
    QMI8658A_STATUS0         = 0x2E,
    QMI8658A_STATUS1         = 0x2F,
    QMI8658A_TIMESTAMP_LOW   = 0x30,
    QMI8658A_TIMESTAMP_MID   = 0x31,
    QMI8658A_TIMESTAMP_HIGH  = 0x32,
    QMI8658A_TEMP_L          = 0x33,
    QMI8658A_TEMP_H          = 0x34,
    QMI8658A_AX_L            = 0x35,
    QMI8658A_AX_H            = 0x36,
    QMI8658A_AY_L            = 0x37,
    QMI8658A_AY_H            = 0x38,
    QMI8658A_AZ_L            = 0x39,
    QMI8658A_AZ_H            = 0x3A,
    QMI8658A_GX_L            = 0x3B,
    QMI8658A_GX_H            = 0x3C,
    QMI8658A_GY_L            = 0x3D,
    QMI8658A_GY_H            = 0x3E,
    QMI8658A_GZ_L            = 0x3F,
    QMI8658A_GZ_H            = 0x40,
    QMI8658A_COD_STATUS      = 0x46,
    QMI8658A_dQW_L           = 0x49,
    QMI8658A_dQW_H           = 0x4A,
    QMI8658A_dQX_L           = 0x4B,
    QMI8658A_dQX_H           = 0x4C,
    QMI8658A_dQY_L           = 0x4D,
    QMI8658A_dQY_H           = 0x4E,
    QMI8658A_dQZ_L           = 0x4F,
    QMI8658A_dQZ_H           = 0x50,
    QMI8658A_dVX_L           = 0x51,
    QMI8658A_dVX_H           = 0x52,
    QMI8658A_dVY_L           = 0x53,
    QMI8658A_dVY_H           = 0x54,
    QMI8658A_dVZ_L           = 0x55,
    QMI8658A_dVZ_H           = 0x56,
    QMI8658A_TAP_STATUS      = 0x59,
    QMI8658A_STEP_CNT_LOW    = 0x5A,
    QMI8658A_STEP_CNT_MIDL   = 0x5B,
    QMI8658A_STEP_CNT_HIGH   = 0x5C,
    QMI8658A_RESET           = 0x60
};

// 三轴数据结构体
typedef struct {
    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;
    int16_t gyr_x;
    int16_t gyr_y;
    int16_t gyr_z;
    float AngleX;
    float AngleY;
    float AngleZ;
} QMI8658A_Data;

class QMI8658A {
public:
    QMI8658A();
    bool begin(uint8_t addr = QMI8658A_I2C_ADDR);
    void reset();
    bool readRawData(QMI8658A_Data* data);
    void readAngle(QMI8658A_Data* data);
    // 可扩展更多接口...

private:
    uint8_t _addr;
    uint32_t _speed;
    // I2C 读写底层函数
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);
    void readMultiple(uint8_t reg, uint8_t* buf, uint8_t len);
};