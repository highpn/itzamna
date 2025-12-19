// render_system.h
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct RenderSystem RenderSystem;

RenderSystem *render_system_create(int width, int height, const char *title);
void render_system_destroy(RenderSystem *rs);

bool render_system_init(RenderSystem *rs);
void render_system_present(RenderSystem *rs, uint32_t *pixels, int width, int height);
void render_system_clear(RenderSystem *rs, uint32_t color);

void render_system_resize(RenderSystem *rs, int width, int height);
void render_system_poll_events(RenderSystem *rs, bool *running);