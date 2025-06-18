#ifndef QMI8658A_H
#define QMI8658A_H

#include <Arduino.h>

// ------------------- Register Map -------------------
#define QMI8658A_RESET           0x60
#define QMI8658A_WHO_AM_I        0x00
#define QMI8658A_REVISION_ID     0x01
#define QMI8658A_CTRL1           0x02
#define QMI8658A_CTRL2           0x03
#define QMI8658A_CTRL3           0x04
#define QMI8658A_CTRL4           0x05
#define QMI8658A_CTRL5           0x06
#define QMI8658A_CTRL6           0x07
#define QMI8658A_CTRL7           0x08
#define QMI8658A_CTRL8           0x09
#define QMI8658A_CTRL9           0x0A

#define QMI8658A_CAL1_L          0x0B
#define QMI8658A_CAL1_H          0x0C
#define QMI8658A_CAL2_L          0x0D
#define QMI8658A_CAL2_H          0x0E
#define QMI8658A_CAL3_L          0x0F
#define QMI8658A_CAL3_H          0x10
#define QMI8658A_CAL4_L          0x11
#define QMI8658A_CAL4_H          0x12

#define QMI8658A_STATUSINT       0x2D

// Data output registers (accel: 0x35~0x3A, gyro: 0x3B~0x40)
#define QMI8658A_AX_L            0x35
#define QMI8658A_AX_H            0x36
#define QMI8658A_AY_L            0x37
#define QMI8658A_AY_H            0x38
#define QMI8658A_AZ_L            0x39
#define QMI8658A_AZ_H            0x3A
#define QMI8658A_GX_L            0x3B
#define QMI8658A_GX_H            0x3C
#define QMI8658A_GY_L            0x3D
#define QMI8658A_GY_H            0x3E
#define QMI8658A_GZ_L            0x3F
#define QMI8658A_GZ_H            0x40

#define QMI8658A_TEMP_L          0x33
#define QMI8658A_TEMP_H          0x34

// ------------------- Bit Masks -------------------
#define QMI8658A_AODR_MASK       0x0F
#define QMI8658A_GODR_MASK       0x0F
#define QMI8658A_ASCALE_MASK     0x70
#define QMI8658A_GSCALE_MASK     0x70
#define QMI8658A_ALPF_MASK       0x06
#define QMI8658A_GLPF_MASK       0x60

#define QMI8658A_ASCALE_OFFSET   4
#define QMI8658A_GSCALE_OFFSET   4
#define QMI8658A_ALPF_OFFSET     1
#define QMI8658A_GLPF_OFFSET     5

#define QMI8658A_COMM_TIMEOUT    50
#define QMI8658A_SIXTEENBIT_SCALER (1.0f / 32768.0f)
#define QMI8658A_REFRESH_DELAY   2000
#define QMI8658A_CTRL_CMD_AHB_CLOCK_GATING 0x12

// ------------------- Types -------------------
typedef enum {
    QMI8658A_ACC_ODR_8000 = 0x0,
    QMI8658A_ACC_ODR_4000,
    QMI8658A_ACC_ODR_2000,
    QMI8658A_ACC_ODR_1000,
    QMI8658A_ACC_ODR_500,
    QMI8658A_ACC_ODR_250,
    QMI8658A_ACC_ODR_120,
    QMI8658A_ACC_ODR_60,
    QMI8658A_ACC_ODR_30,
    QMI8658A_ACC_ODR_LP_128 = 0xC,
    QMI8658A_ACC_ODR_LP_21,
    QMI8658A_ACC_ODR_LP_11,
    QMI8658A_ACC_ODR_LP_3,
} QMI8658A_acc_odr_t;

typedef enum {
    QMI8658A_GYRO_ODR_8000 = 0x0,
    QMI8658A_GYRO_ODR_4000,
    QMI8658A_GYRO_ODR_2000,
    QMI8658A_GYRO_ODR_1000,
    QMI8658A_GYRO_ODR_500,
    QMI8658A_GYRO_ODR_250,
    QMI8658A_GYRO_ODR_120,
    QMI8658A_GYRO_ODR_60,
    QMI8658A_GYRO_ODR_30
} QMI8658A_gyro_odr_t;

typedef enum {
    QMI8658A_ACC_SCALE_2G = 0x0,
    QMI8658A_ACC_SCALE_4G,
    QMI8658A_ACC_SCALE_8G,
    QMI8658A_ACC_SCALE_16G
} QMI8658A_acc_scale_t;

typedef enum {
    QMI8658A_GYRO_SCALE_16DPS = 0x0,
    QMI8658A_GYRO_SCALE_32DPS,
    QMI8658A_GYRO_SCALE_64DPS,
    QMI8658A_GYRO_SCALE_128DPS,
    QMI8658A_GYRO_SCALE_256DPS,
    QMI8658A_GYRO_SCALE_512DPS,
    QMI8658A_GYRO_SCALE_1024DPS,
    QMI8658A_GYRO_SCALE_2048DPS
} QMI8658A_gyro_scale_t;

typedef enum {
    QMI8658A_LPF_2_66 = 0x0,
    QMI8658A_LPF_3_63 = 0x2,
    QMI8658A_LPF_5_39 = 0x4,
    QMI8658A_LPF_13_37 = 0x6
} QMI8658A_lpf_t;

typedef enum {
    QMI8658A_STATE_DEFAULT,
    QMI8658A_STATE_POWER_DOWN,
    QMI8658A_STATE_RUNNING,
    QMI8658A_STATE_LOCKING
} QMI8658A_state_t;

// ------------------- Class -------------------
class QMI8658A {
private:
    QMI8658A_acc_odr_t acc_odr;
    QMI8658A_gyro_odr_t gyro_odr;
    QMI8658A_acc_scale_t acc_scale;
    QMI8658A_gyro_scale_t gyro_scale;
    QMI8658A_lpf_t acc_lpf;
    QMI8658A_lpf_t gyro_lpf;
    QMI8658A_state_t sensor_state;
    uint8_t device_addr;
    int16_t readings[6];
    uint32_t reading_timestamp_us;

    void writeRegister(uint8_t addr, uint8_t data);
    uint8_t readRegister(uint8_t addr);
    void writeCTRL9(uint8_t command);
    void updateSensor();
    void updateIfNeeded();

public:
    explicit QMI8658A();
    bool begin(uint8_t addr, uint32_t speed = 400000);
    void reset();
    bool checkWhoAmI();
    void setAccODR(QMI8658A_acc_odr_t odr);
    void setGyroODR(QMI8658A_gyro_odr_t odr);
    void setAccScale(QMI8658A_acc_scale_t scale);
    void setGyroScale(QMI8658A_gyro_scale_t scale);
    void setAccLPF(QMI8658A_lpf_t lpf);
    void setGyroLPF(QMI8658A_lpf_t lpf);
    void setState(QMI8658A_state_t state);

    void getRawReadings(int16_t* buf);
    float getAccX();
    float getAccY();
    float getAccZ();
    float getGyroX();
    float getGyroY();
    float getGyroZ();
    float getTemperature();

    ~QMI8658A();
};

#endif