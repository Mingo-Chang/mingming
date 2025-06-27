/**
 * @file 
 * @author 
 * @brief 
 * @version 
 * @date 
 * 
 * @copyright 
 * 
 */
#include "devices.h"

// IRsend irsend(HAL_PIN_IR_TX);
// IRrecv irrecv(HAL_PIN_IR_RX);
// decode_results results;
// uint16_t rawData[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
//                         600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
//                         600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
//                         650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
//                         650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
//                         650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
//                         650, 1650, 650, 1650, 650, 1650, 600};
// // Example Samsung A/C state captured from IRrecvDumpV2.ino
// uint8_t samsungState[kSamsungAcStateLength] = {
//     0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
//     0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};

void DEVICES::init()
{
    Serial0.begin(115200);
    Serial0.println("BSP init...");

    /* Init POWER */
    button.PWR_ON.begin();
    button.PWR_ON.read();
    if (button.PWR_ON.held(3000)) {
        digitalWrite(HAL_PIN_PWR_HOLD, HIGH);
        delay(1000);
    }

    /* Init I2C */
    Wire.begin(HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL);
    Wire.setClock(I2CSPEED);

    /* Init PCA9557 */
    #define LCD_CS_PIN (0)
    io.pinMode(LCD_CS_PIN, OUTPUT);
    io.digitalWrite(LCD_CS_PIN, LOW); //lcd使能 
    #define PA_EN (1)
    io.pinMode(PA_EN, OUTPUT);
    io.digitalWrite(PA_EN, HIGH); //扬声器使能

    /* I2C设备检测 */
    struct {
        const char* name;
        uint8_t addr;
        uint8_t* result;
    } i2c_devs[] = {
        {"PCA9557", 0x19, nullptr},
        {"RTC", PCF8563_ADDR, nullptr},
        {"IMU", QMI8658A_I2C_ADDR, nullptr},
        {"CTP", CTP_DEV_ADDR, nullptr},
        {"SPEAKER", ES8311ADDR, nullptr},
        {"MIC", 0x41, nullptr}
    };
    uint8_t i2c_results[sizeof(i2c_devs)/sizeof(i2c_devs[0])];
    for (size_t i = 0; i < sizeof(i2c_devs)/sizeof(i2c_devs[0]); ++i) {
        Wire.beginTransmission(i2c_devs[i].addr);
        i2c_results[i] = Wire.endTransmission();
        i2c_devs[i].result = &i2c_results[i];
    }

    /* Init lcd bootloader */
    Lcd.init();
    Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    Lcd.setFont(&fonts::efontCN_16);
    Lcd.setCursor(0, 0);
    Lcd.printf(" \n BSP %s :)\n Author: Mingo@whitecliff\n", BSP_VERISON);
    Lcd.printf(" Project: %s\n", PROJECT_NAME);

    // 显示I2C检测结果
    for (size_t i = 0; i < sizeof(i2c_devs)/sizeof(i2c_devs[0]); ++i) {
        Lcd.printf(" %s: %s\n", i2c_devs[i].name, (*i2c_devs[i].result == 0) ? "OK" : "FAIL");
    }

    /* Init button A and B */
    button.A.begin();
    button.B.begin();

    // 检测A键
    Lcd.printf(" 请按下A键...");
    while (1) {
        button.A.read();
        if (button.A.pressed()) {
            Lcd.printf(" A键 OK\n");
            break;
        }
        delay(10);
    }

    // 检测B键
    Lcd.printf(" 请按下B键...");
    while (1) {
        button.B.read();
        if (button.B.pressed()) {
            Lcd.printf(" B键 OK\n");
            break;
        }
        delay(10);
    }

    Lcd.printf(" BSP init done!\n");
    delay(2000); // 等待显示稳定
    
    /* Init SD_MMC*/
    //sd.init();
    // // 写文件
    // File file = SD_MMC.open("/test.txt", FILE_WRITE);
    // if (file) {
    //     file.println("Hello, ESP32-S3 SDMMC 1bit!");
    //     file.close();
    //     Serial0.println("File written successfully!");
    // } else {
    //     Serial0.println("Failed to write file!");
    // }

    // // 读文件
    // file = SD_MMC.open("/test.txt", FILE_READ);
    // if (file) {
    //     Serial0.println("Reading file content:");
    //     while (file.available()) {
    //         Serial0.write(file.read());
    //     }
    //     file.close();
    //     Serial0.println("\nFile read successfully!");
    // } else {
    //     Serial0.println("Failed to read file!");
    // }

    // // 删除文件
    // if (SD_MMC.remove("/test.txt")) {
    //     Serial0.println("File deleted successfully!");
    // } else {
    //     Serial0.println("Failed to delete file!");
    // }

    /*Init IMU*/
    //imu.begin(0x6A);
    /*欧拉角、立方体姿态测试*/
    // imu.calibrateGyroBias(200);

    // while(1){
    // QMI8658A_Data imu_data;
    //     if (imu.readRawData(&imu_data)) {
    //         imu.filterGyro(&imu_data);                // 低通滤波
    //         imu.complementaryFilter(&imu_data, 0.98f);// 互补滤波融合
    //         Serial0.printf("angle: %.2f, %.2f, %.2f\n",
    //             imu_data.pitch, imu_data.roll, imu_data.yaw);
    //         delay(20); // 50Hz
    //     }
    // }

    /*air mouse*/
    // imu.calibrateGyroBias(200);
    // bleMouse.begin();
    // while(1){
    // // 等待蓝牙连接
    // if (!bleMouse.isConnected()) {
    //     delay(100);
    //     continue;
    // }
    // QMI8658A_Data imu_data;
    // if (imu.readRawData(&imu_data)) {
    //     imu.updateMouseDelta(&imu_data, 5.0f); // sensitivity 可调
    //     bleMouse.move(imu_data.mouse_dx, imu_data.mouse_dy, 0); // X, Y, 滚轮
    //     Serial0.printf("Mouse X: %d, Y: %d\n", imu_data.mouse_dx, imu_data.mouse_dy);
    // }
    // delay(20); // 50Hz
    // }
    // 记录实时数据显示的起始Y坐标
    // int info_y = Lcd.getCursorY();
    // pcf.begin();
    // RTC_Time t = {0, 24, 4, 26, 5, 6, 2025}; // 2025-1-1 12:00:00
    // pcf.setTime(t);
    
    // irsend.begin();
    // //irrecv.enableIRIn();
    // delay(1000); // 等待红外发送器稳定
    // while(1)
    // {
        // RTC_Time now;
        // button.A.read(); // 更新按键状态
        // button.B.read(); // 更新按键状态

        // // 获取电池电量和RTC时间
        // int percent = getBatteryPercent();
        // pcf.getTime(now);
        
        // // 显示电池电量和RTC时间
        // Lcd.setCursor(0, info_y);
        // Lcd.printf(" Battery: %d%%   \n", percent);
        // Lcd.printf(" RTC: %04d-%02d-%02d %02d:%02d:%02d   \n",
        //     now.year, now.month, now.day, now.hour, now.min, now.sec);

        // delay(500); // 刷新间隔，防止刷屏太快

        // if(button.A.pressed()) // 按键A被按下
        // {
        //     Serial0.println("NEC");
        //     irsend.sendNEC(0x00FFE01FUL);
        //     delay(2000);
        //     Serial0.println("Sony");
        //     irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
        //     delay(2000);
        //     Serial0.println("a rawData capture from IRrecvDumpV2");
        //     irsend.sendRaw(rawData, 67, 38);  // Send a raw data capture at 38kHz.
        //     delay(2000);
        //     Serial0.println("a Samsung A/C state from IRrecvDumpV2");
        //     irsend.sendSamsungAC(samsungState);
        //     delay(2000);
        // }

        // if (irrecv.decode(&results)) {
        //     // 直接用 Serial.printf 打印 uint64_t
        //     Serial0.printf("0x%llX\n", results.value);
        //     irrecv.resume();  // Receive the next value
        // }
        // delay(100);          
    // }
}

