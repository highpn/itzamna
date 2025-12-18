/*
    * memory.c
    *
    * Source file for memory management.
    * Author: Highpn
*/
#include "memory.h"

void arena_init(Arena *arena, void *memory, size_t size) {
	arena->memory = (uint8_t *)memory;
	arena->size = size;
	arena->offset = 0;
}

void *arena_alloc(Arena *arena, size_t size, size_t alignment) {
	size_t current = (size_t)(arena->memory + arena->offset);
	size_t aligned = (current + (alignment - 1)) & ~(alignment - 1);
	size_t new_offset = aligned - (size_t)arena->memory + size;

	if (new_offset > arena->size) return NULL; // Out of memory
	void *ptr = arena->memory + (aligned - (size_t)arena->memory);
	arena->offset = new_offset;
	return ptr;
}

void arena_reset(Arena *arena) {
	arena->offset = 0;
}