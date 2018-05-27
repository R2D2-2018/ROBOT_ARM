#include "settings.hpp"

Settings::Settings(int motorSpeed) : motorSpeed(motorSpeed) {
}

void Settings::setMotorSpeed(int speed) {
    motorSpeed = speed;
}

int Settings::getMotorSpeed() {
    return motorSpeed;
}