#ifndef WIFI_HPP
#define WIFI_HPP

#include <time.h>
#include <ESP8266WiFi.h>
#include "secret.h"

#define JST 3600 * 9

char currentTimeStr[19];

void getCurrentDateTimeStr() {
  time_t t;
  struct tm *tm;

  t = time(NULL);
  tm = localtime(&t);
  sprintf(currentTimeStr, "%04d/%02d/%02d %02d:%02d:%02d", tm->tm_year + 1900,
          tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void setupWifi() {
  Serial.println();
  Serial.print("connecting WiFi ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" Finished !");

  configTime(JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

  int i = 0;
  time_t t = 0;
  while (t < 160937596 && i <= 30) {
    delay(500);
    Serial.print("*");
    t = time(NULL);
    i++;
  }

  getCurrentDateTimeStr();
  Serial.printf("Current date-time is ");
  Serial.println(currentTimeStr);
}

#endif