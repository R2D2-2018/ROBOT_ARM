#include "settings.hpp"
settings::settings(int motorSpeed) : motorSpeed(motorSpeed) {
}

void settings::setMotorSpeed(int speed) {
    motorSpeed = speed;
    hwlib::cout << "Set motorspeed to: " << motorSpeed << hwlib::endl;
}

int settings::returnMotorSpeed() {
    return motorSpeed;
}