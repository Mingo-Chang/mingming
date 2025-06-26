/**
 * @file SDMMC_SD.hpp
 * @author 
 * @brief ESP32-S3 SDMMC 1-bit 3线SD卡驱动
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright (c) 
 * 
 */
#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD_MMC.h>

// 3线SDMMC 1-bit模式引脚定义
#define SDMMC_SD_PIN_CLK   47
#define SDMMC_SD_PIN_CMD   48
#define SDMMC_SD_PIN_D0    21

class SDMMC_SD {
private:
    bool _inited;

public:
    inline SDMMC_SD() : _inited(false) {}
    inline ~SDMMC_SD() {}

    /**
     * @brief 初始化SDMMC 1-bit模式
     * @return true 成功
     * @return false 失败
     */
    inline bool init() {
        // 设置SDMMC引脚
        if (!SD_MMC.setPins(SDMMC_SD_PIN_CLK, SDMMC_SD_PIN_CMD, SDMMC_SD_PIN_D0)) {
            Serial0.println("[SDMMC_SD] setPins failed");
            return false;
        }

        // 1-bit模式初始化
        if (!SD_MMC.begin("/sdcard", true)) {
            Serial0.println("[SDMMC_SD] mount failed");
            return false;
        }

        uint8_t cardType = SD_MMC.cardType();
        if (cardType == CARD_NONE) {
            Serial0.println("[SDMMC_SD] no card attached");
            return false;
        }

        Serial0.print("[SDMMC_SD] init success, type: ");
        if (cardType == CARD_MMC) Serial0.print("MMC");
        else if (cardType == CARD_SD) Serial0.print("SDSC");
        else if (cardType == CARD_SDHC) Serial0.print("SDHC");
        else Serial0.print("UNKNOWN");
        Serial0.printf(" %lluMB\n", SD_MMC.cardSize() / (1024 * 1024));

        _inited = true;
        return true;
    }

    inline bool isInited() const { return _inited; }
};
