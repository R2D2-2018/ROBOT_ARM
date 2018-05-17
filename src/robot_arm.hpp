/**
 * @file robot_arm.hpp
 * @brief
 *
 * @author Jeffrey de Waal
 * @date 2018-05-17
 */
#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "functions.hpp"

class RobotArm {
  private:
    Functions f;
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
     * @param coordinates
     * @param speed
     */
    void move(int coordinates[3], int speed);
    /**
     * @brief Return the current coordinates
     *
     * @return current_coordinates
     */
    int getCoordinates(char dimension);
};

#endif