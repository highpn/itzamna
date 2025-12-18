/*
    * vec3.h
    *
    * Header file for 3D vector operations.
*/
#ifndef VEC3_H
#define VEC3_H

typedef struct {
	float x;
	float y;
	float z;
} vec3_t;

// Function prototypes for vector operations
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
vec3_t vec3_scale(vec3_t v, float scalar);
float vec3_dot(vec3_t a, vec3_t b);
vec3_t vec3_cross(vec3_t a, vec3_t b);
float vec3_inv_length(vec3_t v);
vec3_t vec3_normalize(vec3_t v);
#endif // VEC3_H
