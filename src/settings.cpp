#include "settings.hpp"
settings::settings(int motorSpeed) : motorSpeed(motorSpeed) {
}

/// setMotorSpeed()
//
/// This function sets a fixed motorspeed for moving the arm.
void settings::setMotorSpeed(int speed) {
    motorSpeed = speed;
    hwlib::cout << "Set motorspeed to: " << motorSpeed << hwlib::endl;
}

/// returnMotorSpeed()
//
/// This function returns the motor speed
int settings::returnMotorSpeed() {
    return motorSpeed;
}