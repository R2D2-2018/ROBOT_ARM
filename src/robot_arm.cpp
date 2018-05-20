/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() {
}

void RobotArm::move(int coordinates[3], int _speed) {
    f.copyData(coordinates, goto_coordinates);
    f.copyData(goto_coordinates, current_coordinates);
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