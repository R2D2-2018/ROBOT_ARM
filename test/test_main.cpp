/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/robot_arm.hpp"

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

TEST_CASE("Robot Arm move() speed") {
    int coordinates[3] = {10, 30, 30};

    uarmSwiftPro.move(coordinates, 5000);

    REQUIRE(uarmSwiftPro.getSpeed() == 5000);
}