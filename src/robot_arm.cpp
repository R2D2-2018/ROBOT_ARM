/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#include "robot_arm.hpp"

RobotArm::RobotArm() :  uartConn(115200, UARTController::ONE) {
}

void RobotArm::sendGCodeToArm(const char *command) {
    //if ((hwlib::now_us() / 1000) - startMsSend > 2500) {
        //startMsSend = hwlib::now_us() / 1000;
        //hwlib::cout << command << hwlib::endl;
        uartConn << command;
    //}

    //if    uartConn.available() > 0 && (hwlib::now_us() / 1000) - startMsReceive > 30) {
        //startMsReceive = hwlib::now_us() / 1000;

        //for (unsigned int i = 0; i <  uartConn.available(); i++) {
            //hwlib::cout << (char  uartConn.receive();
        //}
    //}
}

void RobotArm::move(Coordinate3D coordinates, int speed) {
    this->speed = speed;
    determineGCode(coordinates, speed);

    sendGCodeToArm(commandBuffer);
}

void RobotArm::executeAction(const char *newAction) {
    char command[15];
    //strcopy(command, action);
    strcopy(command, newAction);
    stradd(command, "\n");

    sendGCodeToArm(command);
}

void RobotArm::executeAction(Actions newAction) {
    action = newAction;
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
        /// TODO team 6 - We still need to write a implementation.
        break;
    default:
        hwlib::cout << "This isn't a legit action" << hwlib::endl;
        break;
    }
}

int RobotArm::getSpeed() {
    return speed;
}

int RobotArm::receiveGcodeResponse(char *response, size_t responseSize, unsigned int readTimeout) {
    bool receivingData = true;
    unsigned int responseCharCounter = 0;
    char byteRead = 0;

    /// Convert to microseconds
    readTimeout *= 1000;

    /// Decrease the response size as we will include a \0 character by ourselves.
    if (responseSize > 0) {
        responseSize--;
    }

    unsigned int lastRead = hwlib::now_us();

    while (receivingData) {
        if (uartConn.available() > 0) {
            byteRead = uartConn.receive();

            /// Read until we found an endline character.
            /// If the responseCharCounter does equal the size of the response array, we stop to prevent writing out of memory.
            if (byteRead != '\n' && responseCharCounter < responseSize) {
                if (response) {
                    /// Only if the response is not a null pointer, we write to the response array.
                    response[responseCharCounter] = byteRead;
                }
                responseCharCounter += 1;

                lastRead = hwlib::now_us();
            } else if (responseCharCounter > 0) { /// We have found a endline. If the response char counter is larger then zero
                                                  /// (there is data), we will stopping polling for new data.
                receivingData = false;
            }
        }

        /// Check if a timeout occurred. If so, return zero.
        if ((hwlib::now_us() - lastRead) > readTimeout) {
            return 0;
        }
    }

    /// Add a \0 character to the response, if the is a response.
    if (responseCharCounter > 0) {
        response[responseCharCounter++] = '\0';
    }

    /// Return the amount of characters read
    return responseCharCounter;
}

bool RobotArm::isConnected() {
    uartConn << "#n P2203\n";

    /// By giving a null pointer as a method parameter, we save unnecessarily memory space.
    if (!receiveGcodeResponse(nullptr, 255)) {
        return false;
    }

    return true;
}

char *RobotArm::stradd(char *dest, const char *src) {
    size_t i = 0, j = 0;

    for (j = 0; src[j] != '\0'; j++) {
        dest[i + j] = src[j];
    }

    dest[i + j] = '\0';
    return dest;
}

char *RobotArm::strcopy(char *dest, const char *src) {
    char *saved = dest;
    while (*src != '\0') { // *src
        *dest++ = *src++;
    }

    *dest++ = '\0';
    //*dest = 0; No need to reset the pointer.

    return saved;
}

char *RobotArm::intToChar(int number, char *dest) {
    if ((number / 10) == 0) {
        *dest++ = number + '0';
        *dest = '\0';
        return dest;
    }

    dest = intToChar(number / 10, dest);
    *dest++ = (number % 10) + '0';
    *dest = '\0';
    return dest;
}