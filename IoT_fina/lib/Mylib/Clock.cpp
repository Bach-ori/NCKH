#include "Clock.h"

ClockLibrary::ClockLibrary() {
  // Constructor
}

void ClockLibrary::begin(int hour, int minute, int second, int day, int month, int year) {
  _hour = hour;
  _minute = minute;
  _second = second;
  _day = day;
  _month = month;
  _year = year;
  _previousMillis = millis();
}

void ClockLibrary::update() 
{
  unsigned long currentMillis = millis();
  unsigned long elapsedMillis = currentMillis - _previousMillis;

  updateTime(elapsedMillis);
  _previousMillis = currentMillis;
}

String ClockLibrary::getTimeString() 
{
  String hourStr = (_hour < 10) ? "0" + String(_hour) : String(_hour);
  String minuteStr = (_minute < 10) ? "0" + String(_minute) : String(_minute);
  String secondStr = (_second < 10) ? "0" + String(_second) : String(_second);
  return hourStr + ":" + minuteStr;// + ":" + secondStr;
}

String ClockLibrary::getDateString() 
{
  String dayStr = (_day < 10) ? "0" + String(_day) : String(_day);
  String monthStr = (_month < 10) ? "0" + String(_month) : String(_month);
  String yearStr = String(_year);
  return dayStr + "/" + monthStr + "/" + yearStr;
}

unsigned long ClockLibrary::getElapsedTime() 
{
  return millis() - _previousMillis;
}

void ClockLibrary::updateTime(unsigned long elapsedMillis) 
{
  _second += elapsedMillis / 1000;

  // Adjust minutes and hours if needed
  while (_second >= 60) 
  {
    _second -= 60;
    _minute++;
  }
  while (_minute >= 60) 
  {
    _minute -= 60;
    _hour++;
  }
  while (_hour >= 24) 
  {
    _hour -= 24;
    _day++;
  }
  while (_day > daysInMonth(_month, _year)) 
  {
    _day -= daysInMonth(_month, _year);
    _month++;
  }
  while (_month > 12) 
  {
    _month -= 12;
    _year++;
  }
}

int ClockLibrary::daysInMonth(int month, int year) 
{
  switch (month) 
  {
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
    case 2:
      return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
    default:
      return 31;
  }
}
