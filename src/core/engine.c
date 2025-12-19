/*
    * engine.c
    *
    * Core engine implementation.
    * Author: Highpn
*/

#include "engine.h"
#include "../platform/platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int engine_is_running = 1;
static int graphics_mode = 1;

int main(int argc, char *argv[]) {
	int d = platform_check();
	if (d != 0) {
		printf("Platform check failed with code %d\n", d);
		exit(0);
	}
	exit(0);
	return engine_run(argc, argv);
}

int engine_run(int argc, char *argv[]) {
	if (argc < 1 || argv == NULL) {
		fprintf(stderr, "Invalid arguments \n");
		return -1;
	}

	log_init();
	config_load(argc, argv);
	platform_init(640, 480, "Itzamna");
	timer_init();

	if (argc > 1 && strcmp(argv[1], "--nogfx") == 0) {
		printf("Running in no graphics mode.\n");
	} else {
		printf("Running with graphics mode.\n");
		renderer_init();
	}
	mixer_init();
	world_init();
	runtime_init();
	while (engine_running()) {
		// Main engine loop
		timer_update();
		poll_events();
		world_update();
		if (graphics_enabled()) {
			renderer_begin_frame();
			renderer_draw_world();
			renderer_end_frame();
		}
		mixer_update();
	}
	runtime_shutdown();
	world_shutdown();
	mixer_shutdown();
	if (graphics_enabled()) {
		renderer_shutdown();
	}
	timer_shutdown();
	platform_shutdown();
	log_shutdown();
	// Engine implementation goes here
	printf("Engine is running with %d arguments.\n", argc);
	return 0;
}

// Function prototype for config_load
void config_load(int argc, char *argv[]) {
	// Implementation for loading configuration
}
// Function prototypes for the initialization functions
void mixer_init(void) {
	// Implementation for mixer initialization
}
void world_init(void) {
	// Implementation for world initialization
}
void runtime_init(void) {
	// Implementation for runtime initialization
}
void log_init(void) {
	// Implementation for log initialization
}
void timer_init(void) {
	// Implementation for timer initialization
}
void renderer_init(void) {
	// Implementation for renderer initialization
}
void runtime_shutdown(void) {
	// Implementation for runtime shutdown
}
void world_shutdown(void) {
	// Implementation for world shutdown
}
void mixer_shutdown(void) {
	// Implementation for mixer shutdown
}
void renderer_shutdown(void) {
	// Implementation for renderer shutdown
}
void timer_shutdown(void) {
	// Implementation for timer shutdown
}

void log_shutdown(void) {
	// Implementation for log shutdown
}
// Function prototypes for the engine loop functions
int engine_running(void) {
	// Implementation to check if engine is running

	return engine_is_running;
}
void timer_update(void) {
	// Implementation for timer update
}
void poll_events(void) {
	// Implementation for polling events
}
void world_update(void) {
	// Implementation for world update
}
int graphics_enabled(void) {
	// Implementation to check if graphics is enabled
	return graphics_mode; // Placeholder
}
void renderer_begin_frame(void) {
	// Implementation for beginning the renderer frame
}
void renderer_draw_world(void) {
	// Implementation for drawing the world
}
void renderer_end_frame(void) {
	// Implementation for ending the renderer frame
}
void mixer_update(void) {
	// Implementation for mixer update
}
