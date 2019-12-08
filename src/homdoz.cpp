#include <iostream>
#include <pthread.h>

#include "camera_jig_control.hpp"
#include "servo_rpi.hpp"
#include "TB6612FNG.hpp"

using namespace std;

#define NUM_THREADS 5

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
}


int main (int argc, const char * argv[])
{

  wiringPiSetup();
  //servo servo_vertical_cam = servo(13,50);
  //servo servo_horizontal_cam = servo(14,90);
//
  //if (! servo_vertical_cam.calibrate())
  //{
  //  std::cout <<"ERROR"<<std::endl;
  //}
//
  //if (! servo_horizontal_cam.calibrate())
  //{
  //  std::cout <<"ERROR"<<std::endl;
  //}

  //camera_jig_control camera_jig = camera_jig_control();
  TB6612FNG motor_driver = TB6612FNG(29,28,27,25,24,23);
  motor_driver.init();

  motor_driver.set_AIN01(0);
  motor_driver.set_AIN02(1);
  motor_driver.set_PWMA(100);

  motor_driver.set_BIN01(0);
  motor_driver.set_BIN02(1);
  motor_driver.set_PWMB(100);

  delay(5000);
  return 0;
}
