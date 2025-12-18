/*
    * trig.h
    * Header file for trigonometric functions.
    * 
    * Author: Highpn
*/
// Constants
#define PI 3.14159265358979323846f
#define PI_2 1.57079632679489661923f
#define INV_PI 0.31830988618379067154f
#ifndef TRIG_H
#define TRIG_H
float fast_fabs(float x);
float fast_sin(float angle_rad);
float fast_cos(float angle_rad);
float fast_tan(float angle_rad);
float fast_asin(float value);
float fast_acos(float value);
float fast_atan(float value);
float fast_atan2(float y, float x);
#endif // TRIG_H