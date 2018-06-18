/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem, Jeffrey de Waal, Wiebe van Breukelen
 * @license   See LICENSE
 */
#include "robot_arm.hpp"

namespace RobotArm {

RobotArm::RobotArm() : uartConn(115200, UARTController::ONE) {}

void RobotArm::sendGCodeToArm(const char *command) {
    uartConn << command;
}

void RobotArm::move(Coordinate3D coordinates, unsigned int speed) {
    this->speed = speed;
    determineGCode(coordinates, speed);

    sendGCodeToArm(commandBuffer);
}

Coordinate3D RobotArm::getPosition() {
    char response[40];
    uartConn << "#n P2220\n"; /// See Goode commands on page 26 developer guide -
                              /// http://download.ufactory.cc/docs/en/uArm-Swift-Pro-Develper-Guide-171013.pdf

    receiveGcodeResponse(response, 40);

    Coordinate3D coordinate;
    int posXStart, posYStart, posZStart;
    int posXEnd, posYEnd, posZEnd;

    /// Example response: $n ok X100.00 Y100.00 Z100.00\n
    /// We need to split the X, Y and Z coordinates.
    /// We do this by checking the index positions of the 'X', 'Y', 'Z' coordinates.
    /// After this, we check the position of the '.' character. This is the ending character of a position.
    /// Notice that digits after the point are ignored.

    /// Parse the response to get the x position.
    if ((posXStart = getCharPositionStr(response, 'X')) != -1) {
        if ((posXEnd = getCharPositionStr(response, '.', posXStart))) {
            coordinate.x = charToInt(response, posXStart + 1, posXEnd);
        }
    }

    /// Parse the response to get the y position.
    if ((posYStart = getCharPositionStr(response, 'Y')) != -1) {
        if ((posYEnd = getCharPositionStr(response, '.', posYStart))) {
            coordinate.y = charToInt(response, posYStart + 1, posYEnd);
        }
    }

    /// Parse the response to get the z position.
    if ((posZStart = getCharPositionStr(response, 'Z')) != -1) {
        if ((posZEnd = getCharPositionStr(response, '.', posZStart))) {
            coordinate.z = charToInt(response, posZStart + 1, posZEnd);
        }
    }

    return coordinate;
}

void RobotArm::executeAction(const char *newAction) {
    char command[15];
    // strcopy(command, action);
    strcopy(command, newAction);
    stradd(command, "\n");

    sendGCodeToArm(command);
}

void RobotArm::executeAction(Actions newAction) {
    action = newAction;
}

void RobotArm::determineGCode(const Coordinate3D coordinates, int speed) {
    char coordinatesAsTextX[10];
    char coordinatesAsTextY[10];
    char coordinatesAsTextZ[10];
    char speedAsText[10];

    intToChar(coordinates.x, coordinatesAsTextX);
    intToChar(coordinates.y, coordinatesAsTextY);
    intToChar(coordinates.z, coordinatesAsTextZ);
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

void RobotArm::determineGCode(const Actions action) {
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

    for (i = 0; dest[i] != '\0'; i++)
        ;

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

int RobotArm::charToInt(const char *str, const unsigned int posStart, const unsigned int posEnd) const {
    int result = 0;

    for (unsigned int i = posStart; i < posEnd; i++) {
        char digit = static_cast<char>(str[i] - '0');

        result *= 10;
        result += digit;
    }

    return result;
}

int RobotArm::getCharPositionStr(const char *str, const char search, const int searchStart) const {
    unsigned int strIndex = searchStart;

    const char *strSearchStart = str + searchStart;

    while (*strSearchStart != '\0') {
        if (*strSearchStart == search) {
            return strIndex;
        }

        strSearchStart++;
        strIndex++;
    }

    return -1;
}

} // namespace RobotArm