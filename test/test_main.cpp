#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file"

#include "catch.hpp"

#include "../src/settings.cpp"
#include "../src/settings.hpp"

Settings setting(10);

TEST_CASE("Motorspeed constructor") {

    REQUIRE(setting.getMotorSpeed() == 10);

    setting.setMotorSpeed(50);
    REQUIRE(setting.getMotorSpeed() == 50);

    setting.setMotorSpeed(-10);
    REQUIRE(setting.getMotorSpeed() == -10);
}