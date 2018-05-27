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
    Settings setting1(10);
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    return 0;
}