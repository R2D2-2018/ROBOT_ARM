/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() : conn(115200, UARTController::ONE) {
}

char *RobotArm::intToString(int x) {
    if (x < 1000) {
        char string[3];
        char charValue;
        int value = 0;

        if (x > 100) {
            value = x % 10;
            charValue = value + '0';
            x = (x - value) / 10;
            string[2] = charValue;

            value = x % 10;
            charValue = value + '0';
            x = (x - value) / 10;
            string[1] = charValue;

            charValue = x + '0';
            string[0] = charValue;
            return string;
        }

        else if (x < 100) {
            value = x % 10;
            charValue = value + '0';

            string[2] = charValue;
            x = (x - value) / 10;
            charValue = x + '0';
            string[1] = charValue;

            string[0] = '0';
            return string;
        }
    }

    if (x > 1000 && x < 10000) {
        char string[4];
        char charValue;
        int value = 0;

        value = x % 10;
        charValue = value + '0';
        x = (x - value) / 10;
        string[3] = charValue;

        value = x % 10;
        charValue = value + '0';
        x = (x - value) / 10;
        string[2] = charValue;

        value = x % 10;
        charValue = value + '0';
        x = (x - value) / 10;
        string[1] = charValue;

        charValue = x + '0';
        string[0] = charValue;
        return string;
    }

    if (x > 10000 && x < 100000) {
        int size = 5;
        char string[5];
        char charValue;
        int value = 0;

        for (int i = size; i > 0; i--) {
            value = x % 10;
            charValue = value + '0';
            x = (x - value) / 10;
            string[4] = charValue;

            value = x % 10;
            charValue = value + '0';
            x = (x - value) / 10;
            string[3] = charValue;

            value = x % 10;
            charValue = value + '0';
            x = (x - value) / 10;
            string[2] = charValue;

            value = x % 10;
            charValue = value + '0';
            x = (x - value) / 10;
            string[1] = charValue;

            charValue = x + '0';
            string[0] = charValue;
            return string;
        }
    }
}

void RobotArm::move(Coordinate3D coordinates, int speed) {
    // for (unsigned int i = 0; i < 3; i++) {
    //     goto_coordinates[i] = coordinates[i];
    // }
    // hwlib::string<100> test = "Hello world!";
    // hwlib::string<24> command = "";
    // command += "G0 X";
    // command += intToString(coordinates.getX());
    // command += " Y";
    // command += intToString(coordinates.getY());
    // command += " Z";
    // command += intToString(coordinates.getZ());
    // command += " F";
    // command += intToString(speed);
    // command += "\n";

    strcopy(commandBuffer, "G0 X");
    strcadd(commandBuffer, intToString(coordinates.getX()));
    // hwlib::cout << commandBuffer << hwlib::endl;
    strcadd(commandBuffer, " Y");
    strcadd(commandBuffer, intToString(coordinates.getY()));
    // hwlib::cout << commandBuffer << hwlib::endl;
    strcadd(commandBuffer, " Z");
    strcadd(commandBuffer, intToString(coordinates.getZ()));
    // hwlib::cout << commandBuffer << hwlib::endl;
    strcadd(commandBuffer, " F");
    strcadd(commandBuffer, intToString(speed));
    hwlib::cout << commandBuffer << hwlib::endl;
    strcadd(commandBuffer, "\n");
    hwlib::cout << commandBuffer << hwlib::endl;

    // hwlib::cout << command << hwlib::endl;
    hwlib::cout << commandBuffer << hwlib::endl;

    if ((hwlib::now_us() / 1000) - startMsSend > 2500) {
        startMsSend = hwlib::now_us() / 1000;
        // conn << "G0 X" << intToString(coordinates.getX()) << " Y" << intToString(coordinates.getY()) << " Z" <<
        // intToString(coordinates.getZ() << "F" << intToString(speed) << "\n"; /// Move conn << commandBuffer;
        conn << command;
    }

    if (conn.available() > 0 && (hwlib::now_us() / 1000) - startMsReceive > 30) {
        startMsReceive = hwlib::now_us() / 1000;

        for (unsigned int i = 0; i < conn.available(); i++) {
            hwlib::cout << (char)conn.receive();
        }
    }

    // for (unsigned int i = 0; i < 3; i++) {
    //     current_coordinates[i] = goto_coordinates[i];
    // }
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
    // switch (action) {
    // case Actions::reset:
    //     // move({200, 0, 100}, speed);
    //     hwlib::cout << "Resetting" << hwlib::endl;
    //     break;
    // default:
    //     hwlib::cout << "This isn't a legit action" << hwlib::endl;
    //     xbreak;
    // }
}

int RobotArm::getCoordinates(char dimension) {
    // if (dimension == 'x') {
    //     return coordinates.getX();
    // } else if (dimension == 'y') {
    //     return current_coordinates[1];
    // } else if (dimension == 'z') {
    //     return current_coordinates[2];
    // }
    return 0;
}

int RobotArm::getSpeed() {
    return speed;
}

char *RobotArm::strcadd(char *d, const char *s) {
    // int size = sizeof(d) + sizeof(s);
    char saved[24];
    char *saved = d;
    int counter = 0;
    // int i = 0;

    hwlib::cout << "Adding stuff" << hwlib::endl;

    for (int i = 0; i < sizeof(d); i++) {
        saved[i] = d[i];
        hwlib::cout << d[i];
        counter++;
    }

    for (int i = 0; i < sizeof(s); i++) {
        saved[counter + i] = s[i];
    }

    // while (*d) {
    //     *d++ = *d++;
    // }

    // while (*s) {
    //     *d++ = *s++;
    // }
    // *d = 0;
    // strcopy(d + sizeof(d), s);
    return saved;
}

char *RobotArm::strcopy(char *d, const char *s) {
    char *saved = d;
    while (*s) {
        *d++ = *s++;
    }
    *d = 0;
    hwlib::cout << saved << hwlib::endl;
    return saved;
}
