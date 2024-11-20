#include <stdbool.h>

#define DICT_CAPACITY 16

typedef struct {
    char *key;
    void *value;
    bool used;
} Entry;

typedef struct {
    Entry *entries;
    int count;
    int capacity;
} Dict;


Dict *dict_create();
void dict_destroy(Dict *dict);
void *dict_get(Dict *dict, char *key);
void dict_set(Dict *dict, char *key, void *value);
void *dict_remove(Dict *dict, char *key);
