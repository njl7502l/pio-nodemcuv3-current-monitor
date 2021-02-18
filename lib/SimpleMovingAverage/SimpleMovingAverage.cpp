#ifndef SMA_H
#define SMA_H

#include <queue>

class SimpleMovingAverage {
private:
  std::queue<int> voltageQueue;
  unsigned int voltageQueueSize = 100;
  int averageSum = 0;

public:
  void setVoltageQueueSize(unsigned int size) { voltageQueueSize = size; }

  void push(int val) {
    voltageQueue.push(val);
    averageSum += val;

    if (voltageQueue.size() > voltageQueueSize) {
      averageSum -= voltageQueue.front();
      voltageQueue.pop();
    }
  }

  float cal(void) { return averageSum / (float)voltageQueue.size(); }
};

#endif