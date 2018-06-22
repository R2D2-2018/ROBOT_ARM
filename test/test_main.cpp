/**
 * @file
 * @brief     Test file
 * @author    Jeroen van Hattem, Wiebe van Breukelen
 * @license   MIT
 */
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "../src/robot_arm.hpp"
#include "mock_uart.hpp"

#include "catch.hpp"
#include "test_coordinate3d.hpp"
#include "test_move_queue.hpp"

UARTLib::MockUART comm(115200);
hwlib::test::pin_in<8> testPinIn{1, 0, 1, 0, 1, 0, 1, 1};
RobotArm::RobotArm uarmSwiftPro(comm, testPinIn);


TEST_CASE("Append char* with another char*") {
    char text[100] = "Hello, ";
    uarmSwiftPro.stradd(text, "how are you?");

    REQUIRE_THAT(text, Catch::Matchers::Equals("Hello, how are you?"));
}

TEST_CASE("Copy char* to another char *") {
    char text[100] = "Hello World!";
    uarmSwiftPro.strcopy(text, "Hi");

    REQUIRE_THAT(text, Catch::Matchers::Equals("Hi"));
}

TEST_CASE("Convert integer to char *") {
    int x = 100;
    char buffer[4];

    uarmSwiftPro.intToChar(x, buffer);

    REQUIRE_THAT(buffer, Catch::Matchers::Equals("100"));
}

TEST_CASE("Convert char * to integer") {
    char buffer[4] = "100";

    int val = uarmSwiftPro.charToInt(buffer, 0, 3);

    REQUIRE(val == 100);
}