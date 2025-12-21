#include "zbuffer.h"
#include <stdlib.h>

void zbuffer_init(zbuffer_t *zb, framebuffer_t *fb, int width, int height) {
	zb->width = width;
	zb->height = height;
	zb->depths = (float *)malloc(width * height * sizeof(float));
}
void zbuffer_resize(zbuffer_t *zb, int width, int height) {
	zb->width = width;
	zb->height = height;
	zb->depths = (float *)realloc(zb->depths, width * height * sizeof(float));
}
void zbuffer_clear(zbuffer_t *zb, float depth) {
	for (int i = 0; i < zb->width * zb->height; i++) {
		zb->depths[i] = depth;
	}
}
void zbuffer_destroy(zbuffer_t *zb) {
	if (zb->depths) free(zb->depths);
	zb->depths = NULL;
}