#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

Dict *dict_create() {
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        fprintf(stderr, "ERROR: Initial malloc failed\n");
        exit(1);
    }

    dict->capacity = DICT_CAPACITY;
    dict->count = 0;
    dict->entries = calloc(dict->capacity, sizeof(Entry));
    if (dict->entries == NULL) {
        fprintf(stderr, "ERROR: Initial calloc for entries failed\n");
        exit(1);
    }

    return dict;
}

void dict_destroy(Dict *dict) {
    free(dict->entries);
    dict->capacity = 0;
    dict->count = 0;
    free(dict);
}

unsigned long hash(char *key) {
    unsigned long result = 5381;
    
    for (int i = 0; key[i] != '\0'; i++) {
        result = 33 * result + key[i];
    }

    return result;
}

void *dict_get(Dict *dict, char *key) {
    int index = hash(key) % dict->capacity;

    while (dict->entries[index].used) {
        if (strcmp(dict->entries[index].key, key) == 0) {
            return dict->entries[index].value;
        }
        index = (index + 1) % dict->capacity;
    }
    return NULL;
}

void dict_set(Dict *dict, char *key, void *value) {
    if (dict->count == dict->capacity) {
        Entry *old_entries = dict->entries;
        int old_capacity = dict->capacity;

        dict->capacity *= 2;
        dict->entries = calloc(dict->capacity, sizeof(Entry));
        if (dict->entries == NULL) {
            fprintf(stderr, "ERROR: Resize calloc for entries failed\n");
            exit(1);
        }

        int found = 0;
        for (int i = 0; i < old_capacity; i++) {
            if (old_entries[i].used) {
                int index = hash(old_entries[i].key) % dict->capacity;
                while (dict->entries[index].used) {
                    index = (index + 1) % dict->capacity;
                }
                dict->entries[index] = old_entries[i];
                found++;
            }
            if (found == dict->count) {
                break;
            }
        }
        free(old_entries);
    }
    int index = hash(key) % dict->capacity;
    while (dict->entries[index].used) {
        index = (index + 1) % dict->capacity;
    }
    dict->entries[index] = (Entry) {
        .key = strdup(key),
        .value = value,
        .used = true,
    };
    dict->count++;
}

void *dict_remove(Dict *dict, char *key) {
    int index = hash(key) % dict->capacity;
    while (dict->entries[index].used) {
        if (strcmp(dict->entries[index].key, key) == 0) {
            void *value = dict->entries[index].value;
            free(dict->entries[index].key);
            dict->entries[index].used = false;
            dict->count--;

            // Rehash subsequent keys
            int next = (index + 1) % dict->capacity;
            while (dict->entries[next].used) {
                Entry temp = dict->entries[next];
                dict->entries[next].used = false;
                dict->count--;
                dict_set(dict, temp.key, temp.value);
                next = (next + 1) % dict->capacity;
            }
            return value;
        }
        index = (index + 1) % dict->capacity;
    }
    return NULL;
}

void dict_print(Dict *dict) {
    printf("{\n");
    int found = 0;
    for (int i = 0; i < dict->capacity; i++) {
        if (dict->entries[i].used) {
            printf("    \"%s\": \"%s\",\n", dict->entries[i].key, (char *) dict->entries[i].value);
            found++;
        }
        if (found == dict->count) {
            break;
        }
    }
    printf("}\n");
}

void dict_dump(Dict *dict) {
    printf("Dict COUNT: %d, CAPACITY: %d\n\n", dict->count, dict->capacity);
    for (int i = 0; i < dict->capacity; i++) {
        if (dict->entries[i].used) {
            printf("[%2d]  Key: \"%s\", Value: \"%s\"\n", i, dict->entries[i].key, (char *) dict->entries[i].value);
        } else {
            printf("[%2d]  FREE\n", i);
        }
    }
    printf("\n");
}

