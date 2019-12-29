#ifndef TB6612FNG_HPP
#define TB6612FNG_HPP

#ifndef TRACKDRIVER_HPP
#define TRACKDRIVER_HPP

class trackDriver {
  public:
    trackDriver();
    ~trackDriver();
    void move(int speed, unsigned int time);
    void turn(unsigned int heading);

  private:
    TB6612FNG *motor_driver = nullptr;
    void moveTrackLeft(int speed, unsigned int time);
    void moveTrackRight(int speed, unsigned int time);

};

#endif
