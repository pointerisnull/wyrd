#include "core/engine.h"
#include "core/events.h"
#include "misc/bitset.h"
#include "misc/utils.h"
#include "misc/input_map.h"
#include "gui/window.h"
#include <stdio.h>

#if defined(_WIN32)
  #include <SDL2/SDL.h>
#endif

int main(int argc, char **argv) {
	
	EventManager event_manager;
	clear_manager(&event_manager);

	Engine engine = new_engine(20);
	engine.events = &event_manager;
	start_engine(&engine);
	
	Window win;
	init_window(&win, "Wyrd", DEFAULT_WIDTH, DEFAULT_HEIGHT);
	SDL_Event e;

	while(engine_running(&engine)) {
		if(can_engine_tick(&engine)) {
			tick_engine(&engine);
				if (engine.tick % 10 == 0) {
					Event new = new_event(E_INPUT, RELEASE);
					queue_event(&event_manager, new);
					Event newer = new_event(E_INPUT, JUMP);
					queue_event(&event_manager, newer);
					new = new_event(E_INPUT, 2);
					queue_event(&event_manager, new);
					new = new_event(E_INPUT, 2);
					queue_event(&event_manager, new);
					new = new_event(E_INPUT, 16);
					queue_event(&event_manager, new);
					print_queue(&event_manager);
				}
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
