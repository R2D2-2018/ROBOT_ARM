/**
 * @file
 * @brief     Settings for the robotarm
 *
 * @author    Jeffrey de Waal
 * @license   See LICENSE
 */

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

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
     * @brief Get the Motor Speed
     *
     * @return int
     */
    int getMotorSpeed();
    /**
     * @brief Set the Motor Speed
     *
     * @param speed
     */
    void setMotorSpeed(int speed);
};

#endif