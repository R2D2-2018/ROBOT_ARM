#include "settings.hpp"

Settings::Settings(int motorSpeed) : motorSpeed(motorSpeed) {
}

void Settings::setMotorSpeed(int speed) {
    motorSpeed = speed;
    // hwlib::cout << "Set motorspeed to: " << motorSpeed << hwlib::endl;
}

int Settings::returnMotorSpeed() {
    return motorSpeed;
}