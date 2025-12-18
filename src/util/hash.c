
/*
    * hash.c
    *
    * Hash table implementation.
    * Author: Highpn
*/
#include "hash.h"

uint32_t hash_string(const char *str, size_t len) {
	uint32_t hash = 2166136261u;
	for (size_t i = 0; i < len; i++) {
		hash ^= (uint8_t)str[i];
		hash *= 16777619u;
	}
	return hash;
}
