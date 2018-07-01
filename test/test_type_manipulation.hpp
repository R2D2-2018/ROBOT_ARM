#ifndef TEST_TYPE_MANIPULATION
#define TEST_TYPE_MANIPULATION

#include "catch.hpp"
#include "type_manipulation.hpp"

RobotArm::TypeManipulation typeManip;

TEST_CASE("Append char* with another char*") {
    char text[100] = "Hello, ";
    typeManip.stradd(text, "how are you?");

    REQUIRE_THAT(text, Catch::Matchers::Equals("Hello, how are you?"));
}

TEST_CASE("Copy char* to another char *") {
    char text[100] = "Hello World!";
    typeManip.strcopy(text, "Hi");

    REQUIRE_THAT(text, Catch::Matchers::Equals("Hi"));
}

TEST_CASE("Convert integer to char *") {
    int x = 100;
    char buffer[4];

    typeManip.intToString(x, buffer);

    REQUIRE_THAT(buffer, Catch::Matchers::Equals("100"));
}

TEST_CASE("Convert char * to integer") {
    signed int val = typeManip.charToInt("100", 0, 3);
    signed int val2 = typeManip.charToInt("-100", 0, 4);

    REQUIRE(val == 100);
    REQUIRE(val2 == -100);
}

#endif