#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

#ifndef TB6612FNG_HPP
#define TB6612FNG_HPP

class TB6612FNG
{
  public:
    TB6612FNG();
    TB6612FNG(int chInA01, int chInA02, int chPWMA, int chInB01, int chInB02, int chPWMB);
    ~TB6612FNG();

    int def_AIN01(int chInA01);
    int def_AIN02(int chInA02);
    int def_BIN01(int chInB01);
    int def_BIN02(int chInB02);
    int def_PWMA(int chPWMA);
    int def_PWMB(int chPWMB);

    int set_AIN01(int value);
    int set_AIN02(int value);
    int set_BIN01(int value);
    int set_BIN02(int value);
    int set_PWMA(int value);
    int set_PWMB(int value);

    int init();
    void free_TB6612FNG();

  private:
    int AIN01 = -1;
    int AIN02 = -1;
    int BIN01 = -1;
    int BIN02 = -1;
    int PWMA = -1;
    int PWMB = -1;
    bool validate_pin(int pin);
    bool validate_all_pins();
    bool validate_binary(int value);
    bool validate_pwm_value(int value);
};

#endif
