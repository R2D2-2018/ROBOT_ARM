#include "robot_arm.hpp"
#include "settings.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    int coordinates[3] = {4, 12, 5};
    int speed = 5000;

    hwlib::wait_ms(1000);

    RobotArm uarm_swift_pro(hwlib::target::pin_out(hwlib::target::pins::d7));

    uarm_swift_pro.move(coordinates, speed);

    return 0;
}