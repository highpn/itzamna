/*
    * memory.h
    *
    * Memory management.
    * Author: Highpn
*/

#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string.h>
typedef struct {
	uint8_t *memory;
	size_t size;
	size_t offset;
} Arena;

void arena_init(Arena *arena, void *memory, size_t size);
void *arena_alloc(Arena *arena, size_t size, size_t alignment);
void arena_reset(Arena *arena);