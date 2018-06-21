/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/coordinate3d.hpp"
#include "../src/robot_arm.hpp"
#include "mock_uart.hpp"

#include "catch.hpp"

UARTLib::MockUART comm(115200);
hwlib::test::pin_in<8> testPinIn{1, 0, 1, 0, 1, 0, 1, 1};
RobotArm::RobotArm uarmSwiftPro(comm, testPinIn);
char text[100];

TEST_CASE("Append char* with another char*") {
    uarmSwiftPro.stradd(text, "how are you?");

    //REQUIRE(text == "Hi, how are you?");
}

TEST_CASE("Copy char* to another char *") {
    uarmSwiftPro.strcopy(text, "Hi, ");

    //REQUIRE(text == "Hi, ");
}

TEST_CASE("Convert integer to char *") {
    int x = 100;
    char buffer[5];

    uarmSwiftPro.intToChar(x, buffer);

    //REQUIRE(buffer == "100");
}

TEST_CASE("Coordinates 3D get coordinates positive") {
    RobotArm::Coordinate3D coordinates(140, 150, 130);

    REQUIRE(coordinates.x == 140);
    REQUIRE(coordinates.y == 150);
    REQUIRE(coordinates.z == 130);
}

TEST_CASE("Coordinates 3D get coordinates negative") {
    RobotArm::Coordinate3D coordinates(-140, -150, -130);

    REQUIRE(coordinates.x == -140);
    REQUIRE(coordinates.y == -150);
    REQUIRE(coordinates.z == -130);
}

TEST_CASE("Coordinates 3D set coordinates positive") {
    RobotArm::Coordinate3D coordinates;
    coordinates.x = 140;
    coordinates.y = 150;
    coordinates.z = 130;

    REQUIRE(coordinates.x == 140);
    REQUIRE(coordinates.y == 150);
    REQUIRE(coordinates.z == 130);
}

TEST_CASE("Coordinates 3D set coordinates negative") {
    RobotArm::Coordinate3D coordinates;
    coordinates.x = -140;
    coordinates.y = -150;
    coordinates.z = -130;

    REQUIRE(coordinates.x == -140);
    REQUIRE(coordinates.y == -150);
    REQUIRE(coordinates.z == -130);
}