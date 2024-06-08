#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <My_var.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS  1000
PulseOximeter pox;

uint32_t tsLastt = 0;
void onBeatDetected()
{
    Serial.println("Beat!");
}

float h = 0;
int s = 0;
uint32_t updateSensor = 0;

void loopsensor()
{
    pox.update();
    if (millis() - tsLastt > 1000 && millis() > 10000) 
    {
        h = pox.getHeartRate();
        s = pox.getSpO2();

        tsLastt = millis();  

        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
    }
}

void hienthi()
{
  if (millis() - updateSensor >= 1000) 
    {
        display_health();
        display.fillRect(50, 12, 78 , 52 , BLACK);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(53, 23);
        display.print(h);
        display.println(" bpm");
        display.setCursor(53, 48);
        display.print(s);
        display.println(" %");
        display.display();   
        updateSensor = millis();
    }
}

void send()  
{
    sendMQTT(h,s);
}


