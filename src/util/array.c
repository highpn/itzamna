
/*
    * array.c
    *
    * Dynamic array implementation.
    * Author: Highpn
*/
#include "array.h"

void array_init(Array *array, size_t element_size) {
	array->data = NULL;
	array->element_size = element_size;
	array->capacity = 0;
	array->count = 0;
}

void array_push(Array *array, void *item) {

	if (array->count >= array->capacity) {
		if (array->capacity == 0)
			array->capacity = ARRAY_INIT_CAPACITY;
		array->capacity *= 2;
		array->data = realloc(array->data, array->element_size * array->capacity);
	}
	memcpy((uint8_t *)array->data + (array->element_size * array->count), item, array->element_size);
	array->count++;
}
void *array_pop(Array *array) {
	if (array->count == 0) {
		return NULL;
	}
	array->data = realloc(array->data, array->element_size * --array->count);
	return array->data;
}

void array_free(Array *array) {
	free(array->data);
	array->data = NULL;
	array->count = array->capacity = 0;
}

void *array_get(Array *array, size_t index) {
	if (index >= array->count) return NULL;
	return (char *)array->data + index * array->element_size;
}