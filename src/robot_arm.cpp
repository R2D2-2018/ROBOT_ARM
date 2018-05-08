#include "robot_arm.hpp"

void robot_arm::move(int coordinates[3]) {
    copy_data(coordinates, goto_coordinates);

    hwlib::cout << "Moving to (" << coordinates[0] << ", " << coordinates[1] << ", " << coordinates[2] << ")" << hwlib::endl;
    output_pin.set(1);
    hwlib::wait_ms(1000);
    output_pin.set(0);
    hwlib::cout << "Finished moving" << hwlib::endl;

    copy_data(goto_coordinates, current_coordinates);
}

void robot_arm::copy_data(int *array1, int *array2) {
    for (int i = 0; i < (sizeof(array1) / 4); i++) {
        array2[i] = array1[i];
    }
}