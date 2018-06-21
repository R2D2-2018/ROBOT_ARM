/**
 * @file
 * @brief     This class contains all the functions needed to use the robot arm
 * @author    Jeroen van Hattem, Jeffrey de Waal, Wiebe van Breukelen, Sam Zandee
 * @license   See LICENSE
 */
#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "coordinate3d.hpp"
#include "uart_connection.hpp"
#include "wrap-hwlib.hpp"
#include <cstring>

namespace RobotArm {

class RobotArm {
  private:
    /**
     * @brief Robot arm actions.
     *
     */
    enum class Actions { reset };

    /**
     * @brief Current action.
     *
     */
    Actions action;

    /**
     * @brief Arm command buffer.
     *
     */
    char commandBuffer[25];

    /**
     * @brief Arm motors speed.
     *
     */
    unsigned int speed;

    /**
     * @brief UART connection library instance.
     *
     */
    UARTConnection &uartConn;

    /**
     * @brief bool to set the emergency stop
     * 
     */
    bool emergencyStopped; 

    hwlib::pin_in &emergencyButton;

    /**
     * @brief Get the index of a character within a string.
     *
     * Optionally, the user can give a start position of the search.
     * Note that all strings must be null terminated!
     *
     * @param str Search string.
     * @param search Character to search.
     * @param searchStart Start index of the search.
     * @return int Index position.
     */
    int getCharPositionStr(const char *str, const char search, const int searchStart = 0) const;

  public:
    /**
     * @brief Construct a new Robot Arm
     *
     * The default constructor to create a new RobootArm object.
     *
     */
    RobotArm(UARTConnection &conn, hwlib::pin_in &emergencyButton);

    /**
     * @brief Move the arm to a new setpoint.
     *
     * This function will take an array existing of 3 integer values and an integer that resembles the speed. These parameters
     * will me transformed into a G-Code. This will be send to the uArm using the uart_connection class.
     *
     * @param coordinates New target Coordinate3D.
     * @param speed Motor speed to reach Coordinate3D.
     */
    void move(const Coordinate3D coordinates, unsigned int speed);
    /**
     * @brief Execute a desired action.
     *
     * @param action : Actions
     */
    void executeAction(const Actions action);
    /**
     * @brief Send a G-Code to the uArm.
     *
     * This is the function that sends the G-Code to the uArm.
     *
     * @param command
     */
    inline void sendGCodeToArm(const char *command);

    /**
     * @brief Execute a desired action by sending the G-Code.
     *
     * With this function, G-Codes can be passed as parameter and control the uArm.
     *
     * @param action New action.
     */
    void executeAction(const char *action);
    /**
     * @brief Determine G-Code for a desired location.
     *
     * Determine G-Code for a desired location. This G-Code will be stored in commandBuffer.
     *
     * @param coordinates : Coordinate3D
     * @param speed : int
     */
    void determineGCode(const Coordinate3D coordinates, int speed);

    /**
     * @brief Determine G-Code for desired action.
     *
     * @param action Action.
     */
    void determineGCode(const Actions action);
    /**
     * @brief Return the speed
     *
     * This function returns the speed with which the arm is moving.
     *
     * @return speed
     */
    int getSpeed();

    /**
     * @brief Get the current position of the arm.
     *
     * Note that only the position is correctly received when the arm is NOT moving.
     * This may not be resolvable from the Due size, as the firmware running on the uArm is a black box.
     * The firmware may not handle serial and motor actions concurrent.
     *
     * @return Coordinate3D Current arm position. X, Y or Z is set to zero if something failed during parsing.
     */
    Coordinate3D getPosition();

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
     * @brief Convert a string to a integer.
     *
     * This method only strings containing integers, like "12345". We cast it to a 12345 integer.
     *
     * @param str Input string.
     * @param posStart
     * @param posEnd
     * @return int char
     */
    int charToInt(const char *str, const unsigned int posStart, const unsigned int posEnd) const;

    /**
     * @brief Receive Gcode string from the uArm Swift Pro using UART.
     *
     * We continuely poll the uArm Swift Pro for new serial data. If the read timeout is reached,
     * we will stop the polling and return 0 (no characters received).
     *
     * @param response Gcode response string.
     * @param responseSize Gcode response string size.
     * @param readTimeout UART receiver timeout in milliseconds.
     * @return int Amount of character read (including \0).
     */
    int receiveGcodeResponse(char *response, size_t responseSize, unsigned int readTimeout = 50);

    /**
     * @brief Check if the uArm Swift Pro is connected.
     *
     * By trying to receive the firmware version, we determine if the uArm Swift Pro is connected.
     * If the arm is not connected, a serial receive timeout will occur.
     *
     * @return true Device connected.
     * @return false Device is not connected.
     */
    bool isConnected();

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

    /**
     * @brief Emergency stop function
     * 
     * This function can be called te make a emergency stop
     */
    void emergencyStop(); 
};

} // namespace RobotArm

#endif // ROBOTARM_HPP