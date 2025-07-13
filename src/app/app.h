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
#include "app_template/app_template.h"
#include <mooncake.h>
#include <memory>
#if __cplusplus <= 201103L
namespace std {
    template <typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif


/* Header files locator(Don't remove) */

inline void MeowKit_app_install_callback(mooncake::Mooncake* mooncake, DEVICES* device)
{
    /* Install app locator(Don't remove) */
    mooncake->installApp(std::make_unique<MOONCAKE::APPS::AppTemplate>(device));
    
}