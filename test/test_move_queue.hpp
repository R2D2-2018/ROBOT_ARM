/**
 * @file
 * @brief     Tests for the move queue.
 * @author    Wiebe van Breukelen
 * @license   MIT
 */

#ifndef TEST_MOVE_QUEUE
#define TEST_MOVE_QUEUE

#include "catch.hpp"
#include "queue.hpp"
#include "coordinate3d.hpp"

const int queueSize = 250;
Queue<RobotArm::Coordinate3D, queueSize> queue;

TEST_CASE("Clear queue") {
    queue.push(RobotArm::Coordinate3D(10, 20, 30));
    queue.push(RobotArm::Coordinate3D(10, 20, 30));

    queue.clear();

    REQUIRE(queue.count() == 0);
}

TEST_CASE("Add Coordinate3D object to queue") {
    queue.clear();
    queue.push(RobotArm::Coordinate3D(10, 20, 30));

    REQUIRE(queue.count() == 1);
}

TEST_CASE("Add multiple Coordinate3D objects to queue") {
    queue.clear();

    for (int i = 0; i < queueSize + 10; i++) {
        queue.push(RobotArm::Coordinate3D(10, 20, 30));
    }

    REQUIRE(queue.count() == 250);
}

TEST_CASE("Pop from queue") {
    queue.clear();
    queue.push(RobotArm::Coordinate3D(10, 20, 30));

    REQUIRE((queue.pop() == RobotArm::Coordinate3D(10, 20, 30)));

    REQUIRE(queue.count() == 0);
}

TEST_CASE("Peek from queue") {
    queue.clear();
    queue.push(RobotArm::Coordinate3D(10, 20, 30));

    REQUIRE((queue.peek() == RobotArm::Coordinate3D(10, 20, 30)));
    REQUIRE(queue.count() == 1);
}

#endif