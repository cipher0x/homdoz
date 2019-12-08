#include "camera_jig_control.hpp"


/*! class for controling camera x and y axis
 * This class asumes the following
 *
 * x axis pwm pin is on wiringPi pin 14
 * y axis pwm pin is on wiringPi pin 13
 */


 /**
 * default camera_jig_control constructionr
 *
 * @param  void
 * @return void
 */
camera_jig_control::camera_jig_control()
{
  init();
}


/**
* default camera_jig_control destructionr
*
* @param  void
* @return void
*/
camera_jig_control::~camera_jig_control()
{
  free_camera_control();
}


/**
* move to supplied coordinates
*
* @param  void
* @return 1 on success
  @return 0 on fail
*/
int camera_jig_control::move(int xAngle, int yAngle)
{
  if(x_axis == nullptr || y_axis == nullptr)
  {
    return 1;
  }

  x_axis->move(xAngle);
  y_axis->move(yAngle);

  return 0;
}


/**
* setup cand calibrate servos
*
* @param  void
* @return void
*/
void camera_jig_control::init(void)
{
  x_axis = new servo(14,90);
  y_axis = new servo(13,50);

  x_axis->calibrate();
  y_axis->calibrate();
}


/**
* releases servo pins
*
* @param  void
* @return void
*/
void camera_jig_control::free_camera_control(void)
{
  if(x_axis != nullptr)
  {
    x_axis->free_pin();
  }

  if(y_axis != nullptr)
  {
    y_axis->free_pin();
  }
}
