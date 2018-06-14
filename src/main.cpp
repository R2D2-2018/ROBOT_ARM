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

    RobotArm::RobotArm uarmSwiftPro;

    while (true) {
        uarmSwiftPro.move(Coordinate3D(200, 150, 100), 5000);
        uarmSwiftPro.executeAction("M2231 V1\n");
    }

    return 0;
}