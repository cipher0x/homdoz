#include <wiringPi.h>
#include <iostream>

#ifndef SERVO_HPP
#define SERVO_HPP

class servo
{
  public:
    servo();
    servo(int wiringPi_pin_number);
    servo(int wiringPi_pin_number, int default_angle);
    ~servo();
    int set_pin(int wiringPi_pin_number);
    int set_pin(int wiringPi_pin_number, int default_angle);
    int free_pin();
    int get_pin(void);
    int calibrate();
    int move(int toAngle);

private:
  bool pin_set = false;
  int pin = -1;
  int default_pin_angle = 90;
  int init();
  int send_pwm_pulse(int toAngle);
};

#endif
