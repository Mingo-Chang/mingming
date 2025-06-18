#pragma once

/**
 * @brief Pin configs
 *
 */
/* LCD */
#define HAL_PIN_LCD_MOSI 40
#define HAL_PIN_LCD_MISO -1
#define HAL_PIN_LCD_SCLK 41
#define HAL_PIN_LCD_DC 39
#define HAL_PIN_LCD_CS -1
#define HAL_PIN_LCD_RST -1
#define HAL_PIN_LCD_BUSY -1
#define HAL_PIN_LCD_BL 42

/* Power */
#define HAL_PIN_PWR_HOLD 10
#define HAL_PIN_PWR_ON 11 //high：开机

/* Button */
#define HAL_A 4
#define HAL_B 5

/* SD card */

/* I2C */
#define HAL_PIN_I2C_SCL 2
#define HAL_PIN_I2C_SDA 1

/* Common configs */
#define BSP_VERISON                "v1.0"
#define PROJECT_NAME               "MeowKit"