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
    float acc_x_g;
    float acc_y_g;
    float acc_z_g;
    float gyr_x_dps;
    float gyr_y_dps;
    float gyr_z_dps;
    float angle_x;   // X轴积分角度
    float angle_y;   // Y轴积分角度
    float angle_z;   // Z轴积分角度
    float pitch;     // 欧拉角 Pitch
    float roll;      // 欧拉角 Roll
    float yaw;       // 欧拉角 Yaw
    int mouse_dx;
    int mouse_dy;
} QMI8658A_Data;

class QMI8658A {
public:
    QMI8658A();
    bool begin(uint8_t addr = QMI8658A_I2C_ADDR);
    void reset();
    bool readRawData(QMI8658A_Data* data);
    void calibrateGyroBias(int samples = 200);
    void filterGyro(QMI8658A_Data* data); // 简单滤波
    void integrateGyro(QMI8658A_Data* data); // 角速度积分
    void updateMouseDelta(QMI8658A_Data* data, float sensitivity = 0.08f);
    bool autoSelfTestAndCalibrate(); // 自动自检+校准
    void complementaryFilter(QMI8658A_Data* data, float alpha = 0.98f);

private:
    uint8_t _addr;
    float gyro_bias_x = 0.0f;
    float gyro_bias_y = 0.0f;      // <--- 补充
    float gyro_bias_z = 0.0f;
    float last_gyr_x = 0.0f;
    float last_gyr_y = 0.0f;       // <--- 补充
    float last_gyr_z = 0.0f;
    float integratedAngleX = 0.0f;
    float integratedAngleY = 0.0f; // <--- 补充
    float integratedAngleZ = 0.0f;
    unsigned long lastUpdateTime = 0;

    float pitch = 0.0f;
    float roll  = 0.0f;
    float yaw   = 0.0f;
    // I2C 读写底层函数
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);
    void readMultiple(uint8_t reg, uint8_t* buf, uint8_t len);
};
/*
1. 采样频率与定时精度优化
问题：目前积分依赖 millis()，如果主循环阻塞或延时不稳定，积分精度会受影响。
优化：用定时器中断或高精度定时（如 micros()），保证采样周期恒定，积分更准确。
2. 三轴融合与姿态解算
问题：目前只用加速度和陀螺仪，Yaw（偏航角）会漂移。
优化：
加入磁力计支持（如有）：实现三轴互补滤波、Madgwick/Mahony等算法，获得完整三轴欧拉角/四元数，Yaw 长期不漂移。
输出四元数：避免欧拉角万向锁，适合3D应用。
3. 自适应滤波与动态灵敏度
问题：滤波参数和灵敏度是固定的，不能适应不同运动状态。
优化：
根据运动强度动态调整滤波系数和灵敏度（如静止时更平滑，快速运动时更灵敏）。
可实现自适应一阶滤波或卡尔曼滤波。
4. 温漂补偿与自动校准
问题：陀螺仪存在温漂，长时间积分会有误差。
优化：
利用 QMI8658A 的温度传感器，做温度补偿。
支持运行中自动零漂校准（如检测静止时自动校正零偏）。
5. FIFO与批量读取
问题：单次读取可能丢数据，特别是高频采样。
优化：
利用 QMI8658A 的 FIFO 功能，一次性批量读取多组数据，防止数据丢失，提高采样效率。6. 高级手势与动作识别
扩展：
基于 IMU 数据实现手势识别、动作检测（如晃动、旋转、点击等），可用于更多交互场景。
7. 功耗优化
优化：
根据实际需求动态调整 QMI8658A 的工作模式（如低功耗/高性能切换），延长电池寿命。8. 异常检测与自恢复
优化：
检测数据异常（如长时间无变化、突变），自动重置或重新初始化，提升系统鲁棒性。
9. API友好性与可扩展性
优化：
提供更丰富的API，如获取原始数据、单位转换、姿态回调等，方便上层应用调用和扩展。
10. 文档与注释完善
优化：
补充详细注释和使用说明，便于维护和二次开发。
典型进阶功能举例
Madgwick/Mahony四元数姿态解算（需磁力计）
FIFO批量采样接口
温度补偿接口
动作/手势识别API
运行时自校准与异常自恢复
如需某一方向的具体代码实现（如四元数解算、FIFO读取、温漂补偿等），请告知你的需求！
*/