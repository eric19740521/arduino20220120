#include "BluetoothSerial.h"
#include <TFT_eSPI.h>        //LCD函式庫
#include <Button2.h>


BluetoothSerial SerialBT;

TFT_eSPI tft = TFT_eSPI();

#define BUTTON_A_PIN  0  //按鍵A，PIN 0
#define BUTTON_B_PIN  35 //按鍵B，PIN 35
Button2 buttonA = Button2(BUTTON_A_PIN);
Button2 buttonB = Button2(BUTTON_B_PIN);

void setup() {
  Serial.begin(115200);

  //char *pin = "0119";
  //SerialBT.setPin(pin);
  SerialBT.begin("ESP_A01"); //後面加true從端


  tft.begin();               // 初始化LCD
  tft.setRotation(1);  // landscape
  tft.fillScreen(TFT_BLACK); // 用全黑清除螢幕
  tft.setSwapBytes(true);

  tft.drawRect(0, 0, 240, 130, TFT_RED);//方形空心
  //tft.drawLine(0, 40, 240, 40, TFT_YELLOW);//畫線


  //文字 T-Display
  tft.setFreeFont(&FreeSerifBold12pt7b);
  tft.setCursor(30, 95, 4);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(2);
  tft.printf("ESP_A01");

  buttonA.setPressedHandler(press);   //建立A按鍵按下Pressed的事件
  buttonA.setReleasedHandler(release);//建立A按鍵放開Released的事件
  buttonB.setPressedHandler(press);   //建立B按鍵按下Pressed的事件
  buttonB.setReleasedHandler(release);//建立B按鍵放開Released的事件




}

String readString;
char str;  // 儲存接收資料的變數
void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }


  while (SerialBT.available()) {
    delay(10);  //small delay to allow input buffer to fill

    char c = SerialBT.read();  //gets one byte from serial buffer
    if (c == ',') {
      break;
    }  //breaks out of capture loop to print readstring
    readString += c;
  } //makes the string readString

  if (readString.length() > 0) {
    Serial.println(readString); //prints string to serial port out
    tft.fillScreen(TFT_BLACK); // 用全黑清除螢幕
    //文字 ESP32
    tft.setFreeFont(&FreeSerifBold12pt7b);
    // 设置起始坐标(20, 10)，4 号字体
    tft.setCursor(20, 10);
    // 设置文本颜色为白色，黑色文本背景
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(4);
    // 设置显示的文字，注意这里有个换行符 \n 产生的效果
    tft.println(readString);

    readString = ""; //clears variable for new input
  }




  delay(20);

  buttonA.loop();  //重複按鍵的觸發設定
  buttonB.loop();

}



void press(Button2& btn) {
  if (btn == buttonA) {   //按下A按鍵，更換圖片

    SerialBT.write('A');


  } else if (btn == buttonB) {  //按下B按鍵，顯示文字

    SerialBT.write('B');
  }


}

void release(Button2& btn) {
  if (btn == buttonA) {          //放開按鍵A，恢復顯示圖片

    //SerialBT.write('1');

  } else if (btn == buttonB) {   //放開按鍵A，恢復顯示圖片

    //SerialBT.write('2');
  }
}
