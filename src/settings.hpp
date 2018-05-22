/**
 * @file    settings.hpp
 * @brief   This class contains different settings to adjust the robot arm.
 * @author  Jeroen van Hattem and Jeffrey de Waal
 * @date    2018-05-17
 */
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "wrap-hwlib.hpp"

class Settings {
  private:
    int motorSpeed;

  public:
    /**
     * @brief Construct a new settings object
     *
     * @param motorSpeed
     */
    Settings(int motorSpeed);
    /**
     * @brief Returns motorspeed
     *
     * For now this justs prints the speed, because we can't move the actual robot arm yet.
     *
     * @return int
     */
    int returnMotorSpeed();
    /**
     * @brief Set the Motor Speed object
     *
     * @param[int] speed
     */
    void setMotorSpeed(int speed);
};

#endif