/**
 * @file
 * @brief     This class contains all the functions needed to use the robot arm
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "uart_connection.hpp"
#include "wrap-hwlib.hpp"
#include <sstream>
#include <string>
// #include <stringstream>

class RobotArm {
  private:
    int speed;
    int current_coordinates[3];
    int goto_coordinates[3];
    UARTConnection conn;

  public:
    /**
     * @brief Construct a new Robot Arm object
     *
     */
    RobotArm() : conn(115200, UARTController::ONE) {
    }
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
     * @brief Return the speed
     *
     * @return speed
     */
    int getSpeed();
};

#endif