#include "primitives.h"
#include "ui/window.h"
#include <stdio.h>

#if defined(_WIN32)
  #include <SDL2/SDL.h>
#endif

int main(int argc, char **argv) {

  //Start up SDL and create window
  Window *win = malloc(sizeof(Window));

  if(!init_window(win, "Wyrd"))
      printf("Failed to initialize!\n");
  else {
    //Load media
    if(!draw_frame(win)) { 
      printf("Failed to load media!\n");
    } else {
      //Apply the image
      SDL_BlitSurface(win->media_surface, NULL, win->root_surface, NULL );

	    SDL_UpdateWindowSurface(win->sdl_window);

      SDL_Event e; 
      bool quit = false; 
      while(quit == false) { 
        while(SDL_PollEvent(&e)) { 
          if(e.type == SDL_QUIT) 
            quit = true; 
        } 
      }
		}
  } 
  close_window(win);
  free(win);
  return 0;
}
