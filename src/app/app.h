/**
 * @file app.h
 * @author 
 * @brief
 * @version 
 * @date 
 *
 * @copyright 
 *
 */
#pragma once
#include <mooncake.h>
#include <memory>
#include "app_template/app_template.h"

/* Header files locator(Don't remove) */

inline void MeowKit_app_install_callback(mooncake::Mooncake* mooncake, DEVICES* device)
{
    /* Install app locator(Don't remove) */
    mooncake->installApp(std::make_unique<MOONCAKE::APPS::AppTemplate>(device));
    
}