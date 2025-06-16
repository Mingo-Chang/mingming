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
#pragma once
#include "porting/touch.hpp"
#include "porting/display.hpp"
#include <PCA9557.h>

class DEVICES
{
private:

public:
    CTP ctp;
    LGFX Lcd;


    void init();
    void printBspInfos();
};