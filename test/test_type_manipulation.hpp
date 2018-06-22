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

    typeManip.intToChar(x, buffer);

    REQUIRE_THAT(buffer, Catch::Matchers::Equals("100"));
}

TEST_CASE("Convert char * to integer") {
    char buffer[4] = "100";

    int val = typeManip.charToInt(buffer, 0, 3);

    REQUIRE(val == 100);
}

#endif