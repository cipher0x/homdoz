#include "servo_rpi.hpp"

/*! class for controling pwm to servo motors
 * This class asumes a fixed pwm period of 20ms
 * PWM is emplmented through bit banging thus will work
 * with any gpio pin on the rpi.
 *
 * WARNING: This class should not be used if precise servo control is required
 *          You should use external hardware or one of the pins that
            support hardware pwm control, this class supports nither of those

 *  .5ms  ->   0
 *  1ms   ->  45
 *  1.5ms -> 135
 *  2.5ms -> 180
 */


/**
* default servo constructionr
*
* @param  void
* @return void
*/
servo::servo()
{
}


/**
* servo constructionr
*
* @param  wiringPi_pin_number wiringPi library for the pin number that
          will control the servo
* @return void
*/
servo::servo(int wiringPi_pin_number)
{
  set_pin(wiringPi_pin_number);
}


servo::servo(int wiringPi_pin_number, int default_angle)
{
  set_pin(wiringPi_pin_number, default_angle);
}

servo::~servo()
{
  free_pin();
}


/**
* set_pin defines servo pwm control pin
* If pin has already been set you must call free_pin before setting a new one
* @param  wiringPi_pin_number wiringPi library for the pin number that
          will control the servo
* @param default_angle default pin operation angle
* @return 1 on success
* @return 0 on error
*/
int servo::set_pin(int wiringPi_pin_number)
{
  if (wiringPi_pin_number > 0 && wiringPi_pin_number <= 30 && pin_set == false)
  {
    pin = wiringPi_pin_number;
    pinMode(pin,OUTPUT);
    pin_set = true;
  }
  else
  {
    return 0;
  }

  return 1;
}


/**
* set_pin defines servo pwm control pin
* If pin has already been set you must call free_pin before setting a new one
* @param  wiringPi_pin_number wiringPi library for the pin number that
          will control the servo
* @param default_angle default pin operation angle
* @return 1 on success
* @return 0 on error
*/
int servo::set_pin(int wiringPi_pin_number, int default_angle)
{
  if (wiringPi_pin_number > 0   &&
      wiringPi_pin_number <= 30 &&
      pin_set == false          &&
      default_angle >= 0        &&
      default_angle <= 180)
  {
    set_pin(wiringPi_pin_number);
    default_pin_angle = default_angle;

    return 1;
  }

  return 0;
}


/**
* removes pwm setup from a set pin
*
* @param  void
* @return 1 on success
* @return 0 on error
*/
int servo::free_pin()
{
  if(pin_set)
  {
    digitalWrite(pin,LOW);
    pinMode(pin,INPUT);
    pin = -1;
    pin_set = false;
    }
  else
  {
    return 1;
  }

  return 0;
}


/**
* get_pin gets the set pin
*
* @param  void
* @return -1 on error
* @return number of current pin
*/
int servo::get_pin(void)
{
  if(pin_set)
  {
    return pin;
  }
  else
  {
    return -1;
  }
}


/**
* calibrate the servo
*
* @param  void
* @return 0 on error
* @return 1 on success
*/
int servo::calibrate()
{
  std::cout << "PIN: " << pin << std::endl;
  std::cout << "pin_set: " << pin_set << std::endl;
  if(pin_set)
  {
    std::cout << "running calibration" << std::endl;
    int angle = 0;
    for(angle=0; angle <= 180; angle++)
    {
      send_pwm_pulse(angle);
    }
    for(angle=180; angle >= 0; angle--)
    {
      send_pwm_pulse(angle);
    }

    move(default_pin_angle);
  }
  else
  {
    return 0;
  }

  return 1;
}

/**
* pulse the servo to the supplied angle
*
* @param  1 on success
* @return 0 on error
*/
int servo::send_pwm_pulse(int toAngle)
{
  if(pin_set)
  {
    int pulseWidth=0;
    pulseWidth = (toAngle * 11) + 500;
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pin, LOW);
    delay(20 - pulseWidth / 1000);
    std::cout << "Angle: " << toAngle << std::endl;
  }
  else
  {
    return 0;
  }

  return 1;

}


/**
* send multiple pwm_pulses to requested angle
* t
* @param  1 on success
* @return 0 on error
*/
int servo::move(int toAngle)
{
  if(pin_set)
  {
    for(int i = 0; i != 20; i++)
    {
      send_pwm_pulse(toAngle);
    }
  }
  else
  {
    return 0;
  }

  return 1;
}
