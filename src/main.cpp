#include "arduino.h"

#include <Ticker.h> // 正確な移動平均の計算のためのタイマ割り込み

#include <SimpleMovingAverage.cpp>
#include "Secret.h"
#include "wifi.hpp"
#include "aws.hpp"

Ticker ticker;
SimpleMovingAverage sma;

void flash() {
  // sma.push(analogRead(A0));
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Serial.print("input something: ");
  while (1) {
    Serial.print("input something: ");
    if (Serial.available() > 0) {
      Serial.println(Serial.read());
      break;
    }
    delay(1000);
  }

  /*
   * 60Hzの交流電圧を全波整流して平滑後の波形には120Hzでリプルが乗る。
   * このリプル電圧の周期は8.333msなのでこの周期の倍数の移動平均を取ればリプルの影響を除ける。
   *
   * 8.333msは3周期で25msとなるので、今回は直近25ms間の平均をとる。
   */

  setupWifi();
  setupAWS();

  sma.setVoltageQueueSize(25);
  ticker.attach_ms(1, flash); // 100ms,(10Hz)ごとに読み取り
}

void loop() {
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
  publish(1);
  // Serial.print(sma.cal());
  // Serial.println();
}
