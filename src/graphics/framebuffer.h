#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

typedef struct framebuffer_t {
	int width;
	int height;
	uint32_t *pixels;
} framebuffer_t;

void framebuffer_init(framebuffer_t *fb, int width, int height);
void framebuffer_resize(framebuffer_t *fb, int width, int height);
void framebuffer_destroy(framebuffer_t *fb);
void framebuffer_clear(framebuffer_t *fb, uint32_t color);
void framebuffer_draw_test_pattern(framebuffer_t *fb);
void framebuffer_rotate(framebuffer_t *fb, float angle_rad);
void framebuffer_shade(framebuffer_t *fb, uint32_t color);
void framebuffer_gaussian_blur(framebuffer_t *fb, float sigma);
void framebufffer_bilinear_filter(framebuffer_t *fb, float scale_x, float scale_y);
#endif
