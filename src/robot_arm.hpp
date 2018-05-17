#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include "functions.hpp"
// #include "wrap-hwlib.hpp"

class RobotArm {
  private:
    Functions f;
    int current_coordinates[3];
    int goto_coordinates[3];

  public:
    RobotArm();
    /**
     * @brief Move the arm to the set coordinates
     *
     * @param coordinates
     * @param speed
     */
    void move(int coordinates[3], int speed);
    /**
     * @brief Return the current coordinates
     *
     * @return current_coordinates
     */
    int getCoordinates(char dimension);
};

#endif