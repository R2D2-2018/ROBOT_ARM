#include "type_manipulation.hpp"

namespace RobotArm {
char *TypeManipulation::stradd(char *dest, const char *src) {
    size_t i = 0, j = 0;

    for (i = 0; dest[i] != '\0'; i++) {
    }

    for (j = 0; src[j] != '\0'; j++) {
        dest[i + j] = src[j];
    }

    dest[i + j] = '\0';

    return dest;
}

char *TypeManipulation::strcopy(char *dest, const char *src) {
    char *saved = dest;
    while (*src) {
        *dest++ = *src++;
    }

    *dest++ = '\0';

    return saved;
}

char *TypeManipulation::intToChar(unsigned int number, char *dest) {
    if ((number / 10) == 0) {
        *dest++ = number + '0';
        *dest = '\0';
        return dest;
    }

    dest = intToChar(number / 10, dest);
    *dest++ = (number % 10) + '0';
    *dest = '\0';
    return dest;
}

char* TypeManipulation::intToChar(signed int number, char *dest) {
    if (number < 0) {
        *dest = '-';
        dest++;

        number *= -1;
    }

    return intToChar(static_cast<unsigned int>(number), dest);
}

signed int TypeManipulation::charToInt(const char *str, const unsigned int posStart, const unsigned int posEnd) const {
    signed int result = 0;
    unsigned int start = posStart;
    bool isNegative = false;

    if (str[posStart] == '-') {
        isNegative = true;
        start++;
    }

    for (unsigned int i = start; i < posEnd; i++) {
        char digit = static_cast<char>(str[i] - '0');

        result *= 10;
        result += digit;
    }

    return (isNegative) ? result * -1 : result;
}
} // namespace RobotArm