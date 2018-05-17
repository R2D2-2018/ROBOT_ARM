#include "robot_arm.hpp"
#include "settings.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    int coordinates[3] = {4, 12, 5};
    int speed = 5000;

    hwlib::wait_ms(1000);

    RobotArm uarmSwiftPro;
    uarmSwiftPro.move(coordinates, speed);

    hwlib::cout << uarmSwiftPro.getCoordinates('x') << hwlib::endl;
    hwlib::cout << uarmSwiftPro.getCoordinates('y') << hwlib::endl;
    hwlib::cout << uarmSwiftPro.getCoordinates('z') << hwlib::endl;

    return 0;
}