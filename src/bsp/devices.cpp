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



void DEVICES::init()
{
    Serial0.begin(115200);
    Serial0.println("BSP init...");
    
    /* Init POWER */
    button.PWR_ON.begin();
    button.PWR_ON.read(); // 更新按键状态
    if (button.PWR_ON.held(3000))// 判断按键是否按下并保持 3 秒
    {
        digitalWrite(HAL_PIN_PWR_HOLD,LOW); // 执行开机操作
        delay(1000); // 防止重复触发
    }

    /* Init button A and B*/
    button.A.begin();
    button.B.begin();

    // /* Init I2C */
    Wire.begin(HAL_PIN_I2C_SDA,HAL_PIN_I2C_SCL);
    Wire.setClock(I2CSPEED); // 设置I2C时钟频率

    /* Init PCA9557PW_LCD_CS */
    PCA9557 io(0x19, &Wire); // 0x19 for iFarm4G board
    #define LCD_CS_PIN (0)
    io.pinMode(LCD_CS_PIN, OUTPUT);
    io.digitalWrite(LCD_CS_PIN, LOW); //lcd使能 
    #define PA_EN (1)
    io.pinMode(PA_EN, OUTPUT);
    io.digitalWrite(PA_EN, HIGH); //扬声器使能

    /* Init lcd */
    Lcd.init();
    Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    Lcd.setFont(&fonts::efontCN_16);
    Lcd.setCursor(0, 0);
    Lcd.printf("\n BSP %s :)\n Author: Mingo@whitecliff\n", BSP_VERISON);
    Lcd.printf(" Project: %s\n", PROJECT_NAME);
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
    
}

void DEVICES::printBspInfos()
{
    printf(" BSP %s ;)\n Author: Mingo(ง •_•)ง \n", BSP_VERISON);
    printf(" Project: %s\n", PROJECT_NAME);
}