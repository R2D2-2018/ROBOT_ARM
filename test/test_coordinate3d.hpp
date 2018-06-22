/**
 * @file
 * @brief     Tests for the Coordinate3D ADT
 * @author    Wiebe van Breukelen
 * @license   MIT
 */

#ifndef TEST_COORDINATE_3D
#define TEST_COORDINATE_3D

#include "catch.hpp"
#include "../src/coordinate3d.hpp"

TEST_CASE("Coordinate3D get coord positive") {
    RobotArm::Coordinate3D coord(140, 150, 130);

    REQUIRE(coord.x == 140);
    REQUIRE(coord.y == 150);
    REQUIRE(coord.z == 130);
}

TEST_CASE("coord 3D get coord negative") {
    RobotArm::Coordinate3D coord(-140, -150, -130);

    REQUIRE(coord.x == -140);
    REQUIRE(coord.y == -150);
    REQUIRE(coord.z == -130);
}

TEST_CASE("coord 3D set coord positive") {
    RobotArm::Coordinate3D coord;
    coord.x = 140;
    coord.y = 150;
    coord.z = 130;

    REQUIRE(coord.x == 140);
    REQUIRE(coord.y == 150);
    REQUIRE(coord.z == 130);
}

TEST_CASE("Coordinate3D set coord negative") {
    RobotArm::Coordinate3D coord;
    coord.x = -140;
    coord.y = -150;
    coord.z = -130;

    REQUIRE(coord.x == -140);
    REQUIRE(coord.y == -150);
    REQUIRE(coord.z == -130);
}

TEST_CASE("Coordinate3D addition +=") {
    RobotArm::Coordinate3D coord(150, 40, 30);

    coord += RobotArm::Coordinate3D(30, 20, 10);

    REQUIRE(coord.x == 180);
    REQUIRE(coord.y == 60);
    REQUIRE(coord.z == 40);
}

TEST_CASE("Coordinate3D substract -=") {
    RobotArm::Coordinate3D coord(150, 40, 30);

    coord -= RobotArm::Coordinate3D(30, 20, 10);

    REQUIRE(coord.x == 120);
    REQUIRE(coord.y == 20);
    REQUIRE(coord.z == 20);
}

TEST_CASE("Coordinate3D + Coordinate3D") {
    RobotArm::Coordinate3D coord(150, 40, 30);

    RobotArm::Coordinate3D newCoord = coord + RobotArm::Coordinate3D(30, 20, 10);

    REQUIRE(newCoord.x == 180);
    REQUIRE(newCoord.y == 60);
    REQUIRE(newCoord.z == 40);
}

TEST_CASE("Coordinate3D - Coordinate3D") {
    RobotArm::Coordinate3D coord(150, 40, 0);

    RobotArm::Coordinate3D newCoord = coord - RobotArm::Coordinate3D(30, 20, 10);

    REQUIRE(newCoord.x == 120);
    REQUIRE(newCoord.y == 20);
    REQUIRE(newCoord.z == -10);
}

TEST_CASE("Compare two Coordinate3D objects") {
    RobotArm::Coordinate3D coord(10, 20, 30);
    RobotArm::Coordinate3D coord2(10, 20, 30);

    //REQUIRE(coord == RobotArm::Coordinate3D(10, 20, 30));
    REQUIRE_FALSE((coord != coord2));
}

#endif