
/*
    * array.h
    *
    * Dynamic array implementation.
    * Author: Highpn
*/

#if !defined(ARRAY_H)
#define ARRAY_H

#define ARRAY_INIT_CAPACITY 8
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void *data;
	size_t element_size;
	size_t count;
	size_t capacity;
} Array;

void array_init(Array *array, size_t element_size);
void array_push(Array *array, void *item);
void *array_pop(Array *array);
void array_free(Array *array);
void *array_get(Array *arr, size_t index);
#endif // ARRAY_H