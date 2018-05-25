/**
 * @file
 * @brief     Main function
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */

#include "robot_arm.hpp"
#include "settings.hpp"
#include "wrap-hwlib.hpp"
#include "uart_connection.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
	
	int coordinates[3] = {150, 150, 150};
	
    RobotArm uarmSwiftPro;

    hwlib::cout << "HELLO WORLD!!!!\r\n ";
    UARTConnection conn(115200, UARTController::ONE);
    long startMsReceive = hwlib::now_us() / 1000;
    long startMsSend = hwlib::now_us() / 1000;

    while (true) {
        // uarmSwiftPro.move(coordinates, 5000);
        if ((hwlib::now_us() / 1000) - startMsSend > 2500) {
            startMsSend = hwlib::now_us() / 1000;
            // conn << "G0 X110 Y110 Z110 F10000\n"; /// Move
            conn << "G0 X150 Y150 Z150 F10000\n"; /// Move
            // hwlib::cout << "Moving" << hwlib::endl;
        }

        if (conn.available() > 0 && (hwlib::now_us() / 1000) - startMsReceive > 30) {
            startMsReceive = hwlib::now_us() / 1000;

            for (unsigned int i = 0; i < conn.available(); i++) {
                hwlib::cout << (char)conn.receive();
            }
        }
    }

    return 0;
}