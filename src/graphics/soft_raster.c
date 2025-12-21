#include "soft_raster.h"
void raster_solid_triangle(framebuffer_t *fb, float x0, float y0,
                           float x1, float y1,
                           float x2, float y2,
                           uint32_t color) {
	// Bounding box
	int minX = (int)fmaxf(0.0f, floorf(fminf(x0, fminf(x1, x2))));
	int maxX = (int)fminf(fb->width - 1.0f, ceilf(fmaxf(x0, fmaxf(x1, x2))));
	int minY = (int)fmaxf(0.0f, floorf(fminf(y0, fminf(y1, y2))));
	int maxY = (int)fminf(fb->height - 1.0f, ceilf(fmaxf(y0, fmaxf(y1, y2))));
	// Edge functions
	float area = (x1 - x0) * (y2 - y0) -

	             (x2 - x0) * (y1 - y0);
	if (area == 0.0f) return; // Degenerate triangle
	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			float w0 = (x1 - x0) * (y - y0) - (y1 - y0) * (x - x0);
			float w1 = (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1);
			float w2 = (x0 - x2) * (y - y2) - (y0 - y2) * (x - x2);
			if ((w0 >= 0 && w1 >= 0 && w2 >= 0) ||
			    (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
				fb->pixels[y * fb->width + x] = color;
			}
		}
	}
}
void raster_solid_rectangle(framebuffer_t *fb, float x, float y,
                            float width, float height,
                            uint32_t color) {
	int x0 = (int)fmaxf(0.0f, floorf(x));
	int y0 = (int)fmaxf(0.0f, floorf(y));
	int x1 = (int)fminf(fb->width - 1.0f, ceilf(x + width));
	int y1 = (int)fminf(fb->height - 1.0f, ceilf(y + height));

	for (int j = y0; j < y1; j++) {
		for (int i = x0; i < x1; i++) {
			fb->pixels[j * fb->width + i] = color;
		}
	}
}

raster_draw_triangle_wire(framebuffer_t *fb, float x0, float y0,
                          float x1, float y1,
                          float x2, float y2, uint32_t color) {
	// Bounding box
	int minX = (int)fmaxf(0.0f, floorf(fminf(x0, fminf(x1, x2))));
	int maxX = (int)fminf(fb->width - 1.0f, ceilf(fmaxf(x0, fmaxf(x1, x2))));
	int minY = (int)fmaxf(0.0f, floorf(fminf(y0, fminf(y1, y2))));
	int maxY = (int)fminf(fb->height - 1.0f, ceilf(fmaxf(y0, fmaxf(y1, y2))));
	// Edge functions
	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			float w0 = (x1 - x0) * (y - y0) - (y1 - y0) * (x - x0);
			float w1 = (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1);
			float w2 = (x0 - x2) * (y - y2) - (y0 - y2) * (x - x2);
			if (w0 == 0 || w1 == 0 || w2 == 0) {
				fb->pixels[y * fb->width + x] = color;
			}
		}
	}
}

void raster_draw_line(framebuffer_t *fb, float x0, float y0,
                      float x1, float y1,
                      uint32_t color) {
	int dx = (int)fabsf(x1 - x0);
	int dy = (int)fabsf(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	for (;;) {
		if (x0 >= 0 && x0 < fb->width && y0 >= 0 && y0 < fb->height) {
			fb->pixels[(int)y0 * fb->width + (int)x0] = color;
		}
		if ((int)x0 == (int)x1 && (int)y0 == (int)y1) break;
		int err2 = err * 2;
		if (err2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

raster_draw_rect(
        framebuffer_t *fb,
        int x, int y,
        int w, int h,
        uint32_t color) {
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			if (i >= 0 && i < fb->width && j >= 0 && j < fb->height) {
				if (j == y || j == y + h - 1 || i == x || i == x + w - 1)
					fb->pixels[j * fb->width + i] = color;
			}
		}
	}
}

raster_put_pixel(framebuffer_t *fb, int x, int y, uint32_t color) {
	if (x >= 0 && x < fb->width && y >= 0 && y < fb->height) {
		fb->pixels[y * fb->width + x] = color;
	}
}

raster_draw_circle(framebuffer_t *fb, int cx, int cy, int radius, uint32_t color) {
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;
	while (x <= y) {
		raster_put_pixel(fb, cx + x, cy + y, color);
		raster_put_pixel(fb, cx - x, cy + y, color);
		raster_put_pixel(fb, cx + x, cy - y, color);
		raster_put_pixel(fb, cx - x, cy - y, color);
		raster_put_pixel(fb, cx + y, cy + x, color);
		raster_put_pixel(fb, cx - y, cy + x, color);
		raster_put_pixel(fb, cx + y, cy - x, color);
		raster_put_pixel(fb, cx - y, cy - x, color);
		if (d < 0) {
			d += 4 * x + 6;
		} else {
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}
void raster_fill_circle(
        framebuffer_t *fb,
        int cx, int cy,
        int radius,
        uint32_t color) {
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;
	while (x <= y) {
		for (int i = cx - x; i <= cx + x; i++) {
			raster_put_pixel(fb, i, cy + y, color);
			raster_put_pixel(fb, i, cy - y, color);
		}
		for (int i = cx - y; i <= cx + y; i++) {
			raster_put_pixel(fb, i, cy + x, color);
			raster_put_pixel(fb, i, cy - x, color);
		}
		if (d < 0) {
			d += 4 * x + 6;
		} else {
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}