int DEVICES::getBatteryPercent()
{
    const int adcPin = 9; // IO9
    const float R7 = 100000.0f; // 100k
    const float R8 = 100000.0f; // 100k
    const float adcMax = 4095.0f;
    const float vRef = 3.3f; // ESP32 ADC参考电压

    int raw = analogRead(adcPin);
    float vDiv = (raw / adcMax) * vRef;
    float vBat = vDiv * (R7 + R8) / R8;

    float percent = 0;
    if (vBat >= 4.20f)
        percent = 100;
    else if (vBat >= 4.10f)
        percent = 90 + (vBat - 4.10f) * 100;
    else if (vBat >= 3.95f)
        percent = 80 + (vBat - 3.95f) * 66.7f;
    else if (vBat >= 3.80f)
        percent = 60 + (vBat - 3.80f) * 133.3f;
    else if (vBat >= 3.65f)
        percent = 40 + (vBat - 3.65f) * 133.3f;
    else if (vBat >= 3.50f)
        percent = 20 + (vBat - 3.50f) * 133.3f;
    else if (vBat >= 3.30f)
        percent = 5 + (vBat - 3.30f) * 75.0f;
    else
        percent = 0;

    if (percent > 100.0f) percent = 100.0f;
    if (percent < 0.0f) percent = 0.0f;
    return (int)percent;
}