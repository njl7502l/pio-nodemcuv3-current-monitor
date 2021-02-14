#include "arduino.h"
#include <Ticker.h>
#include <queue>

Ticker ticker;

class SimpleMovingAverage {
private:
  std::queue<int> voltageQueue;
  int voltageQueueSize = 100;
  int averageSum = 0;

public:
  void setVoltageQueueSize(int size) { voltageQueueSize = size; }

  void push(int val) {
    voltageQueue.push(val);
    averageSum += val;

    if (voltageQueue.size() > voltageQueueSize) {
      averageSum -= voltageQueue.front();
      voltageQueue.pop();
    }
  }

  float cal(void) { return averageSum / (float)voltageQueue.size(); }
} sma;

void flash() { sma.push(analogRead(A0)); }

void setup() {
  pinMode(2, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);

  ticker.attach_ms(100, flash); // 100ms,(10Hz)ごとに読み取り
  sma.setVoltageQueueSize(100); // 10秒前の値まで影響を受けるキューのサイズ
}

void loop() {
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);

  Serial.print(sma.cal());
  Serial.println();
}