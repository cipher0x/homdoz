#include "servo_rpi.hpp"

#ifndef CAMERA_JIG_CONTROL_HPP
#define CAMERA_JIG_CONTROL_HPP

class camera_jig_control
{
  public:
    camera_jig_control();
    ~camera_jig_control();
    int move(int xAngle, int yAngle);

  private:
    servo *x_axis = nullptr;
    servo *y_axis = nullptr;
    void init(void);
    void free_camera_control(void);
};
#endif
