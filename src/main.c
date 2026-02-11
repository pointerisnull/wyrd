#include "core/engine.h"
#include "core/primitives.h"
#include "utils/utils.h"
#include "gui/window.h"
#include <stdio.h>

#if defined(_WIN32)
  #include <SDL2/SDL.h>
#endif

int main(int argc, char **argv) {
<<<<<<< HEAD
	Engine engine = new_engine(20);
	
	start_engine(&engine);
	
	while(engine_running(&engine)) {
		if(can_engine_tick(&engine)) {
			tick_engine(&engine);
=======

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
>>>>>>> d5918e97530101c94760354d82c4ab1e2ec4a8c8
		}
		if(engine.tick >= 80)
			kill_engine(&engine);
	}
	
	uint64_t end_time = current_time_ms();
	printf("Time ellipsed: %.02f ms.\n", (float)(end_time - engine.start_time)/1000);
	
	printf("Engine shutting down after %ld ticks.\n", engine.tick);
	
	return 0;
}
