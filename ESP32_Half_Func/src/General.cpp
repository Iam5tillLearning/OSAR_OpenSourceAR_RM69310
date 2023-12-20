#include <Arduino.h>
#include <common.h>
#include <Display.h>
#include <General.h>

/**
 * Define parameters for BLE communication
 * See the following for generating UUIDs: https://www.uuidgenerator.net/
 */
#define SERVICE_UUID "12a59900-17cc-11ec-9621-0242ac130002" // UART service UUID
#define CHARACTERISTIC_UUID_RX "12a59e0a-17cc-11ec-9621-0242ac130002"
#define CHARACTERISTIC_UUID_TX "12a5a148-17cc-11ec-9621-0242ac130002"

#define Display false   // 显示
#define NotDisplay true // 不显示

#define End_Test 0 // 帧尾验证,1是开，0是关

/******************蓝牙变量初始化********************/
uint8_t txValue = 0;
BLEServer *pServer = NULL;                   // BLEServer指针 pServer
BLECharacteristic *pTxCharacteristic = NULL; // BLECharacteristic指针 pTxCharacteristic
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;    // 本次连接状态
bool oldDeviceConnected = false; // 上次连接状态

bool BatteryState = false;
const int TOUCH_PIN = 2; // 触摸引脚

uint8_t X_Start = 0;
uint8_t Y_Start = 0;
uint8_t X_End = 0;
uint8_t Y_End = 0;
uint8_t color1 = 0; // 主要颜色
uint8_t color2 = 0; // 背景颜色
uint16_t Color_Var = 0;
uint8_t Text_len = 0;
uint8_t Bitmap = 0;
char Text_String[40];
uint8_t Order_State = 0;
uint8_t Str_size = 0;

bool c1 = 0; // TEST ONLY

uint8_t CharacterPositionX = 112, CharacterPositionY = 0;

/**
 * 显示当前电量
 */
void Battery_Manage(uint8_t color)
{
  int adcValue;
  adcValue = analogRead(4) - 1830; // 分压电阻二分之一，2.1v时2600  1.5v时1830  共770个刻度
  // Serial.print(adcValue);
  if (adcValue > 15)
    AMOLED_Clear(22, 30, 180, 190, color);
  if (adcValue > 154)
    AMOLED_Clear(34, 42, 180, 190, color);
  if (adcValue > 308)
    AMOLED_Clear(46, 54, 180, 190, color);
  if (adcValue > 462)
    AMOLED_Clear(58, 66, 180, 190, color);
  if (adcValue > 616)
    AMOLED_Clear(70, 74, 182, 188, color);
}

/**
 * 电量显示执行函数
 */
void Bettery_Check()
{
  if (BatteryState)
  {
    BatteryState = false;
    // Serial.print("touched");
    Battery_Manage(13);
    delay(5000);
    Battery_Manage(13);
  }
}

/**
 *  call if touched
 *  触摸回调函数
 */
void myTouchHandler()
{
  BatteryState = true;
}

/**
 * 链接中断回调函数
 */
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    DisplayBTlogo(NotDisplay, 13, 0);
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    pServer->getAdvertising()->start(); // Restart Advertising
    DisplayBTlogo(Display, 13, 0);
  }
};

/**
 * 回调函数
 */
