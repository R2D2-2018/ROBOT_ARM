/**
 * @file
 * @brief     Main function
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */

#include "robot_arm.hpp"
#include "settings.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    RobotArm uarmSwiftPro;

    return 0;
}