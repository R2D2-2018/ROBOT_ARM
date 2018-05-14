#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "functions.hpp"
#include "wrap-hwlib.hpp"

class RobotArm {
  private:
    Functions f;
    int current_coordinates[3];
    int goto_coordinates[3];
    hwlib::target::pin_out output_pin;

  public:
    /**
     * @brief Construct a new Robot Arm object
     *
     * @param output_pin
     */
    RobotArm(hwlib::target::pin_out output_pin);
    /**
     * @brief Move the arm to the set coordinates
     *
     * @param coordinates
     * @param speed
     */
    void move(int coordinates[3], int speed);
};

#endif