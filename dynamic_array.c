#include <stdlib.h>
#include "dynamic_array.h"

DynamicArray *da_create() {
    DynamicArray *result = (DynamicArray *)malloc(sizeof(DynamicArray));
    result->size = 0;
    result->capacity = 8;
    result->items = malloc(8 * sizeof(int));
    return result;
}

