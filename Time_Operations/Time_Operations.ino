#include <time.h>
#include <sys/time.h>
#include <WiFi.h>

const char* ssid       = "YOUR_SSID";
const char* password   = "YOUR_PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;


void setup() {
  Serial.begin(115200);

  // Define the time struct
  struct tm ts = {0};

  //Get time from string - strptime
  strptime("2022-03-28T01:34:42.112Z", "%Y-%m-%dT%H:%M:%S.%03dZ", &ts);

  //Get epoch time from struct
  time_t epoch_ts = mktime(&ts);
  Serial.println("Epoch time is " + String(epoch_ts));


  //Get string from time struct - strftime
  char ts_char[50] = {0};
  strftime(ts_char, sizeof(ts_char), "%A, %B %d %Y %H:%M:%S", &ts);
  Serial.println("strftime output is " + String(ts_char));

  //If you need the formatted string just for printing purposes, you can do it without strftime
  Serial.print("Formatted string without strftime: ");
  Serial.println(&ts, "%A, %B %d %Y %H:%M:%S");

  //Get struct from epoch time
  struct tm ts2;
  localtime_r(&epoch_ts, &ts2);
  Serial.print("Time obtained in struct from epoch is: ");
  Serial.println(&ts2, "%A, %B %d %Y %H:%M:%S");

  //Update current time in system RTC, shouldn't be used along with RTC
//  struct timeval tv_ts = {.tv_sec = epoch_ts};
//  settimeofday(&tv_ts, NULL);

  delay(5000);

  //Get RTC time
  struct tm new_ts;
  getLocalTime(&new_ts);
  Serial.print("Current time obtained from RTC is: ");
  Serial.println(&new_ts, "%A, %B %d %Y %H:%M:%S");

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //Get RTC time
  getLocalTime(&new_ts);
  Serial.print("Current time obtained from RTC after NTP config is: ");
  Serial.println(&new_ts, "%A, %B %d %Y %H:%M:%S");

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  delay(5000);

  //Get RTC time
  getLocalTime(&new_ts);
  Serial.print("Current time obtained from RTC after NTP config and WiFi off is: ");
  Serial.println(&new_ts, "%A, %B %d %Y %H:%M:%S");


}

void loop() {
  // put your main code here, to run repeatedly:

}
