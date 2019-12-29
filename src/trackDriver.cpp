#include "trackDriver.hpp"

/**
* default trackDriver constructor
* assumes the following rpi[wiringPiPin]->TB6612FNG pin mapping:
*  rpi[29]->AIN01
*  rpi[28]->AIN02
*  rpi[27]->PWMA
*  rpi[25]->BIN01
*  rpi[24]->BIN02
*  rpi[23]->PWMB
*
* @param  void
* @return void
*/
trackDriver::trackDriver()
{
  motor_driver = new TB6612FNG(29,28,27,25,24,23);
  motor_driver->init();
}


/**
* default trackDriver destructor
*
* @param  void
* @return void
*/
trackDriver::~trackDriver()
{
  if(motor_driver != nullptr)
  {
    free(motor_driver);
  }
}


/**
* move tracks on y axis
*
* @param  speed -255 to 255
* @param time, time in ms to run motors for
* @return void
*/
void trackDriver::move(int speed, unsigned int time_ms)
{
  if(speed > 255)
  {
    speed = 255;
  }

  if(speed < -255)
  {
    speed = -255;
  }

  int IN01 = 0;
  int IN02 = 0;

  //move tracks forward
  if(speed > 0)
  {
    IN01 = 0;
    IN02 = 1;
  }
  else if(speed < 0)
  {
    IN01 = 1;
    IN02 = 0;
    speed *= -1;
  }

  //start move
  motor_driver->set_AIN01(IN01);
  motor_driver->set_AIN02(IN02);
  motor_driver->set_PWMA(speed);
  motor_driver->set_BIN01(IN01);
  motor_driver->set_BIN02(IN02);
  motor_driver->set_PWMB(speed);

  delay(time_ms);

  //stop tracks
  IN01 = 0;
  IN02 = 0;
  speed = 0;
  motor_driver->set_AIN01(IN01);
  motor_driver->set_AIN02(IN02);
  motor_driver->set_PWMA(speed);
  motor_driver->set_BIN01(IN01);
  motor_driver->set_BIN02(IN02);
  motor_driver->set_PWMB(speed);

  return;
}


/**
* move track left
*
* @param  speed, 0-255 track speed
* @param  time, time in ms to preform turn
* @return void
*/
void trackDriver::moveTrackLeft(int speed, unsigned int time_ms)
{
  if(speed < 0)
  {
    speed = 0;
  }
  else if(speed > 255)
  {
    speed = 255;
  }

  motor_driver->set_AIN01(1);
  motor_driver->set_AIN02(0);
  motor_driver->set_PWMA(speed);
  motor_driver->set_BIN01(0);
  motor_driver->set_BIN02(1);
  motor_driver->set_PWMB(speed);
  delay(time_ms);

  motor_driver->set_AIN01(0);
  motor_driver->set_AIN02(0);
  motor_driver->set_PWMA(0);
  motor_driver->set_BIN01(0);
  motor_driver->set_BIN02(0);
  motor_driver->set_PWMB(0);

  return;
}

/**
* move track left
*
* @param  speed, 0-255 track speed
* @param  time, time in ms to preform turn
* @return void
*/
void trackDriver::moveTrackRight(int speed, unsigned int time_ms)
{
  if(speed < 0)
  {
    speed = 0;
  }
  else if(speed > 255)
  {
    speed = 255;
  }

  motor_driver->set_AIN01(0);
  motor_driver->set_AIN02(1);
  motor_driver->set_PWMA(speed);
  motor_driver->set_BIN01(1);
  motor_driver->set_BIN02(0);
  motor_driver->set_PWMB(speed);
  delay(time_ms);

  motor_driver->set_AIN01(0);
  motor_driver->set_AIN02(0);
  motor_driver->set_PWMA(0);
  motor_driver->set_BIN01(0);
  motor_driver->set_BIN02(0);
  motor_driver->set_PWMB(0);

  return;
}
