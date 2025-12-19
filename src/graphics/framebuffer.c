#include "framebuffer.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Initialize framebuffer: allocate memory for pixels
void framebuffer_init(framebuffer_t *fb, int width, int height) {
	fb->width = width;
	fb->height = height;
	fb->pixels = (uint32_t *)malloc(width * height * sizeof(uint32_t));
}

// Free framebuffer memory
void framebuffer_destroy(framebuffer_t *fb) {
	if (fb->pixels) free(fb->pixels);
	fb->pixels = NULL;
}

// Clear framebuffer with a single color
void framebuffer_clear(framebuffer_t *fb, uint32_t color) {
	for (int i = 0; i < fb->width * fb->height; i++) {
		fb->pixels[i] = color;
	}
}

// Draw a simple checkerboard / test pattern
void framebuffer_draw_test_pattern(framebuffer_t *fb) {
	for (int y = 0; y < fb->height; y++) {
		for (int x = 0; x < fb->width; x++) {
			fb->pixels[y * fb->width + x] =
			        ((x ^ y) & 0xFF) | 0xFF000000; // checkerboard
		}
	}
}

void framebuffer_rotate(framebuffer_t *fb, float angle_rad) {
	int w = fb->width;
	int h = fb->height;

	// Create a temporary buffer to store rotated pixels
	uint32_t *tmp = malloc(sizeof(uint32_t) * w * h);
	if (!tmp) return;

	int cx = w / 2;
	int cy = h / 2;

	float cos_a = cosf(angle_rad);
	float sin_a = sinf(angle_rad);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// Translate pixel to center
			int tx = x - cx;
			int ty = y - cy;

			// Rotate
			int rx = (int)(tx * cos_a - ty * sin_a);
			int ry = (int)(tx * sin_a + ty * cos_a);

			// Translate back
			rx += cx;
			ry += cy;

			// Check bounds
			if (rx >= 0 && rx < w && ry >= 0 && ry < h) {
				tmp[y * w + x] = fb->pixels[ry * w + rx];
			} else {
				tmp[y * w + x] = 0xFF202020; // background color
			}
		}
	}

	// Copy rotated pixels back to framebuffer
	memcpy(fb->pixels, tmp, sizeof(uint32_t) * w * h);
	free(tmp);
}

void framebuffer_shade(framebuffer_t *fb, uint32_t color) {
	for (int i = 0; i < fb->width * fb->height; i++) {
		fb->pixels[i] &= color + i % fb->width; // simple shading effect
	}
}