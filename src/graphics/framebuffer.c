#include "framebuffer.h"
#include "../math/trig.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Initialize framebuffer: allocate memory for pixels
void framebuffer_init(framebuffer_t *fb, int width, int height) {
	fb->width = width;
	fb->height = height;
	fb->pixels = (uint32_t *)malloc(width * height * sizeof(uint32_t));
}
void framebuffer_resize(framebuffer_t *fb, int width, int height) {
	if (fb->pixels) free(fb->pixels);
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

	float cos_a = fast_cos(angle_rad);
	float sin_a = fast_sin(angle_rad);

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
		uint8_t r1 = (fb->pixels[i] >> 16) & 0xFF;
		uint8_t g1 = (fb->pixels[i] >> 8) & 0xFF;
		uint8_t b1 = fb->pixels[i] & 0xFF;

		uint8_t r2 = (color >> 16) & 0xFF;
		uint8_t g2 = (color >> 8) & 0xFF;
		uint8_t b2 = color & 0xFF;

		uint8_t r = (r1 * r2) / 255;
		uint8_t g = (g1 * g2) / 255;
		uint8_t b = (b1 * b2) / 255;

		fb->pixels[i] = (0xFF << 24) | (r << 16) | (g << 8) | b;
	}
}

void framebuffer_gaussian_blur(framebuffer_t *fb, float sigma) {
	int w = fb->width;
	int h = fb->height;
	int radius = (int)(sigma * 3.0f);
	int size = radius * 2 + 1;

	// Create Gaussian kernel
	float *kernel = (float *)malloc(size * sizeof(float));
	float sum = 0.0f;
	for (int i = -radius; i <= radius; i++) {
		kernel[i + radius] = expf(-(i * i) / (2 * sigma * sigma));
		sum += kernel[i + radius];
	}
	for (int i = 0; i < size; i++) {
		kernel[i] /= sum;
	}

	// Temporary buffer
	uint32_t *tmp = (uint32_t *)malloc(w * h * sizeof(uint32_t));

	// Horizontal pass
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			float r = 0, g = 0, b = 0;
			for (int k = -radius; k <= radius; k++) {
				int sx = fminf(fmaxf(x + k, 0), w - 1);
				uint32_t pixel = fb->pixels[y * w + sx];
				float weight = kernel[k + radius];
				r += ((pixel >> 16) & 0xFF) * weight;
				g += ((pixel >> 8) & 0xFF) * weight;
				b += (pixel & 0xFF) * weight;
			}
			tmp[y * w + x] =
			        (0xFF << 24) | ((uint8_t)r << 16) | ((uint8_t)g << 8) | (uint8_t)b;
		}
	}

	// Vertical pass
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			float r = 0, g = 0, b = 0;
			for (int k = -radius; k <= radius; k++) {
				int sy = fminf(fmaxf(y + k, 0), h - 1);
				uint32_t pixel = tmp[sy * w + x];
				float weight = kernel[k + radius];
				r += ((pixel >> 16) & 0xFF) * weight;
				g += ((pixel >> 8) & 0xFF) * weight;
				b += (pixel & 0xFF) * weight;
			}
			fb->pixels[y * w + x] =
			        (0xFF << 24) | ((uint8_t)r << 16) | ((uint8_t)g << 8) | (uint8_t)b;
		}
	}
	free(kernel);
	free(tmp);
}

framebufffer_bilinear_filter(framebuffer_t *fb, float scale_x, float scale_y) {
	int new_width = (int)(fb->width * scale_x);
	int new_height = (int)(fb->height * scale_y);
	uint32_t *new_pixels = (uint32_t *)malloc(new_width * new_height * sizeof(uint32_t));
	if (!new_pixels) return;

	for (int y = 0; y < new_height; y++) {
		for (int x = 0; x < new_width; x++) {
			float src_x = x / scale_x;
			float src_y = y / scale_y;
			int x0 = (int)src_x;
			int y0 = (int)src_y;
			int x1 = fminf(x0 + 1, fb->width - 1);
			int y1 = fminf(y0 + 1, fb->height - 1);
			float dx = src_x - x0;
			float dy = src_y - y0;

			uint32_t c00 = fb->pixels[y0 * fb->width + x0];
			uint32_t c10 = fb->pixels[y0 * fb->width + x1];
			uint32_t c01 = fb->pixels[y1 * fb->width + x0];
			uint32_t c11 = fb->pixels[y1 * fb->width + x1];

			// Interpolate
			uint8_t r = (uint8_t)(((1 - dx) * (1 - dy) * ((c00 >> 16) & 0xFF)) +
			                      (dx * (1 - dy) * ((c10 >> 16) & 0xFF)) +
			                      ((1 - dx) * dy * ((c01 >> 16) & 0xFF)) +
			                      (dx * dy * ((c11 >> 16) & 0xFF)));
			uint8_t g = (uint8_t)(((1 - dx) * (1 - dy) * ((c00 >> 8) & 0xFF)) +
			                      (dx * (1 - dy) * ((c10 >> 8) & 0xFF)) +
			                      ((1 - dx) * dy * ((c01 >> 8) & 0xFF)) +
			                      (dx * dy * ((c11 >> 8) & 0xFF)));
			uint8_t b = (uint8_t)(((1 - dx) * (1 - dy) * (c00 & 0xFF)) +
			                      (dx * (1 - dy) * (c10 & 0xFF)) +
			                      ((1 - dx) * dy * (c01 & 0xFF)) +
			                      (dx * dy * (c11 & 0xFF)));
			new_pixels[y * new_width + x] = (0xFF << 24) | (r << 16) | (g << 8) | b;
		}
	}
	free(fb->pixels);
	fb->pixels = new_pixels;
	fb->width = new_width;
	fb->height = new_height;
}
