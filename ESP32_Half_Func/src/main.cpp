#include <Arduino.h>
#include <SPI.h> //Ref. https://www.arduino.cn/thread-106240-1-1.html
#include <esp_sleep.h>
#include <Display.h>
#include <General.h>

#define CS_PIN 6
#define HSPI_MISO 16
#define HSPI_MOSI 17
#define HSPI_SCLK 18
#define CD_PIN 7
#define Rst_PIN 8

const int TOUCH_PIN = 2; // 触摸引脚

RTC_DATA_ATTR int count = 0; // 将变量存放于RTC Memory

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  BLEseverSetup();
  AmoledInit();
  touchAttachInterrupt(TOUCH_PIN, myTouchHandler, 1000);

  pinMode(0, INPUT); // 上拉输入模式，INPUT就是不上拉也不下拉，下拉就是INPUT_PULLDOWN,有些引脚内部已经上下拉了的，在后面我提到了
}

void loop()
{
  Bettery_Check();

  /**
   *  
    AMOLED_Clear(0, 125, 0, 240, 1);
    delay(100);
    ace_picture_EVER_Display(60, 0, 7, 12, 0);
    delay(2500);
   */

  ace_Mode3_Display(1, 0);
  ace_Mode3_Data_Display(1, 0);
}