#include "TB6612FNG.hpp"


/*! class for controlling a TB6612FNG driver chip
*   through the RPI wiringPi library
*   NOTE: All rpi pins use the wiringPi numbering scheam
*         All PWM pins are defined from 0 to 255
*
*   USE: call consctructor with maped pins, then call init() to set up pin modes
*
 */


/**
* default TB6612FNG constructionr
*
* @param  void
* @return void
*/
TB6612FNG::TB6612FNG()
{
}


/**
* default TB6612FNG construction for defining all pins
*
* @param  chInA01 define rpi->AIN01 pin
* @param  chInA02 define rpi->AIN02 pin
* @param  chPWMA define rpi->PWMA pin
* @param  chInB01 define rpi->BIN01 pin
* @param  chInB02 define rpi->BIN02 pin
* @param  chPWMB define rpi->PWMB pin
* @return void
*/
TB6612FNG::TB6612FNG(int chInA01, int chInA02, int chPWMA, int chInB01, int chInB02, int chPWMB)
{
  def_AIN01(chInA01);
  def_AIN02(chInA02);
  def_BIN01(chInB01);
  def_BIN02(chInB02);
  def_PWMA(chPWMA);
  def_PWMB(chPWMB);
}


/**
* default TB6612FNG destructionr
*
* @param  void
* @return void
*/
TB6612FNG::~TB6612FNG()
{
  free_TB6612FNG();
}


/**
* define rpi->AIN01 pin
*
* @param  wiringPi pin -> AIN01
* @return void
*/
int TB6612FNG::def_AIN01(int chInA01)
{
  if(validate_pin(chInA01))
  {
    AIN01 = chInA01;
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* define rpi->AIN01 pin
*
* @param  wiringPi pin -> AIN01
* @return void
*/
int TB6612FNG::def_AIN02(int chInA02)
{
  if(validate_pin(chInA02))
  {
    AIN02 = chInA02;
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* define rpi->BIN01 pin
*
* @param  wiringPi pin -> BIN01
* @return void
*/
int TB6612FNG::def_BIN01(int chInB01)
{
  if(validate_pin(chInB01))
  {
    BIN01 = chInB01;
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* define rpi->BIN02 pin
*
* @param  wiringPi pin -> AIN01
* @return void
*/
int TB6612FNG::def_BIN02(int chInB02)
{
  if(validate_pin(chInB02))
  {
    BIN02 = chInB02;
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* define rpi->PWMA pin
*
* @param  wiringPi pin -> PWMA
* @return void
*/
int TB6612FNG::def_PWMA(int chPWMA)
{
  if(validate_pin(chPWMA))
  {
    PWMA = chPWMA;
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* define rpi->PWMB pin
*
* @param  wiringPi pin -> PWMB
* @return void
*/
int TB6612FNG::def_PWMB(int chInB02)
{
  if(validate_pin(chInB02))
  {
    PWMB = chInB02;
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* set AIN01 to 0 or 1
*
* @param binary value
* @return void
*/
int TB6612FNG::set_AIN01(int value)
{
  if(validate_binary(value) && validate_pin(AIN01))
  {
    std::cout<<"AIN01 value: "<<value<<std::endl;
    std::cout<<"AIN pin: "<<AIN01<<std::endl;
    digitalWrite(AIN01, value);
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* set AIN02 to 0 or 1
*
* @param  binary value
* @return void
*/
int TB6612FNG::set_AIN02(int value)
{
  if(validate_binary(value) && validate_pin(AIN02))
  {
    std::cout<<"AIN02 value: "<<value<<std::endl;
    std::cout<<"AIN02 pin: "<<AIN02<<std::endl;
    digitalWrite(AIN02, value);
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* set BIN01 to 0 or 1
*
* @param  binary value
* @return void
*/
int TB6612FNG::set_BIN01(int value)
{
  if(validate_binary(value) && validate_pin(BIN01))
  {
    digitalWrite(BIN01, value);
  }
  else
  {
    return 0;
  }
  return 1;
}


/**
* set BIN02 to 0 or 1
*
* @param  binary value
* @return void
*/
int TB6612FNG::set_BIN02(int value)
{
  if(validate_binary(value) && validate_pin(BIN02))
  {
    digitalWrite(BIN02, value);
  }
  else
  {
    return 0;
  }
  return 1;
}


int TB6612FNG::set_PWMA(int value)
{
  if(validate_pwm_value(value) && validate_pin(PWMA))
  {
    std::cout<<"PWMA: "<<value<<std::endl;
    softPwmWrite(PWMA, value);
  }
  else
  {
    return 0;
  }
  return 1;
}


int TB6612FNG::set_PWMB(int value)
{
  if(validate_pwm_value(value) && validate_pin(PWMB))
  {
    softPwmWrite(PWMB, value);
  }
  else
  {
    return 0;
  }
  return 1;
}


void TB6612FNG::free_TB6612FNG()
{
  set_AIN01(0);
  set_AIN02(0);
  set_BIN01(0);
  set_BIN02(0);
  set_PWMA(0);
  set_PWMB(0);

  pinMode(AIN01, INPUT);
  pinMode(AIN02, INPUT);
  pinMode(BIN01, INPUT);
  pinMode(BIN02, INPUT);
  pinMode(PWMA, INPUT);
  pinMode(PWMB, INPUT);

}


/**
* validates sets all pins to proper I/O mode
*
* @param  void
* @return 1 on success
* @return 0 on error
*/
int TB6612FNG::init()
{
  if(validate_all_pins())
  {
    pinMode(AIN01, OUTPUT);
    pinMode(AIN02, OUTPUT);
    pinMode(BIN01, OUTPUT);
    pinMode(BIN02, OUTPUT);

    softPwmCreate(PWMA,0,255);
    softPwmCreate(PWMB,0,255);
  }
  else
  {
    return 1;
  }
  return 0;
}


/**
* validates a pin nuber
*
* @param  void
* @return true on success
* @return false on error
*/
bool TB6612FNG::validate_pin(int pin)
{
  if(pin >= 0 && pin <= 30)
  {
    return true;
  }
  return false;
}


/**
* validates all pins
*
* @param  void
* @return true on success
* @return false on error
*/
bool TB6612FNG::validate_all_pins()
{
  if(validate_pin(AIN01) &&
     validate_pin(AIN02) &&
     validate_pin(BIN01) &&
     validate_pin(BIN02) &&
     validate_pin(PWMA)  &&
     validate_pin(PWMB))
  {
    return true;
  }
  return false;
}


/**
* validates all binary value, 0 or 1
*
* @param  binary value
* @return true on success
* @return false on error
*/
bool TB6612FNG::validate_binary(int value)
{
  if(value == 0 || value == 1)
  {
    return true;
  }
  return false;
}


/**
* validates pwm value, 0-255
*
* @param  binary value
* @return true on success
* @return false on error
*/
bool TB6612FNG::validate_pwm_value(int value)
{
  if(value >=0 && value <=255)
  {
    return true;
  }
  return false;
}
