/*
    * mat4.h
    * Header file for the 4x4 matrix operations.
    * 
    * Author: Highpn
*/
#ifndef MAT4_H
#define MAT4_H
#include <stddef.h>
#include <stdint.h>
typedef struct {
	float m[4][4];
} mat4_t;
mat4_t mat4_identity(void);
mat4_t mat4_multiply(mat4_t a, mat4_t b);
mat4_t mat4_translate(float x, float y, float z);
mat4_t mat4_scale(float x, float y, float z);
mat4_t mat4_rotate_x(float angle_rad);
mat4_t mat4_rotate_y(float angle_rad);
mat4_t mat4_rotate_z(float angle_rad);
#endif // MAT4_H