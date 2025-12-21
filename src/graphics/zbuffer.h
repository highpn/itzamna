#include "framebuffer.h"
#ifndef ZBUFFER_H
#define ZBUFFER_H

typedef struct zbuffer_t {
	int width;
	int height;
	float *depths;
} zbuffer_t;

void zbuffer_init(zbuffer_t *zb, framebuffer_t *fb, int width, int height);
void zbuffer_clear(zbuffer_t *zb, float depth);
void zbuffer_destroy(zbuffer_t *zb);

#endif