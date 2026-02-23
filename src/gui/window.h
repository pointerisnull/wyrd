#ifndef WINDOW_H
#define WINDOW_H

#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "../ecs/ecs.h"
#include "../core/events.h"
#include "../core/engine.h"

typedef struct Window {
	SDL_Window *sdl_window;
	SDL_GLContext gl_context;

	Engine *engine;
	ECS *ecs;
	EventManager *em;

	int width; 
	int height;

	int mode;

	Event quit_event;
	Event forward_event;
	Event backward_event;
	Event left_event;
	Event right_event;
	Event look_left_event;
	Event look_right_event;
	Event jump_event;

} Window;

enum WindowMode {
	WM_2D,
	WM_3D,
	WM_MENU
};

bool init_window(Window *win, char *title, int width, int height);
void draw_frame(Window *win);
void close_window(Window *win);
#endif
