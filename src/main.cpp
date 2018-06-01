/**
 * @file
 * @brief     Main function
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */

#include "coordinate3d.hpp"
#include "robot_arm.hpp"
#include "settings.hpp"
#include "uart_connection.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    Coordinate3D coordinates(200, 150, 100);

    RobotArm uarmSwiftPro;

    while (true) {
        uarmSwiftPro.move(coordinates, 5000);
        hwlib::wait_ms(400);
    }
    return 0;
}