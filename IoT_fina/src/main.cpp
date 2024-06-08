#include <WiFi.h>
#include <time.h>
#include <ArduinoJson.h>

#include <DNSServer.h>
#include <WiFiManager.h>
#include <HTTPClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Clock.h"
#include "Bitmap.h"
#include "My_var.h"
#include "Display.h"
#include "Weather.h"
#include "Real_time.h"
#include "Other.h"
#include "MQTT.h"
#include "Sensor.h"

TaskHandle_t Task1;
TaskHandle_t Task2;
uint32_t lastsend = 0;

/*-------------------------------------------BUTTON---------------------------------------------------*/
void IRAM_ATTR buttonISR()   //chuyển hiển thị oled
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime > debounceDelay) 
  {
    lastDebounceTime = currentMillis;
    int intValue = static_cast<int>(displayMode);
    intValue = (intValue + 1) % 3;
    displayMode = static_cast<Display_oled>(intValue); 
    buttonPressed_g = true;
    if(message)
    {
      data = true;
    }
    if(displayMode == Time)
    {
      display.fillRect(0, 12, 128 , 52 , BLACK);    
    }
  }
}

/*-------------------------------------------GRAPHICS---------------------------------------------------*/
void graphics()
{
  display_wifi();
  check_time();  
  setloopMQTT();

  if (WiFi.status() == WL_CONNECTED)
  {    
    if(millis() - lastsend > 1000 && client.connected())
    {  
      send();
      lastsend = millis();
    }
  }

  if(displayMode == Time)
  {
    if( (millis() - lastTime_t) > timerDelay_t ) 
    {
      time_up();
      lastTime_t = millis();
    }
  }

  else if(displayMode == Weather)
  {
    display_weather();
    if( (millis() - lastTime_w) > timerDelay_w ) 
    {
      checkAndUpdateWeather();
      lastTime_w = millis();
    }
  }
  
  else if(displayMode == Health)
  {
    hienthi();
  }
}


/*-------------------------------------------LOOP---------------------------------------------------*/
// core 0
void connect_wifi(void * parameter)
{
  for(;;)
  {
    if (WiFi.status() != WL_CONNECTED)
    {      
      wifiManager.autoConnect("IOT_BL");
    }
    else
    {
      Serial.println("Connected to WiFi");
      vTaskDelete(NULL); 
    }
    wifiManager.process();
  }
}

// core 1
void plan(void * parameter)
{
  for(;;)
  {
    graphics();  
    //power_display();  
  }
}


/*-------------------------------------------SET UP---------------------------------------------------*/
void setup() 
{
  Serial.begin(115200);
  
  /*--------------Connect Oled----------------------------*/
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.drawBitmap(105, 0,  bit_map_Pin, 20, 12, WHITE);
  display.setTextColor(WHITE);
  display.display();
  delay(2000); 
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) 
  {
      Serial.println("FAILED");
      for(;;);
  } 
  else 
  {
      Serial.println("SUCCESS");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
  
  /*--------------Button-----------------------------------*/
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
              
  xTaskCreatePinnedToCore(plan,"Loop",10000,NULL,1,&Task2,1);                 
  xTaskCreatePinnedToCore(connect_wifi,"Connect_WIFI", 10000, NULL,1,&Task1,0);     

  setMQTT();  
}

void loop()  
{
  loopsensor();
}
