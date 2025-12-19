/*
    * vulkan_backend.h
    *
    * Vulkan backend implementation.
    * 
    * Author: Highpn
*/
// vulkan_render.h
#pragma once
#include "render_system.h"

RenderSystem *vulkan_render_create(int width, int height, const char *title);

bool vulkan_render_init(RenderSystem *rs);
void vulkan_render_present(RenderSystem *rs, uint32_t *pixels, int width, int height);
void vulkan_render_clear(RenderSystem *rs, uint32_t color);

void vulkan_render_resize(RenderSystem *rs, int width, int height);
void vulkan_render_poll_events(RenderSystem *rs, bool *running);

void vulkan_render_destroy(RenderSystem *rs);