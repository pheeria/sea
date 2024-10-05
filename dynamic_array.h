#define SUCCESS 0
#define WRONG_POSITION 1

typedef struct {
    int capacity;
    int size;
    int *items;
} DynamicArray;


DynamicArray *da_create();
void da_destroy(DynamicArray *da);

int da_get(DynamicArray *da, int index);
int da_set(DynamicArray *da, int index, int value);

int da_push(DynamicArray *da, int value);
int da_pop(DynamicArray *da);
