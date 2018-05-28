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
    for (unsigned int i = 0; i < 3; i++) {
        goto_coordinates[i] = coordinates[i];
    }
    hwlib::wait_ms(500);

    for (unsigned int i = 0; i < 3; i++) {
        current_coordinates[i] = goto_coordinates[i];
    }
    speed = _speed;
}

void RobotArm::determineGCode(int coordinates[3]) {
    hwlib::cout << "Moving to " << coordinates[0] << ", " << coordinates[1] << ", " << coordinates[2] << "." << hwlib::endl;
}

void RobotArm::determineGCode(Actions action) {
    switch (action) {
    case reset:
        hwlib::cout << "Resetting" << hwlib::endl;
    case calibrate:
        hwlib::cout << "Calibrating" << hwlib::endl;
    default:
        hwlib::cout << "This isn't a legit move" << hwlib::endl;
    }
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