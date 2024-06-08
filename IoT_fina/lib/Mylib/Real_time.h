/*-------------------------------------------REAL TIME _ WIFI------------------------------------------------*/
#ifndef REALT_H
#define REALT_H

void real_time()
{  //cập nhật thời gian thực lần đầu vào đồng hồ offonline
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  time_t now;
  struct tm* p_tm;
  do
  {
    now = time(nullptr);
    delay(1000);
  } while (now < 1000000000);  // Wait until a reasonable time value is obtained (adjust as needed)
  p_tm = localtime(&now);
  myClock.begin(p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec, p_tm->tm_mday, p_tm->tm_mon + 1, p_tm->tm_year + 1900);
           //chuyển đối số vào thư viện
  snprintf(timeString, sizeof(timeString), "%02d:%02d:%02d", p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);
  snprintf(dateString, sizeof(dateString), "%02d/%02d/%04d", p_tm->tm_mday, p_tm->tm_mon + 1, p_tm->tm_year + 1900);
  Serial.print("Current date and time: ");
  Serial.print(dateString);
  Serial.print(" ");
  Serial.println(timeString);
}

#endif
