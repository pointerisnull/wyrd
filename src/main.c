#include "primitives.h"
#include "ui/window.h"
#include <stdio.h>

#if defined(_WIN32)
  #include <SDL2/SDL.h>
#endif

int main(int argc, char **argv) {
  /*
  int count = 4;
  Vertex *verts = create_verticies(count);
  int positions[] = {3,4,5,1,2,3,9,8,7,11};
  populate_verticies(verts, count, positions);
  printf("Vertex Count: %d\n", count);
  printf("Vertex 3 position - x: %d y: %d \n", verts[2].x, verts[2].y);
  */
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
