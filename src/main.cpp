/**
 * @file
 * @brief     Main function
 * @author    Jeroen van Hattem and Jeffrey de Waal, Wiebe van Breukelen, Sam Zandee
 * @license   MIT
 */

#include "coordinate3d.hpp"
#include "robot_arm.hpp"
#include "uart_connection.hpp"
#include "wrap-hwlib.hpp"

namespace target = hwlib::target;

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    target::pin_in emergencyButton = target::pin_in(target::pins::d50);

    UARTConnection conn(115200, UARTController::ONE);
    RobotArm::RobotArm uarmSwiftPro(conn, emergencyButton);
    

    /// Check if the arm is connected.
    if (!uarmSwiftPro.isConnected()) {
        hwlib::cout << "Please connect the uArm Swift Pro" << hwlib::endl;

        /// Wait until the arm is connected using a UART connection.
       while (!uarmSwiftPro.isConnected())
          hwlib::wait_ms(200);
    }

    hwlib::cout << "uArm Swift Pro is connected!" << hwlib::endl;

    /// Little delay to let the uArm Swift Pro boot properly.
    hwlib::wait_ms(2000);

    /// Move the arm to a 3D coordinate.
    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 100, 100), 5000);

    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 150, 100), 5000);

    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 100, 100), 5000);

    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 150, 100), 5000);

    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 100, 100), 5000);

    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 150, 100), 5000);

    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 100, 100), 5000);

    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 150, 100), 5000);

    while (true) {
        hwlib::wait_ms(500);

        /// Receive the position.
       RobotArm::Coordinate3D 
       coordinate = uarmSwiftPro.getPosition();

        /// Display the position.
        hwlib::cout << coordinate.x << ", " << coordinate.y << ", " << coordinate.z << hwlib::endl;
    }

    return 0;
}