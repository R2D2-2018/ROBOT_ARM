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
     * @param dest : char *
     * @param src : const char *
     * @return char*
     */
    char *strcopy(char *dest, const char *src);

    /**
     * @brief stradd function
     *
     * This function is purely here because the STD variant doesn't work. It's a literal copy of strcat. dest = destination. src =
     * source.
     *
     * @param dest : char *
     * @param src : const char *
     * @return char*
     */
    char *stradd(char *dest, const char *src);

    /**
     * @brief intToChar function
     *
     * This function takes an integer number and converts it to a char *. The char * will be stored in the 'dest'(destination)
     * parameter
     *
     * @param x : int
     * @param dest  : char *
     * @return char*
     */
    char *intToChar(int x, char *dest);

    /**
     * @brief Convert a string to a integer.
     *
     * This method only strings containing integers, like "12345". We cast it to a 12345 integer.
     *
     * @param str Input string.
     * @param posStart
     * @param posEnd
     * @return int char
     */
    int charToInt(const char *str, const unsigned int posStart, const unsigned int posEnd) const;
};

} // namespace RobotArm

#endif