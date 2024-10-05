#include <stdio.h>
#include "minunit.h"

#include "dynamic_array.h"

int tests_run = 0;

static char * test_dynamic_arrays() {
    DynamicArray *da = da_create();
    mu_assert("New size", da->size == 0);

    int D = da->capacity;
    mu_assert("New capacity", 8 == D);

    da_push(da, 69);
    da_push(da, 420);
    mu_assert("Four Twenty", da_pop(da) == 420);
    mu_assert("Sixty Nine", da_pop(da) == 69);
    

    da_destroy(da);
    return 0;
}

static char * test_all() {
    mu_run_test(test_dynamic_arrays);
    return 0;
}

int main() {
    char *result = test_all();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("All tests passed!\n");
    }

    printf("Tests run: %d\n", tests_run);
 
    return result != 0;
}
