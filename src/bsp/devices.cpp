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
    //  /* Init lcd */
    // Lcd.init();
    // Lcd.setFont(&fonts::efontCN_12);
    // Lcd.setCursor(0, 0);
    // Lcd.printf("\n BSP %s :)\n Author: Mingo(ง •_•)ง\n", BSP_VERISON);
    // Lcd.printf(" Project: %s\n", PROJECT_NAME);

    /* Init I2C */
    Wire.begin(HAL_PIN_I2C_SDA,HAL_PIN_I2C_SCL);
    Wire.setClock(100000);

    /* Init PCA9557PW_LCD_CS */
    PCA9557 io(0x19, &Wire); // 0x19 for iFarm4G board
    #define LCD_CS_PIN (0)
    io.pinMode(LCD_CS_PIN, OUTPUT);
    io.digitalWrite(LCD_CS_PIN, LOW);  // 确保CS引脚正确设置为低电平


}
void DEVICES::printBspInfos()
{
    printf(" BSP %s ;)\n Author: Mingo(ง •_•)ง \n", BSP_VERISON);
    printf(" Project: %s\n", PROJECT_NAME);
}