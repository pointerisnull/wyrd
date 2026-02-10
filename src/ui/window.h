#ifndef WINDOW_H
#define WINDOW_H

#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600

#include <stdbool.h>

#include <SDL2/SDL.h>

typedef struct Window {
  SDL_Window *sdl_window;
  SDL_Surface *root_surface;
  SDL_Surface *media_surface;
} Window;

bool init_window(Window *win, char *title);
bool draw_frame(Window *win);
void close_window(Window *win);
#endif
