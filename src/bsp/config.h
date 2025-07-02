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

#define HAL_adcPin 6

/* Button */
#define HAL_A 5
#define HAL_B 4

/* SD card 3线SDMMC 1-bit模式 */
#define SDMMC_SD_PIN_CLK   47
#define SDMMC_SD_PIN_CMD   48
#define SDMMC_SD_PIN_D0    21

/* I2C */
#define HAL_PIN_I2C_SCL 2
#define HAL_PIN_I2C_SDA 1
#define I2CSPEED        400000 // Clock Rate

/* I2S */
#define MCLKPIN             38 // Master Clock
#define BCLKPIN             14 // Bit Clock
#define WSPIN               13 // Word select
#define DOPIN               45 // This is connected to DI on ES8388 (MISO)
#define DIPIN               -1 // This is connected to DO on ES8388 (MOSI)

/* IR */
#define HAL_PIN_IR_TX 15 // IR TX pin
#define HAL_PIN_IR_RX 16 // IR RX pin

/* Common configs */
#define BSP_VERISON                "v1.0"
#define PROJECT_NAME               "MeowKit"