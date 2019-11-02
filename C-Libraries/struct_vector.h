/**
 * struct vector (and others) for C
 * 
 * typedefs and macros:
 * item_length: Type of list length in vector.
 * item_type: Type of item held in vector.
 * 
 * Constants:
 * DEFAULT_VECTOR: Default vector.
 * 
 * Properties:
 * item_type *list: The list of item_types held in the vector.
 * item_length size: The size of list.
 * item_length length: The current length of occupied item_types in list.
 * bool allocated: True iff list has been dynamically allocated.
 * 
 * Functions:
 * void insertItem(vector *list, item_type item)
 * * Inserts item into list.
*/

#pragma once

#include <stdbool.h>
#include <string.h>

#define CHUNK 50
typedef int64_t item_length;
typedef int64_t item_type;
typedef struct vector {
    item_length size;
    item_length length;
    item_type *list;
    bool allocated;
} vector;
vector DEFAULT_VECTOR = { .size = 0, .length = 0, .list = NULL, .allocated = false };

void insertItem(vector *list, item_type item) {
    item_type *store;
    //If the list has no more space, allocate more space.
    if (list->length == list->size) {
        //store holds our old space
        store = list->list;
        //Increment size and allocate our new space.
        list->size += CHUNK;
        list->list = malloc(list->size*sizeof(item_type));
        //Transfer the old data over to the new space.
        memcpy(list->list, store, list->length*sizeof(item_type));
        //Free the old space if the old space was dynamically allocated.
        if (list->allocated) free(store);
        //Otherwise, mark allocated as true so we know the new space was allocated.
        else list->allocated = true;
    }
    //Insert item and increment list->length
    list->list[list->length++] = item;
}
#undef CHUNK