/**
 * @file
 * @brief     Main function
 * @author    Jeroen van Hattem and Jeffrey de Waal, Wiebe van Breukelen, Sam Zandee
 * @license   MIT
 */

#include "coordinate3d.hpp"
#include "robot_arm.hpp"
#include "uart_lib.hpp"
#include "wrap-hwlib.hpp"

namespace target = hwlib::target;

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    target::pin_in emergencyButton = target::pin_in(target::pins::d50);
    target::pin_in cancelEmergencyButton = target::pin_in(target::pins::d12);

    UARTLib::HardwareUART conn(115200, UARTLib::UARTController::ONE);
    RobotArm::RobotArm uarmSwiftPro(conn, emergencyButton, cancelEmergencyButton);

    ///< Check if the arm is connected.
    if (!uarmSwiftPro.isConnected()) {
        hwlib::cout << "Please connect the uArm Swift Pro" << hwlib::endl;

        ///< Wait until the arm is connected using a UART connection.
        while (!uarmSwiftPro.isConnected())
            hwlib::wait_ms(200);
    }

    hwlib::cout << "uArm Swift Pro is connected!" << hwlib::endl;

    ///< Little delay to let the uArm Swift Pro boot properly.
    hwlib::wait_ms(2000);

    ///< Do some moving.
    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 100, 100), 5000);
    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 200, 150), 5000);
    uarmSwiftPro.move(RobotArm::Coordinate3D(50, 200, 280), 5000);
    uarmSwiftPro.move(RobotArm::Coordinate3D(100, 100, 100), 5000);

    while (true) {
        uarmSwiftPro.loop();
    }

    return 0;
}