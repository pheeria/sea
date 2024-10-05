#include <stdlib.h>
#include "dynamic_array.h"

DynamicArray *da_create() {
    DynamicArray *result = (DynamicArray *)malloc(sizeof(DynamicArray));
    result->size = 0;
    result->capacity = 8;
    result->items = malloc(8 * sizeof(int));
    return result;
}

void da_destroy(DynamicArray *da) {
    free(da->items);
    free(da);
}

int da_push(DynamicArray *da, int value) {
    if (da->size < da->capacity) {
        da->items[da->size++] = value;
    }
    return SUCCESS;
}

int da_pop(DynamicArray *da) {
    if (da->size >= 0) {
        da->size--;
        return da->items[da->size];
    }
    return WRONG_POSITION;
}

int da_get(DynamicArray *da, int index) {
    if (0 <= index && index < da->size) {
        return da->items[index];
    }
    return WRONG_POSITION;
}

int da_set(DynamicArray *da, int index, int value) {
    if (0 <= index && index < da->size) {
        da->items[index] = value;
        return SUCCESS;
    }
    return WRONG_POSITION;
}
