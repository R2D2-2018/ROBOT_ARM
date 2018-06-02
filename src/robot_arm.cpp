/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() : conn(115200, UARTController::ONE) {
}

char *RobotArm::strcadd(char *d, const char *s) {
    size_t i, j;
    for (i = 0; d[i] != '\0'; i++) {
    }
    for (j = 0; s[j] != '\0'; j++) {
        d[i + j] = s[j];
    }
    d[i + j] = '\0';
    return d;
}

char *RobotArm::strcopy(char *d, const char *s) {
    char *saved = d;
    while (*s) {
        *d++ = *s++;
    }
    *d++ = '\0';
    *d = 0;
    return saved;
}

char *RobotArm::intToChar(int i, char *p) {
    if (i / 10 == 0) {
        // No more digits.
        *p++ = i + '0';
        *p = '\0';
        return p;
    }

    p = intToChar(i / 10, p);
    *p++ = i % 10 + '0';
    *p = '\0';
    return p;
}

void RobotArm::move(Coordinate3D coordinates, int speed) {

    char coordinatesAsTextX[10];
    char coordinatesAsTextY[10];
    char coordinatesAsTextZ[10];
    char speedAsText[10];
    intToChar(coordinates.getX(), coordinatesAsTextX);
    intToChar(coordinates.getY(), coordinatesAsTextY);
    intToChar(coordinates.getZ(), coordinatesAsTextZ);
    intToChar(speed, speedAsText);

    strcopy(commandBuffer, "G0 X");
    strcadd(commandBuffer, coordinatesAsTextX);
    strcadd(commandBuffer, " Y");
    strcadd(commandBuffer, coordinatesAsTextY);
    strcadd(commandBuffer, " Z");
    strcadd(commandBuffer, coordinatesAsTextZ);
    strcadd(commandBuffer, " F");
    strcadd(commandBuffer, speedAsText);
    strcadd(commandBuffer, "\n");

    if ((hwlib::now_us() / 1000) - startMsSend > 2500) {
        startMsSend = hwlib::now_us() / 1000;
        conn << commandBuffer;
    }

    if (conn.available() > 0 && (hwlib::now_us() / 1000) - startMsReceive > 30) {
        startMsReceive = hwlib::now_us() / 1000;

        for (unsigned int i = 0; i < conn.available(); i++) {
            hwlib::cout << (char)conn.receive();
        }
    }

    speed = speed;
}

void RobotArm::executeAction(Actions action) {
    action = action;
    hwlib::cout << "Executing Action" << hwlib::endl;
}

void RobotArm::determineGCode(int coordinates[3]) {
    hwlib::cout << "Moving to " << coordinates[0] << ", " << coordinates[1] << ", " << coordinates[2] << "." << hwlib::endl;
}

void RobotArm::determineGCode(Actions action) {
    switch (action) {
    case Actions::reset:
        // move({200, 0, 100}, speed);
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
