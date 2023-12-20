#ifndef _GENERAL_H // 和文件名一致，将.换成_；前面加_。

#define _GENERAL_H // 避免重复声明，使用if no define,define......endif

#include <BLEDevice.h> //Ref. https://blog.csdn.net/weixin_42880082/article/details/120534190
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <driver/touch_pad.h>
#include <SPI.h>

/**
 * 显示当前电量
 */
void Battery_Manage(uint8_t color);

/**
 * 电量显示执行函数
 */
void Bettery_Check();

/**
 *  call if touched
 *  触摸回调函数
 */
void myTouchHandler();

void var_reset(); // 重置所有函数

void RUN_Order(uint8_t var1); // 输入状态

/**
 *  Setup BLE
 */
void BLEseverSetup();

void demo();

void demo2();

#endif