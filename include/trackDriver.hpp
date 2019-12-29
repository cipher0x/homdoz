#include "TB6612FNG.hpp"

#ifndef TRACKDRIVER_HPP
#define TRACKDRIVER_HPP

class trackDriver {
  public:
    trackDriver();
    ~trackDriver();
    void move(int speed, unsigned int time_ms);
    void moveTrackLeft(int speed, unsigned int time);
    void moveTrackRight(int speed, unsigned int time);

  private:
    TB6612FNG *motor_driver = nullptr;

};

#endif
