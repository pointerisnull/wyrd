#include "window.h"

bool init_window(Window *win, char *title) {
  if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  } else {
    win->sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN);
    if(win->sdl_window == NULL ) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return false;
    } else {
      win->root_surface = SDL_GetWindowSurface(win->sdl_window);
    }
  }

  return true;
}

bool draw_frame(Window *win) {
  char *path = "./res/years.bmp";
  //test load image
  win->media_surface = SDL_LoadBMP(path);
  if(win->media_surface == NULL ) {
    printf("Unable to load image %s! SDL Error: %s\n", "", SDL_GetError() );
    return false;
  }
  return true;
}

void close_window(Window *win) {
  SDL_FreeSurface(win->media_surface);
  win->media_surface = NULL;
  
  SDL_DestroyWindow(win->sdl_window);
  win->sdl_window = NULL;

  SDL_Quit();
}
