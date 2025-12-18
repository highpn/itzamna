
/*
    * trig.h
    * Source file for trigonometric functions.
    *
    * Author: Highpn
*/
#include "trig.h"
#include <stdint.h>

float fast_fabs(float x) {
	int32_t i = *(int32_t *)&x;
	i &= 0x7FFFFFFF;
	return *(float *)&i;
}
float fast_sin(float x) {
	// Wrap x to [-pi, pi]
	if (x < -PI)
		x += 2 * PI;
	else if (x > PI)
		x -= 2 * PI;

	const float B = 4.0f / PI;
	const float C = -4.0f / (PI * PI);
	float y = B * x + C * x * (x < 0 ? -x : x);

	// Optional: 0.225f factor for minimax correction
	const float P = 0.225f;
	return P * (y * (y < 0 ? -y : y) - y) + y;
}

float fast_cos(float x) {
	return fast_sin(x + PI_2);
}
float fast_tan(float x) {
	return fast_sin(x) / fast_cos(x);
}

float fast_asin(float x) {
	if (x < -1.0f)
		x = -1.0f;
	else if (x > 1.0f)
		x = 1.0f;
	float neg = x < 0 ? 1.0f : 0.0f;
	x = x < 0 ? -x : x;
	float ret = PI_2 - sqrtf(1.0f - x) * (1.5707288f + -0.2121144f * x + 0.0742610f * x * x - 0.0187293f * x * x * x);
	return neg ? -ret : ret;
}

float fast_acos(float x) {
	return PI_2 - fast_asin(x);
}

float fast_atan(float x) {
	return (PI / 4.0f) * x - x * (fast_fabs(x) - 1.0f) * (0.2447f + 0.0663f * fast_fabs(x));
}

float fast_atan2(float y, float x) {
	if (x == 0.0f) return y > 0.0f ? PI_2 : (y < 0.0f ? -PI_2 : 0.0f);
	float atan;
	float z = y / x;
	if (fast_fabs(z) < 1.0f) {
		atan = fast_atan(z);
		if (x < 0.0f) atan += (y >= 0.0f ? PI : -PI);
	} else {
		atan = PI_2 - fast_atan(1.0f / z);
		if (y < 0.0f) atan -= PI;
	}
	return atan;
}