// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <Fonts/FreeSerif9pt7b.h>
// #include <My_var.h>
// #include "MAX30100_PulseOximeter.h"
// #define REPORTING_PERIOD_MS  1000
// PulseOximeter pox;

// uint32_t tsLastt = 0;
// void onBeatDetected()
// {
//     Serial.println("Beat!");
// }

// void setsensor()
// {
//     Serial.begin(115200);
//     if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
//     {  
//       Serial.println("SSD1306 allocation failed");
//       for(;;);
//     }

//     display.clearDisplay();
//     display.setTextSize(1);             
//     display.setTextColor(WHITE);        
//     display.setCursor(20,15);             
//     display.println("Welcom to");
//     display.setCursor(0,40);             
//     display.println("DTM E-SMART");
//     display.display();
//     display.setTextSize(1);

//     delay(2000); 
//     Serial.print("Initializing pulse oximeter..");
//     if (!pox.begin()) 
//     {
//         Serial.println("FAILED");
//         for(;;);
//     } 
//     else 
//     {
//         Serial.println("SUCCESS");
//     }
//     pox.setOnBeatDetectedCallback(onBeatDetected);
// }

// void loopsensor()
// {
//     pox.update();
//     if (millis() - tsLastt > REPORTING_PERIOD_MS) 
//     {
//         Serial.print("Heart rate:");
//         Serial.print(pox.getHeartRate());
//         Serial.print("bpm / SpO2:");
//         Serial.print(pox.getSpO2());
//         Serial.println("%");

//         // display.fillRect(50, 12, 78 , 52 , BLACK);
//         // display.setTextSize(1);
//         // display.setTextColor(WHITE);
//         // display.setCursor(53, 23);
//         // display.print(pox.getHeartRate());
//         // display.println(" bpm");
//         // display.setCursor(53, 48);
//         // display.print(pox.getSpO2());
//         // display.println(" %");
//         // display.display();   
//         // tsLastt = millis();
//     }
// }