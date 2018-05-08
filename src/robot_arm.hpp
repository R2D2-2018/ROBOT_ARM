#ifndef ROBOT_ARM_HPP
#define ROBOT_ARM_HPP

#include "wrap-hwlib.hpp"

class robot_arm {
  private:
    int current_coordinates[3];
    int goto_coordinates[3];
    hwlib::target::pin_out output_pin;

  public:
    robot_arm(hwlib::target::pin_out output_pin) : output_pin(output_pin) {
    }
    void move(int coordinates[3]);
    void copy_data(int *array1, int *array2);
};

#endif