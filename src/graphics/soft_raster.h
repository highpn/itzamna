#include <stdint.h>
#include "framebuffer.h"
#ifndef SOFT_RASTER_H
#define SOFT_RASTER_H
void raster_solid_triangle(framebuffer_t *fb, float x0, float y0,
                           float x1, float y1,
                           float x2, float y2,
                           uint32_t color);
void raster_draw_rect(
        framebuffer_t *fb,
        int x, int y,
        int w, int h,
        uint32_t color);
void raster_solid_rectangle(framebuffer_t *fb, float x, float y,
                            float width, float height,
                            uint32_t color);
void raster_draw_triangle_wire(framebuffer_t *fb, float x0, float y0,
                               float x1, float y1,
                               float x2, float y2, uint32_t color);
void raster_draw_line(framebuffer_t *fb, float x0, float y0,
                      float x1, float y1,
                      uint32_t color);
void raster_put_pixel(framebuffer_t *fb, int x, int y, uint32_t color);
void raster_draw_circle(
        framebuffer_t *fb,
        int cx, int cy,
        int radius,
        uint32_t color);
void raster_fill_circle(
        framebuffer_t *fb,
        int cx, int cy,
        int radius,
        uint32_t color);
#endif