/*-------------------------------------------OTHER------------------------------------------------*/
#ifndef OTHER_H
#define OTHER_H

#include <WiFi.h>
#include <time.h>
#include <ArduinoJson.h>

#include <DNSServer.h>
#include <WiFiManager.h>
#include <HTTPClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

unsigned long up_time_30m = 0;
unsigned long up_KhamBenh = 0;

boolean message = false;
boolean data = false;

String Phong = "";
String Stt = "";

void check_time()  // cập nhật realtime 1 lần đầu tiên cho lần đầu tiên kết nối wifi
{
  if (WiFi.status() == WL_CONNECTED && flag_wifi == false)
  {
    real_time(); 
    flag_wifi = true;
  }
  else if(WiFi.status() == WL_CONNECTED && flag_wifi == true)
  {
    flag_wifi = true;
    if(millis() - up_time_30m > 1000*60*15)  // mỗi 15p cập nhật lại time (nếu cần)
    {
      flag_wifi = false;
      up_time_30m = millis();
    }
  }
  else if(WiFi.status() != WL_CONNECTED && flag_wifi == true)
  {
     flag_wifi = false;
  }
}

void Split(String data) 
{
  // Tạo một bản sao của chuỗi để tránh làm thay đổi chuỗi ban đầu
  String temp = data;
  
  // Tách chuỗi thành hai phần dựa trên dấu cách
  Phong = temp.substring(0, temp.indexOf(' ')); // Lấy phần đầu cho đến dấu cách đầu tiên
  Stt = temp.substring(temp.indexOf(' ') + 1); // Lấy phần còn lại sau dấu cách đầu tiên
  
  // In ra kết quả
  Serial.println("Phong: " + Phong);
  Serial.println("Stt: " + Stt);
}

void hienthikhambenh()
{
  if(message && data)
  {
    display.fillRect(0, 55, 123 , 13 , BLACK);
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("P. " + Phong + " STT: " + Stt);
    display.display();
    data = false;
  }
  else if(message == false && data ==  false)
  {
    display.fillRect(0, 55, 128 , 14 , BLACK);
    display.display();
  }
}

void time_up()
{
  myClock.update();
  display.fillRect(0, 12, 128 , 38 , BLACK);
  display.setTextSize(2);
  display.setCursor(30, 20);
  display.println(myClock.getTimeString());
  display.setCursor(30, 36);
  display.setTextSize(1);
  display.println(myClock.getDateString());
  display.display();
  hienthikhambenh();
}

#endif
