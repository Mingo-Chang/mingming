/**
 * @file app.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
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

inline void MeowKit_app_install_callback(mooncake::Mooncake* mooncake)
{
    mooncake->installApp(std::make_unique<mooncake::APPS::AppTemplate>());
    /* Install app locator(Don't remove) */
}