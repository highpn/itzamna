// opengl_render.h
#pragma once
#include "render_system.h"

RenderSystem *opengl_render_create(int width, int height, const char *title);

bool opengl_render_init(RenderSystem *rs);
void opengl_render_present(RenderSystem *rs, uint32_t *pixels, int width, int height);
void opengl_render_clear(RenderSystem *rs, uint32_t color);

void opengl_render_resize(RenderSystem *rs, int width, int height);
void opengl_render_poll_events(RenderSystem *rs, bool *running);

void opengl_render_destroy(RenderSystem *rs);