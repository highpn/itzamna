// platform.h
#ifndef PLATFORM_H
#define PLATFORM_H
#include <SDL3/SDL.h>
#include <stdint.h>

SDL_Window *platform_init(int width, int height, const char *title);
bool platform_poll_events(void);
void platform_present(uint32_t *pixels, int width, int height);
void platform_shutdown(void);
int platform_check(void);
#endif // PLATFORM_H