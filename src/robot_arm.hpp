/**
 * @file
 * @brief     This class contains all the functions needed to use the robot arm
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "wrap-hwlib.hpp"
#include <sstream>
#include <string>

class RobotArm {
  private:
    enum class Actions { reset, calibrate };

    Actions action;

    int speed;
    int current_coordinates[3];
    int goto_coordinates[3];

  public:
    /**
     * @brief Construct a new Robot Arm object
     *
     */
    RobotArm();
    /**
     * @brief Move the arm to the set coordinates
     *
     *
     *
     * @param[int[3]] coordinates
     * @param[int] speed
     */
    void move(int coordinates[3], int _speed);
    /**
     * @brief Return the current coordinates
     *
     * @return current_coordinates
     */
    int getCoordinates(char dimension);
    /**
     * @brief Determine G-Code for a desired location.
     *
     *
     *
     * @param[int[3]] coordinates
     */
    void determineGCode(int coordinates[3]);
    /**
     * @brief Determine G-Code for a desired action.
     *
     *
     *
     * @param[Actions]] action
     */
    void determineGCode(Actions action);
    /**
     * @brief Return the speed
     *
     * @return speed
     */
    int getSpeed();
};

#endif