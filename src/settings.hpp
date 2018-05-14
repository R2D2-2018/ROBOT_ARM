#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "wrap-hwlib.hpp"
class settings {
  private:
    int motorSpeed;

  public:
    settings(int motorSpeed);
    int returnMotorSpeed();
    void setMotorSpeed(int speed);
};

#endif