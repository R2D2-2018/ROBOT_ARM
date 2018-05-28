/**
 * @file
 * @brief     Main function
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */

#include "robot_arm.hpp"
#include "settings.hpp"
#include "uart_connection.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    int coordinates[3] = {150, 150, 150};

    RobotArm uarmSwiftPro;

    while (true) {
        uarmSwiftPro.move(coordinates, 5000);
    }
    return 0;
}