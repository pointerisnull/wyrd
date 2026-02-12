#include "core/engine.h"
#include "core/primitives.h"
#include "core/bitset.h"
#include "utils/utils.h"
#include "gui/window.h"
#include <stdio.h>

#if defined(_WIN32)
  #include <SDL2/SDL.h>
#endif

int main(int argc, char **argv) {
	Engine engine = new_engine(20);
	
	start_engine(&engine);
	
	Window win;
	init_window(&win, "Wyrd", DEFAULT_WIDTH, DEFAULT_HEIGHT);
	SDL_Event e;

	while(engine_running(&engine)) {
		if(can_engine_tick(&engine)) {
			tick_engine(&engine);
		}
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				kill_engine(&engine);
		}
		draw_frame(&win);
	}

	close_window(&win);
	
	uint64_t end_time = current_time_ms();
	
	printf("Time ellipsed: %.02f ms.\n", (float)(end_time - engine.start_time)/1000);
	printf("Engine shutting down after %ld ticks.\n", engine.tick);
	
	return 0;
}
