/**
 * @file
 * @brief     This class contains all the functions needed to use the robot arm
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   See LICENSE
 */
#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "coordinate3d.hpp"
#include "uart_connection.hpp"
#include "wrap-hwlib.hpp"
#include <cstring>

class RobotArm {
  private:
    enum class Actions { reset };

    Actions action;

    int speed;
    // int current_coordinates[3];
    // int goto_coordinates[3];
    long startMsReceive = hwlib::now_us() / 1000;
    long startMsSend = hwlib::now_us() / 1000;
    char commandBuffer[25];
    int bufferCounter = 0;
    UARTConnection conn;

  public:
    /**
     * @brief Construct a new Robot Arm
     *
     * The default constructor to create a new RobootArm object.
     *
     */
    RobotArm();

    char *intToString(int x);
    /**
     * @brief strcpy function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy.
     *
     * @param d : char *
     * @param s : const char *
     * @return char*
     */
    char *strcopy(char *d, const char *s);
    char *strcadd(char *d, const char *s);
    /**
     * @brief Move the arm to the set coordinates
     *
     * This function will take an array existing of 3 integer values and an integer that resembles the speed. These parameters
     * will me transformed into a G-Code. This will be send to the uArm using the uart_connection class.
     *
     * @param[int[3]] coordinates
     * @param[int] speed
     */
    void move(Coordinate3D coordinates, int speed);
    /**
     * @brief Execute a desired action.
     *
     *
     *
     * @param[Actions]] action
     */
    void executeAction(Actions action);
    /**
     * @brief Return the current coordinates
     *
     * This function returns the coordinates of where the robot arm is or is moving to.
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
     * This function returns the speed with which the arm is moving.
     *
     * @return speed
     */
    int getSpeed();
};

#endif // ROBOTARM_HPP