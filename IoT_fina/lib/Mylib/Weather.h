/*-------------------------------------------WEATHER---------------------------------------------------*/
#ifndef WEAT_H
#define WEAT_H

int temperatureCelsius, pressure, humidity, windSpeed;
void parseWeatherData(String jsonBuffer, int &temperatureCelsius, int &pressure, int &humidity, int &windSpeed) 
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, jsonBuffer);

  int temperatureKelvin = doc["main"]["temp"];
  pressure = doc["main"]["pressure"];
  humidity = doc["main"]["humidity"];
  windSpeed = doc["wind"]["speed"];

  temperatureCelsius = temperatureKelvin - 273.15;
}

void displayWeather(int temperatureCelsius, int pressure, int humidity, int windSpeed) 
{
  display.fillRect(30, 11, 34, 53, BLACK);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 23);
  display.print(temperatureCelsius);
  display.println((String)((char)247));

  display.setCursor(30, 51);
  display.print(humidity);
  display.println("%");

  display.fillRect(84, 11, 44, 53, BLACK);
  display.setCursor(94, 24);
  display.print(windSpeed);
  display.println(" m/s");

  display.setCursor(84, 51);
  display.print(pressure);
  display.println("hPa");
  display.display();
}

String httpGETRequest(const char* serverName) 
{
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "{}";

  if (httpResponseCode > 0) 
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } 
  else 
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}

void checkAndUpdateWeather() 
{
  if(WiFi.status() == WL_CONNECTED)
  {
    if( (flag_w == false) || ((millis() - lastUpdateTime) >= (1000*60*30)) )   // 30 phút cập nhật thông tin thời tiết 1 lần
    {
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&APPID=" + openWeatherMapApiKey;
      jsonBuffer = httpGETRequest(serverPath.c_str());
 
      parseWeatherData(jsonBuffer, temperatureCelsius, pressure, humidity, windSpeed);
      displayWeather(temperatureCelsius, pressure, humidity, windSpeed);
      lastUpdateTime = millis();
      flag_w = true;
    } 
    else 
    {
      parseWeatherData(jsonBuffer, temperatureCelsius, pressure, humidity, windSpeed);
      displayWeather(temperatureCelsius, pressure, humidity, windSpeed);
    }
  }
  else
  {
     displayWeather(0,0,0,0); 
  }
}

#endif
