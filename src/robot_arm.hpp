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

    char commandBuffer[25];

    int speed;
    long startMsReceive = hwlib::now_us() / 1000;
    long startMsSend = hwlib::now_us() / 1000;
    UARTConnection conn;

  public:
    /**
     * @brief Construct a new Robot Arm
     *
     * The default constructor to create a new RobootArm object.
     *
     */
    RobotArm();
    /**
     * @brief Move the arm to the set coordinates
     *
     * This function will take an array existing of 3 integer values and an integer that resembles the speed. These parameters
     * will me transformed into a G-Code. This will be send to the uArm using the uart_connection class.
     *
     * @param coordinates : Coordinate3D
     * @param speed : int
     */
    void move(Coordinate3D coordinates, int speed);
    /**
     * @brief Execute a desired action.
     *
     *
     *
     * @param action : Actions
     */
    void executeAction(Actions action);
    /**
     * @brief Send a G-Code to the uArm
     *
     * This is the function that send the G-Code to the uArm.
     *
     * @param command
     */
    void sendGCodeToArm(const char *command);
    /**
     * @brief Execute a desired action by sending the G-Code
     *
     * With this function, G-Codes can be passed as parameter and control the uArm.
     *
     * @param action : char *
     */
    void executeAction(const char *action);
    /**
     * @brief Determine G-Code for a desired location.
     *
     * Determine G-Code for a desired location.
     *
     * @param coordinates : Coordinate3D
     * @param speed : int
     * @return g-code : char *
     */
    void determineGCode(Coordinate3D coordinates, int speed);
    /**
     * @brief Determine G-Code for a desired action.
     *
     * Determine G-Code for a desired action.
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
    /**
     * @brief intToChar function
     *
     * This function takes an integer number and converts it to a char *. The char * will be stored in the 'dest'(destination)
     * parameter
     *
     * @param x : int
     * @param dest  : char *
     * @return char*
     */
    char *intToChar(int x, char *dest);

    /**
     * @brief strcopy function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy of strcpy. dest = destination. src =
     * source.
     *
     * @param dest : char *
     * @param src : const char *
     * @return char*
     */
    char *strcopy(char *dest, const char *src);

    /**
     * @brief stradd function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy of strcat. dest = destination. src =
     * source.
     *
     * @param dest : char *
     * @param src : const char *
     * @return char*
     */
    char *stradd(char *dest, const char *src);
};

#endif // ROBOTARM_HPP