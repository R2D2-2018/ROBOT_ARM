#include "functions.hpp"

template <typename T>
void Functions::copyData(T *array1, T *array2) {
    for (unsigned int i = 0; i < (sizeof(array1) / 4); i++) {
        array2[i] = array1[i];
    }
}