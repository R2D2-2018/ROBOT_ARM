#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "wrap-hwlib.hpp"

class settings {
  private:
    int motorSpeed;

  public:
    /**
     * @brief Construct a new settings object
     *
     * @param motorSpeed
     */
    settings(int motorSpeed);
    /**
     * @brief Returns motorspeed
     *
     * @return int
     */
    int returnMotorSpeed();
    /**
     * @brief Set the Motor Speed object
     *
     * @param speed
     */
    void setMotorSpeed(int speed);
};

#endif