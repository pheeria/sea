#include <stdio.h>
#include "minunit.h"

#include "dynamic_array.h"

int tests_run = 0;

static char * test_equality() {
    DynamicArray *da = da_create();
    mu_assert("New capacity", da->capacity == 8);
    return 0;
}

static char * test_all() {
    mu_run_test(test_equality);
    return 0;
}

int main() {
    char *result = test_all();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("All tests passed!");
    }

    printf("Tests run: %d\n", tests_run);
 
    return result != 0;
}
