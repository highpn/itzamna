
#include "platform.h"
#include "../graphics/framebuffer.h"
static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;

bool platform_poll_events(void) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) return false;
		if (e.type == SDL_EVENT_KEY_DOWN) {
			return true;
		}
	}
	return true;
}

void platform_present(uint32_t *pixels, int width, int height) {
	SDL_LockSurface(surface);
	for (int y = 0; y < height; y++) {
		memcpy((uint8_t *)surface->pixels + y * surface->pitch,
		       pixels + y * width,
		       width * sizeof(uint32_t));
	}
	SDL_UnlockSurface(surface);
	SDL_UpdateWindowSurface(window);
}

void platform_shutdown(void) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Window *platform_init(int width, int height, const char *title) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return NULL;
	}

	window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
	if (!window) return NULL;

	surface = SDL_GetWindowSurface(window);
	if (!surface) return NULL;

	return window;
}
int platform_check(void) {
	// Initialize SDL and create window
	SDL_Window *window = platform_init(640, 640, "Itzamna");
	if (!window) return 1;

	// Initialize framebuffer
	framebuffer_t fb;
	framebuffer_init(&fb, 640, 480); // allocates fb.pixels

	// Main loop
	float angle = 0.0f;
	uint8_t shade = 0;
	while (platform_poll_events()) {
		framebuffer_clear(&fb, 0xFF202020);

		framebuffer_draw_test_pattern(&fb);
		framebuffer_rotate(&fb, angle * 3.14159265f / 180.0f); // Rotate by 25 degrees
		framebuffer_shade(&fb, 0xFFFFFF80 - (uint8_t)--shade); // Apply shading
		platform_present(fb.pixels, fb.width, fb.height);
		angle += 0.02f; // rotate a little each frame
	}

	// Cleanup
	framebuffer_destroy(&fb);
	platform_shutdown();

	return 0;
}