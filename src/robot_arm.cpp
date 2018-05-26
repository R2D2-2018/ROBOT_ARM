/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#include "robot_arm.hpp"

void RobotArm::move(int coordinates[3], int _speed) {
    long startMsReceive = hwlib::now_us() / 1000;
    long startMsSend = hwlib::now_us() / 1000;

    for (unsigned int i = 0; i < 3; i++) {
        goto_coordinates[i] = coordinates[i];
    }
    if ((hwlib::now_us() / 1000) - startMsSend > 2500) {
        conn << "G0 X110 Y110 Z110 F10000\n"; /// For now, this is hard coded, using the coordinates passed as parameters will be in
                                              /// the next sprint.
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