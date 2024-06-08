/*-------------------------------------------Display---------------------------------------------------*/
#ifndef DISPLAY_H
#define DISPLAY_H

void display_weather()
{
  display.fillRect(0, 12, 128 , 52 , BLACK);    
  display.drawBitmap(0, 11, bit_map_sun, 30, 30, WHITE);
  display.drawBitmap(0, 40, bit_map_Water, 30, 30, WHITE);
  display.drawBitmap(64, 20, bit_map_Wind, 20, 14, WHITE);
  display.drawBitmap(64, 42, bit_map_Pre, 16, 20, WHITE);
}

void display_health()
{
  display.fillRect(0, 12, 128 , 52 , BLACK);  
  display.drawBitmap(20, 12, bit_map_Tim, 30, 30, WHITE);
  display.drawBitmap(20, 37, bit_map_SpO2, 28, 28, WHITE); 
}

void display_wifi()  
{
  if (WiFi.status() == WL_CONNECTED)
  {
    display.fillRect(0, 0, 13 , 12 , BLACK);  
    display.drawBitmap(0, 0, bit_map_Wifi, 16, 12, WHITE);
  }
  else
  {
    display.fillRect(0, 0, 16 , 12 , BLACK);  
  }
}

#endif
