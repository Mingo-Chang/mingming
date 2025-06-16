/**
 * @file rachel.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "MeowKit.h"
#include <PCA9557.h>
#include "lvgl.h"
#include "ui/ui.h"
#include <mooncake.h>


// using namespace mooncake;
// static Mooncake* _mooncake = nullptr;

void MeowKit::Setup()
{
    printf("Rachel Setup");


}

void MeowKit::Loop() { lv_timer_handler();delay(5); }

void MeowKit::Destroy()
{
    
}
