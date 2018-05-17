#include "robot_arm.hpp"

RobotArm::RobotArm() {
}

void RobotArm::move(int coordinates[3], int speed) {
    f.copyData(coordinates, goto_coordinates);

    // hwlib::cout << "Moving to (" << coordinates[0] << ", " << coordinates[1] << ", " << coordinates[2] << ") with speed " <<
    // speed
    // << hwlib::endl;
    // hwlib::wait_ms(1000);
    // Send G-Codes over Serial communication (X, Y, Z, Speed)

    // hwlib::cout << "Finished moving" << hwlib::endl;

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
}
