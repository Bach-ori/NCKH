#ifndef Clock_h
#define Clock_h

#include <Arduino.h>

class ClockLibrary 
{
  public:
    ClockLibrary();
    // Initialize the clock with the current time
    void begin(int hour, int minute, int second, int day, int month, int year);
    // Update the clock
    void update();
    // Get current time as string (HH:MM:SS)
    String getTimeString();
    // Get current date as string (DD/MM/YYYY)
    String getDateString();
    // Get elapsed time in seconds
    unsigned long getElapsedTime();
  private:
    int _hour;
    int _minute;
    int _second;
    int _day;
    int _month;
    int _year;
    int daysInMonth(int month, int year);
    unsigned long _previousMillis;
    // Helper function to update time based on elapsed milliseconds
    void updateTime(unsigned long elapsedMillis);
};

#endif
