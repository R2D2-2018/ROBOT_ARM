#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/robot_arm.hpp"

#include "catch.hpp"

RobotArm uarmSwiftPro;
int coordinates[3] = {10, 30, 30};
uarmSwiftPro.move(coordinates, 5000);

TEST_CASE("Example Test Case") {
    REQUIRE(10 == 10);
}

TEST_CASE("Robot Arm Move") {
    REQUIRE(uarmSwiftPro.getCoordinates('x') == 10);
}

TEST_CASE("Robot Arm Move") {
    REQUIRE(uarmSwiftPro.getCoordinates('y') == 30);
}

TEST_CASE("Robot Arm Move") {
    REQUIRE(uarmSwiftPro.getCoordinates('z') == 30);
}