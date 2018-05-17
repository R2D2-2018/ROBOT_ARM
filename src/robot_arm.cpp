#include "robot_arm.hpp"

RobotArm::RobotArm() {
}

void RobotArm::move(int coordinates[3], int speed) {
    f.copyData(coordinates, goto_coordinates);
    f.copyData(goto_coordinates, current_coordinates);
}

int RobotArm::getCoordinates(char dimension) {
    if (dimension == 'x') {
        return current_coordinates[0];
    } else if (dimension == 'y') {
        return current_coordinates[1];
    } else if (dimension == 'z') {
        return current_coordinates[2];
    }
    return 0;
}
