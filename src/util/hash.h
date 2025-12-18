/*
    * hash.h
    *
    * Hash table implementation.
    * Author: Highpn
*/
#ifndef HASH_H
#define HASH_H
#include <stddef.h>
#include <stdint.h>

uint32_t hash_string(const char *str, size_t len);
#endif // HASH_H