/*
    * engine.h
    * Header file for the core engine functionalities.
    * 
    * Author: Highpn
*/

// Function prototype for engine_run
int engine_run(int argc, char *argv[]);
// Function prototype for config_load
void config_load(int argc, char *argv[]);
// Function prototypes for the initialization functions
void mixer_init(void);
void world_init(void);
void runtime_init(void);
void log_init(void);
void platform_init(void);
void timer_init(void);
void renderer_init(void);
void runtime_shutdown(void);
void world_shutdown(void);
void mixer_shutdown(void);
void renderer_shutdown(void);
void timer_shutdown(void);
void platform_shutdown(void);
void log_shutdown(void);
// Function prototypes for the engine loop functions
int engine_running(void);
void timer_update(void);
void poll_events(void);
void world_update(void);
int graphics_enabled(void);
void renderer_begin_frame(void);
void renderer_draw_world(void);
void renderer_end_frame(void);
void mixer_update(void);
