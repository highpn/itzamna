#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
	uint32_t *node; // vertex id
	double *key; // priority
	uint32_t size;
	uint32_t capacity;
} heap_t;

static inline heap_t *heap_create(uint32_t capacity) {
	heap_t *h = malloc(sizeof(heap_t));
	h->node = malloc(sizeof(uint32_t) * capacity);
	h->key = malloc(sizeof(double) * capacity);
	h->size = 0;
	h->capacity = capacity;
	return h;
}

static inline void heap_free(heap_t *h) {
	free(h->node);
	free(h->key);
	free(h);
}

static inline void heap_swap(heap_t *h, uint32_t i, uint32_t j) {
	uint32_t tn = h->node[i];
	double tk = h->key[i];
	h->node[i] = h->node[j];
	h->key[i] = h->key[j];
	h->node[j] = tn;
	h->key[j] = tk;
}

static inline void heap_push(heap_t *h, uint32_t node, double key) {
	uint32_t i = h->size++;
	h->node[i] = node;
	h->key[i] = key;

	while (i > 0) {
		uint32_t p = (i - 1) / 2;
		if (h->key[p] <= h->key[i])
			break;
		heap_swap(h, p, i);
		i = p;
	}
}

static inline int heap_empty(heap_t *h) {
	return h->size == 0;
}

static inline uint32_t heap_pop(heap_t *h, double *out_key) {
	uint32_t root_node = h->node[0];
	*out_key = h->key[0];

	h->size--;
	h->node[0] = h->node[h->size];
	h->key[0] = h->key[h->size];

	uint32_t i = 0;
	while (1) {
		uint32_t l = 2 * i + 1;
		uint32_t r = 2 * i + 2;
		uint32_t smallest = i;

		if (l < h->size && h->key[l] < h->key[smallest])
			smallest = l;
		if (r < h->size && h->key[r] < h->key[smallest])
			smallest = r;

		if (smallest == i)
			break;

		heap_swap(h, i, smallest);
		i = smallest;
	}

	return root_node;
}

#endif