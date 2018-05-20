/**
 * @file
 * @brief     A class with some function used in the project to provent repetition code.
 * @author    Jeroen van Hattem
 * @license   MIT
 */
#include "functions.hpp"

void Functions::copyData(int array1[3], int array2[3]) {
    for (unsigned int i = 0; i < 3; i++) {
        array2[i] = array1[i];
    }
}