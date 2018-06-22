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
///< Tests for Coordinate3D ADT.
#include "test_coordinate3d.hpp"
///< Tests for movement queue.
#include "test_move_queue.hpp"
///< Tests for type manipulation.
#include "test_type_manipulation.hpp"

UARTLib::MockUART comm(115200);
hwlib::test::pin_in<8> testPinEmergency{1, 0, 1, 0, 1, 0, 1, 1};
hwlib::test::pin_in<8> testPinCancelEmergency{1, 0, 1, 0, 1, 0, 1, 1};
RobotArm::RobotArm uarmSwiftPro(comm, testPinEmergency, testPinCancelEmergency);


TEST_CASE("RobotArm emergency trigger") {
    REQUIRE(!uarmSwiftPro.isEmergencyStopped());

    uarmSwiftPro.emergencyStop();

    REQUIRE(uarmSwiftPro.isEmergencyStopped());
}