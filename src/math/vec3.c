/*
    * vec3.c
    *
    * Implementation of 3D vector operations.
	* Author: Highpn
*/

#include "vec3.h"

vec3_t vec3_add(vec3_t a, vec3_t b) {
	vec3_t result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
	vec3_t result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

vec3_t vec3_scale(vec3_t v, float scalar) {
	vec3_t result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

float vec3_dot(vec3_t a, vec3_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
vec3_t vec3_cross(vec3_t a, vec3_t b) {
	vec3_t result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}
static inline float fast_rsqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int *)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float *)&i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}
float vec3_inv_length(vec3_t v) {

	return fast_rsqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3_normalize(vec3_t v) {
	if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f) {
		vec3_t zero = {0.0f, 0.0f, 0.0f};
		return zero; // Return zero vector if length is zero
	}
	return vec3_scale(v, fast_rsqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
