#include "settings.hpp"

settings::settings(int motorSpeed) : motorSpeed(motorSpeed) {
}

void settings::setMotorSpeed(int speed) {
    motorSpeed = speed;
}

int settings::getMotorSpeed() {
    return motorSpeed;
}