class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue(); // 接收信息

    if (rxValue.length() > 0)
    {
      if (rxValue[0] = 0xff) // 帧头ff
      {
        if (rxValue[1] = 0xff) // 帧头ff
        {
          if (rxValue[2] = 0xf0) // 帧头f0
          {
            if (rxValue[3] = 0xa0) // 纯输出英文文字
            {
              std::string rxValue = pCharacteristic->getValue();
              // DisplayNavigationPrompt(rxValue);

              unsigned char Tempdata1[28] = {0x00, 0xFC, 0x04, 0x04, 0xFC, 0x00, 0xFE, 0x82, 0x82, 0xFE, 0x82, 0x82, 0xFE, 0x00, 0x00, 0x07, 0x02, 0x02, 0x07, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38};
              unsigned char Tempdata[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00};
              for (int i = 0; i < rxValue.length(); i++)
              {
                int index = rxValue[i] - ' ';
                for (int i = 0; i < 5; i++)
                {
                  Tempdata[i] = font_5_8[index][i];
                }
                CharacterPositionY = CharacterPositionY + 8;
                if (CharacterPositionY > 116)
                {
                  CharacterPositionX = CharacterPositionX - 8;
                  CharacterPositionY = 0;
                }
                LCD_font_5_7(Tempdata, CharacterPositionX, CharacterPositionY, 13, 0);
              }
              // ChN_Font_14(Tempdata1, CharacterPositionX - 30, CharacterPositionY + 30);
              ace_Mode2_Display(9, 0);
              ace_Mode2_Data_Display(9, 0);
            }                           // 输出纯英文
            else if (rxValue[3] = 0xa1) // 输出文字(中英混合)
            {
              X_Start = rxValue[4];
              Y_Start = rxValue[5];
              color1 = rxValue[6];   // 主要颜色
              color2 = rxValue[7];   // 背景颜色
              Text_len = rxValue[8]; // 文字数量
              uint8_t Text_num = 1;  // 记录字符串序号
              for (uint8_t i = 0; i < Text_len; i++)
              {
                if (rxValue[Text_num + 8] <= 127) // 如果是ascii字符集
                {
                  Text_String[(Text_num - 1)] = rxValue[Text_num + 8];
                  Text_num = Text_num + 1;
                }
                else if (rxValue[Text_num + 8] > 127) // 如果是GB2312字符集
                {
                  Text_String[(Text_num - 1)] = rxValue[Text_num + 8];
                  Text_String[(Text_num - 1 + 1)] = rxValue[Text_num + 8 + 1];
                  Text_num = Text_num + 2;
                }
              }

              if (End_Test == 1)
              {
                if (rxValue[8 + Text_num] = 0xff)
                {
                  if (rxValue[9 + Text_num] = 0xff)
                  {
                    if (rxValue[10 + Text_num] = 0x0f)
                    {
                      Order_State = true;
                      Serial.print("输出文字");
                    }
                  }
                }
              }
              else if (End_Test == 0)
              {
              }
            }
            else if (rxValue[3] = 0xa2) // 输出图案
            {
              X_Start = rxValue[4];
              Y_Start = rxValue[5];
              color1 = rxValue[6];
              Bitmap = rxValue[7];
              if (End_Test == 1)
              {
                if (rxValue[8] = 0xff)
                {
                  if (rxValue[9] = 0xff)
                  {
                    if (rxValue[10] = 0x0f)
                    {
                      Order_State = true;
                      Serial.print("输出图案");
                    }
                  }
                }
              }
            }
            else if (rxValue[3] = 0xa3) // 全局清屏
            {
              if (End_Test == 1)
              {
                if (rxValue[4] = 0xff)
                {
                  if (rxValue[5] = 0xff)
                  {
                    if (rxValue[6] = 0x0f)
                    {
                      Order_State = true;
                      // 全局清屏
                      Serial.print("全局清屏");
                    }
                  }
                }
              }
            }
            else if (rxValue[3] = 0xa4) // 局部清屏
            {
              X_Start = rxValue[4];
              Y_Start = rxValue[5];
              X_End = rxValue[6];
              Y_End = rxValue[7];
              color1 = rxValue[8];
              if (End_Test == 1)
              {
                if (rxValue[9] = 0xff)
                {
                  if (rxValue[10] = 0xff)
                  {
                    if (rxValue[11] = 0x0f)
                    {
                      Order_State = true;
                      Serial.print("全局清屏");
                    }
                  }
                }
              }
            }
            else if (rxValue[3] = 0xa5) // 显示模式切换
            {

            }
          }
        }
      }
      // 向串口输出收到的值
      // Serial.print("RX: ");
      for (int i = 0; i < rxValue.length(); i++)
      {
        Serial.print(rxValue[i]);
        Serial.println();
      }
    }
  }
};

void var_reset() // 重置所有函数
{
  X_Start = 0;
  Y_Start = 0;
  X_End = 0;
  Y_End = 0;
  color1 = 16;
  Color_Var = 0;
  Text_len = 0;
  Bitmap = 0;
  Str_size = 0;
  for (uint8_t i = 0; i < 20; i++)
  {
    Text_String[i] = 0;
  }
  Order_State = 0;
}

void RUN_Order(uint8_t var1) // 输入状态
{
  if (var1 == 1) // 输出文字
  {
    // DisplayString_English(Text_String, Text_len, X_Start, Y_Start, Color_Var);  //仅输出英文
    // DisplayString_Chinese(Str_size, X_Start, Y_Start, Color_Var);
    var_reset(); // 重置变量状态
  }
  else if (var1 == 2) // 输出图案
  {
    var_reset(); // 重置变量状态
  }
  else if (var1 == 3) // 全局清屏
  {
    // AMOLED_Clear(0, 240, 0, 120, 0xffff);
    var_reset(); // 重置变量状态
  }
  else if (var1 == 4) // 局部清屏
  {
    // AMOLED_Clear(Y_Start, Y_Start, X_Start, X_End, Color_Var);
    var_reset(); // 重置变量状态
  }
  else
  {
    var_reset(); // 重置变量状态
  }
}

/**
 *  Setup BLE
 */
void BLEseverSetup()
{
  // 创建一个 BLE 设备
  BLEDevice::init("AirGlass_LingJing");

  // 创建一个 BLE 服务
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks()); // 设置回调
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 创建一个 BLE 特征
  pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);

  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);

  pRxCharacteristic->setCallbacks(new MyCallbacks()); // 设置回调

  pService->start(); // 开始服务

  pServer->getAdvertising()->start(); // 开始广播

  Serial.println(" 等待一个客户端连接，且发送通知... ");
}

void demo()
{
  if (deviceConnected)
  {
    for (uint8_t i = 0; i < 14; i++)
    {
      AMOLED_Clear(0, 120, 0, 112, 0);
      delay(50);
      ace_Mode2_Display(i, 0);
      ace_Mode2_Data_Display(i, 0);
      delay(1000);
    }
  }
}

void demo2()
{
  if (deviceConnected && c1 == 0)
  {
    AMOLED_Clear(0, 125, 0, 120, 2);
    for (uint8_t i = 0; i < 8; i++)
    {
      delay(100);
      ace_picture_EVER_Display(60, 60, i, 7, 0);
      delay(2500);
      c1 = 1;
    }
  }
}