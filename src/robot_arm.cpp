/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#include "robot_arm.hpp"
#include <sstream>
#include <string>

RobotArm::RobotArm() {
}

void RobotArm::move(int coordinates[3], int _speed) {
    for (unsigned int i = 0; i < 3; i++) {
        goto_coordinates[i] = coordinates[i];
    }

    // Move the arm.

    for (unsigned int i = 0; i < 3; i++) {
        current_coordinates[i] = goto_coordinates[i];
    }
    speed = _speed;
}

int RobotArm::getCoordinates(char dimension) {
    if (dimension == 'x') {
        return current_coordinates[0];
    } else if (dimension == 'y') {
        return current_coordinates[1];
    } else if (dimension == 'z') {
        return current_coordinates[2];
    }
    return 0;
}

int RobotArm::getSpeed() {
    return speed;
}