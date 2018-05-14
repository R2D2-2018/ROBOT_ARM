#include "robotarm.hpp"

/// RobotArm()
//
/// Default constructor for the RobotArm class
RobotArm::RobotArm(hwlib::target::pin_out output_pin) : output_pin(output_pin) {
}

/// Move
//
/// With this function, the RobotArm can move to the desired location. It requires a 3D location and the speed with which the arm
/// has to move
void RobotArm::move(int coordinates[3], int speed) {
    f.copyData(coordinates, goto_coordinates);

    hwlib::cout << "Moving to (" << coordinates[0] << ", " << coordinates[1] << ", " << coordinates[2] << ") with speed " << speed
                << hwlib::endl;
    output_pin.set(1);
    hwlib::wait_ms(1000);
    // Send G-Codes over Serial communication (X, Y, Z, Speed)

    output_pin.set(0);
    hwlib::cout << "Finished moving" << hwlib::endl;

    f.copyData(goto_coordinates, current_coordinates);
}
