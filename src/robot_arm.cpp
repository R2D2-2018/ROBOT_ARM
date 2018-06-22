/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem, Jeffrey de Waal, Wiebe van Breukelen, Sam Zandee
 * @license   See LICENSE
 */
#include "robot_arm.hpp"

namespace RobotArm {

RobotArm::RobotArm(UARTLib::UARTConnection &conn, hwlib::pin_in &emergencyButton, hwlib::pin_in &cancelEmergencyButton) 
: uartConn(conn), emergencyStopped(false), emergencyButton(emergencyButton), cancelEmergencyButton(cancelEmergencyButton), toGoPos(0, 0, 0){}

inline void RobotArm::sendGCodeToArm(const char *command) {
    if (emergencyStopped == false) {
        uartConn << command;
    }
}

void RobotArm::loop() {
    ///< If we are in a emergency, we stop any arm activity.
    if (emergencyStopped) {
        ///< If the noEmergency button is pressed we continue the arm movement.
        if (!cancelEmergencyButton.get()){
            cancelEmergency();
        }
        return;
    }

    ///< If the emergency button is pressed, we stop the arm movement.
    if (!emergencyButton.get()) {
        emergencyStop();
        return;
    }

    ///< If we are still not at our target position, move...
    if (toGoPos != Coordinate3D(0, 0, 0)) {
        Coordinate3D curPos = getPosition();

        if (toGoPos.x > 0) {
            curPos.x++;
            toGoPos.x--;
        } else if (toGoPos.x < 0) {
            curPos.x--;
            toGoPos.x++;
        }

        if (toGoPos.y > 0) {
            curPos.y++;
            toGoPos.y--;
        } else if(toGoPos.y < 0) {
            curPos.y--;
            toGoPos.y++;
        }

        if (toGoPos.z > 0) {
            curPos.z++;
            toGoPos.z--;
        } else if (toGoPos.z < 0) {
            curPos.z--;
            toGoPos.z++;
        }


        determineGCode(curPos, speed);
        sendGCodeToArm(commandBuffer);
        ///< Little wait to prevent serial flooding.
        hwlib::wait_ms(3);

        while (getPosition() != curPos) {
            ///< Little wait to prevent serial flooding.
            hwlib::wait_ms(3);
        }
    } else {
        if (moveQueue.count() > 0) {
            ///< New item available in the move queue, set it at our target position.
            toGoPos = moveQueue.pop() - getPosition();
        }
    }
}

void RobotArm::move(Coordinate3D coordinates, unsigned int speed) {
    this->speed = speed;

    ///< Push a new move action to the move queue.
    moveQueue.push(coordinates);
}

Coordinate3D RobotArm::getPosition() {
    char response[40];
    sendGCodeToArm("#n P2220\n"); ///< See Goode commands on page 26 developer guide -
                                  ///< http://download.ufactory.cc/docs/en/uArm-Swift-Pro-Develper-Guide-171013.pdf

    receiveGcodeResponse(response, 40);

    Coordinate3D coordinate;
    int posXStart, posYStart, posZStart;
    int posXEnd, posYEnd, posZEnd;

    ///< Example response: $n ok X100.00 Y100.00 Z100.00\n
    ///< We need to split the X, Y and Z coordinates.
    ///< We do this by checking the index positions of the 'X', 'Y', 'Z' coordinates.
    ///< After this, we check the position of the '.' character. This is the ending character of a position.
    ///< Notice that digits after the point are ignored.

    ///< Parse the response to get the x position.
    if ((posXStart = getCharPositionStr(response, 'X')) != -1) {
        if ((posXEnd = getCharPositionStr(response, '.', posXStart))) {
            coordinate.x = typeManip.charToInt(response, posXStart + 1, posXEnd);
        }
    }

    ///< Parse the response to get the y position.
    if ((posYStart = getCharPositionStr(response, 'Y')) != -1) {
        if ((posYEnd = getCharPositionStr(response, '.', posYStart))) {
            coordinate.y = typeManip.charToInt(response, posYStart + 1, posYEnd);
        }
    }

    ///< Parse the response to get the z position.
    if ((posZStart = getCharPositionStr(response, 'Z')) != -1) {
        if ((posZEnd = getCharPositionStr(response, '.', posZStart))) {
            coordinate.z = typeManip.charToInt(response, posZStart + 1, posZEnd);
        }
    }

    return coordinate;
}

void RobotArm::executeAction(const char *newAction) {
    char command[15];

    typeManip.strcopy(command, newAction);
    typeManip.stradd(command, "\n");

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

    typeManip.intToChar(coordinates.x, coordinatesAsTextX);
    typeManip.intToChar(coordinates.y, coordinatesAsTextY);
    typeManip.intToChar(coordinates.z, coordinatesAsTextZ);
    typeManip.intToChar(speed, speedAsText);

    typeManip.strcopy(commandBuffer, "G0 X");

    typeManip.stradd(commandBuffer, coordinatesAsTextX);

    typeManip.stradd(commandBuffer, " Y");
    typeManip.stradd(commandBuffer, coordinatesAsTextY);

    typeManip.stradd(commandBuffer, " Z");
    typeManip.stradd(commandBuffer, coordinatesAsTextZ);

    typeManip.stradd(commandBuffer, " F");
    typeManip.stradd(commandBuffer, speedAsText);

    typeManip.stradd(commandBuffer, "\n");
}

void RobotArm::determineGCode(const Actions action) {
    switch (action) {
    case Actions::reset:
        hwlib::cout << "Resetting" << hwlib::endl;
        ///< TODO team 6 - We still need to write a implementation.
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

    ///< Convert to microseconds
    readTimeout *= 1000;

    ///< Decrease the response size as we will include a \0 character by ourselves.
    if (responseSize > 0) {
        responseSize--;
    }

    unsigned int lastRead = hwlib::now_us();

    while (receivingData) {
        if (uartConn.available() > 0) {
            byteRead = uartConn.receive();

            ///< Read until we found an endline character.
            ///< If the responseCharCounter does equal the size of the response array, we stop to prevent writing out of memory.
            if (byteRead != '\n' && responseCharCounter < responseSize) {
                if (response) {
                    ///< Only if the response is not a null pointer, we write to the response array.
                    response[responseCharCounter] = byteRead;
                }
                responseCharCounter += 1;

                lastRead = hwlib::now_us();
            } else if (responseCharCounter > 0) { ///< We have found a endline. If the response char counter is larger then zero
                                                  ///< (there is data), we will stopping polling for new data.
                receivingData = false;
            }
        }

        ///< Check if a timeout occurred. If so, return zero.
        if ((hwlib::now_us() - lastRead) > readTimeout) {
            return 0;
        }
    }

    ///< Add a \0 character to the response, if the is a response.
    if (responseCharCounter > 0) {
        response[responseCharCounter++] = '\0';
    }

    ///< Return the amount of characters read
    return responseCharCounter;
}

bool RobotArm::isConnected() {
    sendGCodeToArm("#n P2203\n");

    ///< By giving a null pointer as a method parameter, we save unnecessarily memory space.
    if (!receiveGcodeResponse(nullptr, 255)) {
        return false;
    }

    return true;
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

void RobotArm::emergencyStop() {
    sendGCodeToArm("#n G2203\n");
    emergencyStopped = true;
}

void RobotArm::cancelEmergency(){
    emergencyStopped = false;
}

} // namespace RobotArm