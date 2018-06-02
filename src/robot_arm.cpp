/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() : conn(115200, UARTController::ONE) {
}

void RobotArm::sendGCodeToArm(const char *command) {
    if ((hwlib::now_us() / 1000) - startMsSend > 2500) {
        startMsSend = hwlib::now_us() / 1000;
        hwlib::cout << command << hwlib::endl;
        conn << command;
    }

    if (conn.available() > 0 && (hwlib::now_us() / 1000) - startMsReceive > 30) {
        startMsReceive = hwlib::now_us() / 1000;

        for (unsigned int i = 0; i < conn.available(); i++) {
            hwlib::cout << (char)conn.receive();
        }
    }
}

void RobotArm::move(Coordinate3D coordinates, int speed) {
    speed = speed;
    determineGCode(coordinates, speed);

    sendGCodeToArm(commandBuffer);
}

void RobotArm::executeAction(const char *action) {
    char command[15];
    strcopy(command, action);
    stradd(command, "\n");

    sendGCodeToArm(command);
}

void RobotArm::executeAction(Actions action) {
    action = action;
}

void RobotArm::determineGCode(Coordinate3D coordinates, int speed) {
    char coordinatesAsTextX[10];
    char coordinatesAsTextY[10];
    char coordinatesAsTextZ[10];
    char speedAsText[10];

    intToChar(coordinates.getX(), coordinatesAsTextX);
    intToChar(coordinates.getY(), coordinatesAsTextY);
    intToChar(coordinates.getZ(), coordinatesAsTextZ);
    intToChar(speed, speedAsText);

    strcopy(commandBuffer, "G0 X");
    stradd(commandBuffer, coordinatesAsTextX);
    stradd(commandBuffer, " Y");
    stradd(commandBuffer, coordinatesAsTextY);
    stradd(commandBuffer, " Z");
    stradd(commandBuffer, coordinatesAsTextZ);
    stradd(commandBuffer, " F");
    stradd(commandBuffer, speedAsText);
    stradd(commandBuffer, "\n");
}

void RobotArm::determineGCode(Actions action) {
    switch (action) {
    case Actions::reset:
        hwlib::cout << "Resetting" << hwlib::endl;
        break;
    default:
        hwlib::cout << "This isn't a legit action" << hwlib::endl;
        break;
    }
}

int RobotArm::getSpeed() {
    return speed;
}

char *RobotArm::stradd(char *dest, const char *src) {
    size_t i, j;
    for (i = 0; dest[i] != '\0'; i++) {
    }
    for (j = 0; src[j] != '\0'; j++) {
        dest[i + j] = src[j];
    }
    dest[i + j] = '\0';
    return dest;
}

char *RobotArm::strcopy(char *dest, const char *src) {
    char *saved = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest++ = '\0';
    *dest = 0;
    return saved;
}

char *RobotArm::intToChar(int number, char *dest) {
    if (number / 10 == 0) {
        *dest++ = number + '0';
        *dest = '\0';
        return dest;
    }

    dest = intToChar(number / 10, dest);
    *dest++ = number % 10 + '0';
    *dest = '\0';
    return dest;
}