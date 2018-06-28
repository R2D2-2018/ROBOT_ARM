#ifndef TYPE_MANIPULATION
#define TYPE_MANIPULATION

#include "wrap-hwlib.hpp"

namespace RobotArm {

class TypeManipulation {
  public:
    /**
     * @brief strcopy function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy of strcpy. dest = destination. src =
     * source.
     *
     * @param Destination string.
     * @param Source string.
     * @return char* Copied string.
     */
    char *strcopy(char *dest, const char *src);

    /**
     * @brief stradd function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy of strcat. dest = destination. src =
     * source.
     *
     * @param Destination string.
     * @param Source string.
     * @return char* Appended string.
     */
    char *stradd(char *dest, const char *src);

    /**
     * @brief intToChar function
     *
     * This function takes an signed integer number and converts it to a char *. The char * will be stored in the
     * 'dest'(destination) parameter. If the integer is negative, the representing character will be signed.
     *
     * @param x Signed integer to convert.
     * @param dest String pointer.
     * @return char* Converted integer.
     */
    char *intToChar(signed int x, char *dest);

    /**
     * @brief intToChar function
     *
     * This function takes an unsigned integer number and converts it to a char *. The char * will be stored in the
     * 'dest'(destination) parameter.
     *
     * @param x Unsigned integer to convert.
     * @param dest String pointer.
     * @return char* Converted integer.
     */
    char *intToChar(unsigned int x, char *dest);

    /**
     * @brief Convert a string to a signed integer.
     *
     * This method only strings containing integers, like "-12345". We cast it to a -12345 integer.
     *
     * @param str Input string.
     * @param posStart
     * @param posEnd
     * @return int Converted string.
     */
    signed int charToInt(const char *str, const unsigned int posStart, const unsigned int posEnd) const;
};

} // namespace RobotArm

#endif
