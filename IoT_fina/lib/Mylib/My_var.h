/*-------------------------------------------GLOBAL VARIABLE---------------------------------------------------*/
#ifndef GLOVAR_H
#define GLOVAR_H

const char* openWeatherMapApiKey = "b08ee95bc53475ffcb4c730d0cbe3d01";

Adafruit_SSD1306 display(128, 64, &Wire, -1);
ClockLibrary myClock;
WiFiManager wifiManager;

String lat = "21.028333";
String lon = "105.853333";


const int buttonPin = 4; 
const int buttonPin_ = 5; 

// Nội dung hiển thị
enum Display_oled 
{
  Time,
  Weather,
  Health,
 // Receive,
};
Display_oled displayMode = Time;

enum Power
{
  on_display,
  off_display,
};
Power state_power = on_display;

     // flag button graphics
volatile bool buttonPressed_g = false;
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 300; // Thời gian chờ để xử lý nhiễu (milliseconds)

     // flag button power
volatile bool buttonPressed_p = false;
volatile unsigned long lastDebounceTime_ = 0;

     // Time
int timezone = 7 * 3600; // GMT+7
int dst = 0;
char timeString[20];
char dateString[20];

     // Time up time
unsigned long lastTime_t = 0;
unsigned long timerDelay_t = 1000;

     // Time up_weather
String jsonBuffer;
boolean flag_w = false;
static unsigned long lastUpdateTime = 0;

     // Time up display weather
unsigned long lastTime_w = 0;
unsigned long timerDelay_w = 1000;

     // Time up_sensor
uint32_t tsLastReport = 0;
#define REPORTING_PERIOD_MS 1000

boolean flag_wifi = false;

bool bothTasksStarted = false;

#endif
