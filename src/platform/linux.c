
#include "platform.h"
#include "../graphics/framebuffer.h"
#include "../graphics/soft_raster.h"
static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;
// Initialize framebuffer
framebuffer_t fb;
float direction = 0.0f;
bool platform_poll_events(void) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) return false;
		if (e.type == SDL_EVENT_KEY_DOWN) {
			if (e.key.scancode == SDL_SCANCODE_R) {
				direction += 1; /* pressed what would be "W" on a US QWERTY keyboard. Move forward! */
			}
			return true;
		}
		if (e.type == SDL_EVENT_WINDOW_RESIZED) {
			int new_width = e.window.data1;
			int new_height = e.window.data2;
			framebuffer_resize(&fb, new_width, new_height);
			SDL_SetWindowSize(window, new_width, new_height);
			surface = SDL_GetWindowSurface(window);
		}

		/* (We're writing our code such that it sees both keys are pressed and cancels each other out!) */
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
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
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
	SDL_Window *window = platform_init(1024, 1024, "Itzamna");
	if (!window) return 1;

	framebuffer_init(&fb, 1024, 1024); // allocates fb.pixels

	// Main loop
	float angle = 0.0f;
	uint8_t shade = 0;
	while (platform_poll_events()) {
		framebuffer_clear(&fb, 0xFF202020);

		framebuffer_draw_test_pattern(&fb);

		raster_draw_triangle_wire(&fb, 200.0f, 100.0f,
		                          400.0f, 300.0f,
		                          100.0f, 400.0f,
		                          0xFFFF0000); // Red triangle outline
		raster_draw_line(&fb, 500.0f, 100.0f,
		                 700.0f, 400.0f,
		                 0xFF00FF00); // Green line
		raster_draw_rect(&fb, 300, 300, 200, 150, 0xFF0000FF); // Blue rectangle
		raster_put_pixel(&fb, 512, 512, 0xFFFFFF00); // Yellow pixel in center
		raster_draw_circle(&fb, 800, 800, 50, 0xFFFF00FF); // Magenta circle
		raster_fill_circle(&fb, 200, 800, 40, 0xFF00FFFF); // Cyan filled circle
		//framebuffer_rotate(&fb, angle * 3.14159265f / 180.0f); // Rotate by 25 degrees
		//framebuffer_shade(&fb, 0xFFFFFF80 - (uint8_t)shade); // Apply shading
		platform_present(fb.pixels, fb.width, fb.height);
		angle += 0.2f; // rotate a little each frame

		shade += 1;
	}

	// Cleanup
	framebuffer_destroy(&fb);
	platform_shutdown();

	return 0;
}