/*
    * mat4.h
    * Source file for the 4x4 matrix operations.
    * 
    * Author: Highpn
*/

#include "mat4.h"
mat4_t mat4_identity(void) {
	mat4_t result = {0};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}
mat4_t mat4_multiply(mat4_t a, mat4_t b) {
	mat4_t result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return result;
}
mat4_t mat4_translate(float x, float y, float z) {
	mat4_t result = mat4_identity();
	result.m[3][0] = x;
	result.m[3][1] = y;
	result.m[3][2] = z;
	return result;
}
mat4_t mat4_scale(float x, float y, float z) {
	mat4_t result = mat4_identity();
	result.m[0][0] = x;
	result.m[1][1] = y;
	result.m[2][2] = z;
	return result;
}