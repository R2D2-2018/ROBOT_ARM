/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() : conn(115200, UARTController::ONE) {
}

void RobotArm::move(int coordinates[3], int _speed) {
    for (unsigned int i = 0; i < 3; i++) {
        goto_coordinates[i] = coordinates[i];
    }

    if ((hwlib::now_us() / 1000) - startMsSend > 2500) {
        startMsSend = hwlib::now_us() / 1000;
        conn << "G0 X150 Y150 Z150 F10000\n"; /// Move
    }

    if (conn.available() > 0 && (hwlib::now_us() / 1000) - startMsReceive > 30) {
        startMsReceive = hwlib::now_us() / 1000;

        for (unsigned int i = 0; i < conn.available(); i++) {
            hwlib::cout << (char)conn.receive();
        }
    }

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
    case Actions::reset:
        move({200, 0, 100}, speed);
        hwlib::cout << "Resetting" << hwlib::endl;
    default:
        hwlib::cout << "This isn't a legit action" << hwlib::endl;
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