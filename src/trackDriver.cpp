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
    free motor_driver;
  }
}


/**
* default trackDriver destructor
*
* @param  void
* @return void
*/
void trackDriver::moveTrackLeft(int speed, unsigned int time)
{
}


/**
* default trackDriver destructor
*
* @param  void
* @return void
*/
void trackDriver::turn(unsigned int heading)
{

}
