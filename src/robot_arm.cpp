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

void RobotArm::sendToArm(Actions action) {
}

void RobotArm::move(int coordinates[3], int _speed) {
    for (unsigned int i = 0; i < 3; i++) {
        goto_coordinates[i] = coordinates[i];
    }
    hwlib::wait_ms(500);

    // Move the arm.
    // std::ostringstream g_code_stream;
    // g_code_stream << "G0 X" << coordinates[0] << " Y" << coordinates[1] << " Z" << coordinates[2] << " F" + speed;
    // std::string g_code = g_code_stream.str();

    
    for (unsigned int i = 0; i < 3; i++) {
        current_coordinates[i] = goto_coordinates[i];
    }
    speed = _speed;
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