#include "robot_arm.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    int coordinates[3] = {4, 12, 5};

    hwlib::wait_ms(1000);

    robot_arm uarm_swift_pro(hwlib::target::pin_out(hwlib::target::pins::d7));

    uarm_swift_pro.move(coordinates);

    return 0;
}