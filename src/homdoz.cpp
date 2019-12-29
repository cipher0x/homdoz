#include <iostream>
#include <pthread.h>
#include <signal.h>

//tmp for unbufferd input
#include <unistd.h>
#include <termios.h>

#include "camera_jig_control.hpp"
#include "servo_rpi.hpp"
#include "TB6612FNG.hpp"
#include "trackDriver.hpp"

//temp for unbuffered input
char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
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
  int cam_x = 90;
  int cam_y = 50;
  camera_jig_control camera_jig = camera_jig_control();
  camera_jig.move(cam_x, cam_y);

  TB6612FNG motor_driver = TB6612FNG(29,28,27,25,24,23);
//
  //motor_driver.set_AIN01(0);
  //motor_driver.set_AIN02(1);
  //motor_driver.set_PWMA(100);
//
  //motor_driver.set_BIN01(0);
  //motor_driver.set_BIN02(1);
  //motor_driver.set_PWMB(100);
//
  //delay(5000);
  trackDriver tDrive;
  //tDrive.move(30, 2000);
  char in;
  bool stopLoop = false;
  int mvTime = 500; //500ms
  int speed = 50;


  while(true) {
    in = getch();

    if (in == '\33' )// 33 signals special key
    {
      in = getch(); //read in [
      in = getch(); //read in arrow
      cout << in << endl;
      switch (in) {
        case 'A':
          cam_y++;
          camera_jig.move(cam_x, cam_y);
          break;
        case 'B': //down
          cam_y--;
          camera_jig.move(cam_x, cam_y);
          break;
        case 'C': //right
        cam_x--;
        camera_jig.move(cam_x, cam_y);
          break;
        case 'D': //left
        cam_x++;
        camera_jig.move(cam_x, cam_y);
          break;
      }
    }
    switch (in) {
      case 27:
      stopLoop = true;
      break;

      case 'q':
      stopLoop = true;
      break;

      case 'w':
      tDrive.move(speed, mvTime);
      break;

      case 's':
      tDrive.move((speed*-1), mvTime);
      break;

      case 'a':
      tDrive.moveTrackLeft(speed, mvTime);
      break;

      case 'd':
      tDrive.moveTrackRight(speed, mvTime);
      break;

      case 'i':
      speed++;
      std::cout << speed << std::endl;
      break;

      case 'k':
      speed--;
      std::cout << speed << std::endl;
      break;

      case 'c':
      cam_x = 90;
      cam_y = 50;
      camera_jig.move(cam_x, cam_y);
    }

    if(stopLoop) {
      break;
    }
  }
  return 0;
}
