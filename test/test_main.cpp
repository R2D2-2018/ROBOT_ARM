/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/robot_arm.hpp"
#include "../src/settings.hpp"

#include "catch.hpp"

RobotArm uarmSwiftPro;

TEST_CASE("Robot Arm move() coordinates positive") {
    int coordinates[3] = {10, 30, 30};

    uarmSwiftPro.move(coordinates, 5000);

    REQUIRE(uarmSwiftPro.getCoordinates('x') == 10);
    REQUIRE(uarmSwiftPro.getCoordinates('y') == 30);
    REQUIRE(uarmSwiftPro.getCoordinates('z') == 30);
}

TEST_CASE("Robot Arm move() coordinates negative") {
    int coordinates[3] = {-10, -30, -30};

    uarmSwiftPro.move(coordinates, 5000);

    REQUIRE(uarmSwiftPro.getCoordinates('x') == -10);
    REQUIRE(uarmSwiftPro.getCoordinates('y') == -30);
    REQUIRE(uarmSwiftPro.getCoordinates('z') == -30);
}

TEST_CASE("Robot Arm move() getSpeed") {
    int coordinates[3] = {10, 30, 30};

    uarmSwiftPro.move(coordinates, 5000);

    REQUIRE(uarmSwiftPro.getSpeed() == 5000);
}


TEST_CASE("set/get setting speed") {
    Settings setting1(10);
    Settings setting2(20);

    setting1.setMotorSpeed(20)

    REQUIRE(setting1.getMotorSpeed() == 20);
    REQUIRE(setting2.getMotorSpeed() == 20);
}