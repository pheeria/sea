typedef struct {
    int capacity;
    int size;
    int *items;
} DynamicArray;


DynamicArray *da_create();
void da_destroy(DynamicArray *da);

int da_get(int index);
void da_set(int index, int value);
