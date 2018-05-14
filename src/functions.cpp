#include "functions.hpp"

/// CopyData()
//
/// This function can be used to copy data from one array to another, I created this function because of code repetition.
void Functions::copyData(int *array1, int *array2) {
    for (unsigned int i = 0; i < (sizeof(array1) / 4); i++) {
        array2[i] = array1[i];
    }
}