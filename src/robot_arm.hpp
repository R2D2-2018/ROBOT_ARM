/**
 * @file
 * @brief     This class contains all the functions needed to use the robot arm
 * @author    Jeroen van Hattem, Jeffrey de Waal, Wiebe van Breukelen, Sam Zandee
 * @license   See LICENSE
 */
#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "coordinate3d.hpp"
#include "queue.hpp"
#include "type_manipulation.hpp"
#include "uart_lib.hpp"
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
     * @brief Queue containing arm move actions.
     *
     */
    Queue<Coordinate3D, 50> moveQueue;

    /**
     * @brief Arm motors speed.
     *
     */
    unsigned int speed;

    /**
     * @brief UART connection library instance.
     *
     */
    UARTLib::UARTConnection &uartConn;

    /**
     * @brief bool to set the emergency stop
     *
     */
    bool emergencyStopped;

    /**
     * @brief Button pin used for emergency stop.
     *
     */
    hwlib::pin_in &emergencyButton;

    /**
     * @brief Button pin used to cancel the emergency stop.
     *
     */
    hwlib::pin_in &cancelEmergencyButton;

    /**
     * @brief Arm target position.
     *
     */
    Coordinate3D toGoPos;

    /**
     * @brief Used for type manipulation, parsing Gcode strings, etc.
     *
     * This class created is purely here because the STD variant doesn't work (libc is missing).
     *
     */
    TypeManipulation typeManip;

    /**
     * @brief Get the index of a character within a string/Gcode command.
     *
     * Optionally, the user can give a start position of the search.
     * Note that all strings must be null terminated!
     *
     * @param str Search string.
     * @param search Character to search.
     * @param searchStart Start index of the search.
     * @return int16_t Index position.
     */
    int16_t getCharPositionStr(const char *str, const char search, const uint16_t searchStart = 0) const;

  public:
    /**
     * @brief Construct a new Robot Arm
     *
     * The default constructor to create a new RobootArm object.
     *
     */
    RobotArm(UARTLib::UARTConnection &conn, hwlib::pin_in &emergencyButton, hwlib::pin_in &cancelEmergencyButton);

    /**
     * @brief Move the arm to a new setpoint.
     *
     * This function will take an array existing of 3 integer values and an integer that resembles the speed. These parameters
     * will me transformed into a G-Code. This will be send to the uArm using the uart_connection class.
     *
     * @param coordinates New target Coordinate3D.
     * @param speed Motor speed to reach Coordinate3D.
     */
    void move(const Coordinate3D coordinates, unsigned int newSpeed);

    /**
     * @brief Loop action.
     *
     * This method will check if we are currently performing a arm movement, and if so, increase/decrease
     * the arm position to get closer to the target position.
     * If we are not doing a arm movement, we check if there is one available in the queue.
     *
     */
    void loop();

    /**
     * @brief Execute a action upon the arm.
     *
     * Actions are available with in the Actions enum.
     *
     * @param action Action to perform.
     */
    void executeAction(const Actions action);
    /**
     * @brief Send a G-Code to the uArm.
     *
     * This is the function that sends the G-Code to the uArm.
     *
     * @param command G-Code command in the form of a string.
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
     * @return speed Speed of the arm.
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
     * @brief Receive Gcode string from the uArm Swift Pro using UART.
     *
     * We continuely poll the uArm Swift Pro for new serial data. If the read timeout is reached,
     * we will stop the polling and return 0 (no characters received).
     *
     * @param response Gcode response string.
     * @param responseSize Gcode response string size.
     * @param readTimeout UART receiver timeout in milliseconds.
     * @return uint16_t Amount of character read (including \0).
     */
    uint16_t receiveGcodeResponse(char *response, size_t responseSize, unsigned int readTimeout = 50);

    /**
     * @brief Check if the uArm Swift Pro is connected.
     *
     * By trying to receive the firmware version, we determine if the uArm Swift Pro is connected.
     * If the arm is not connected, a serial receive timeout will occur.
     *
     * @return bool Device connected or not.
     */
    bool isConnected();

    /**
     * @brief Check if the uArm Swift Pro is emergency stopped.
     *
     * @return true Emergency stopped.
     * @return false Not emergency stopped.
     */
    bool isEmergencyStopped();

    /**
     * @brief Emergency stop function
     *
     * This function can be called to make a emergency stop
     */
    void emergencyStop();

    /**
     * @brief No Emergency function.
     *
     * This function can be called to cancel the emergency.
     */
    void cancelEmergency();
};
} // namespace RobotArm

#endif // ROBOTARM_HPP