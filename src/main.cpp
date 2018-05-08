#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);
    auto pin_out = hwlib::target::pin_out(hwlib::target::pins::d7);

    for (;;) {
        pin_out.set(1);
        hwlib::wait_ms(100);
        pin_out.set(0);
        hwlib::wait_ms(100);
    }

    hwlib::cout << "Hello world!" << hwlib::endl;

    return 0;
}