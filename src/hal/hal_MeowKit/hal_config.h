#pragma once

/**
 * @brief Pin configs
 *
 */
// LCD
#define HAL_PIN_LCD_MOSI 40
#define HAL_PIN_LCD_MISO -1
#define HAL_PIN_LCD_SCLK 41
#define HAL_PIN_LCD_DC 39
#define HAL_PIN_LCD_CS -1
// /* Init PCA9557PW_LCD_CS */
//     PCA9557 io(0x19, &Wire); // 0x19 for iFarm4G board
//     #define LCD_CS_PIN (0)
//     io.pinMode(LCD_CS_PIN, OUTPUT);
//     io.digitalWrite(LCD_CS_PIN, LOW);  // 确保CS引脚正确设置为低电平
#define HAL_PIN_LCD_RST -1
#define HAL_PIN_LCD_BUSY -1
#define HAL_PIN_LCD_BL 42

// Power
#define HAL_PIN_PWR_HOLD 10
#define HAL_PIN_PWR_ON 11 //high：开机

// Button
#define HAL_A 4
#define HAL_B 5

// SD card
#define HAL_PIN_SD_CS -1
#define HAL_PIN_SD_MOSI 21
#define HAL_PIN_SD_MISO 48
#define HAL_PIN_SD_CLK 47

// I2C
#define HAL_PIN_I2C_SCL 2
#define HAL_PIN_I2C_SDA 1