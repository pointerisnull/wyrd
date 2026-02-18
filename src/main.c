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
	
	
	Window win;
	init_window(&win, "Wyrd", DEFAULT_WIDTH, DEFAULT_HEIGHT);
	win.ecs = &engine.ecs;
	win.em = &event_manager;

	Event ev = new_event(E_ENTITY, E_SPAWN);
	queue_event(&event_manager, ev);
	engine.ecs.position[0] = (Vec3){200.0f, 0.0f, 200.0f};

	SDL_Event e;
	printf("Starting engine -> Tick: %ld\n", engine.tick);
	start_engine(&engine);
	while(engine_running(&engine)) {
		if(can_engine_tick(&engine)) {
			tick_engine(&engine);
		}
		draw_frame(&win);
	}
	
	uint64_t end_time = current_time_ms();
	printf("User position: (%.02f, %.02f, %.02f)\n", engine.ecs.position[0].x, engine.ecs.position[0].y, engine.ecs.position[0].z);	
	printf("Time ellipsed: %.02f seconds.\n", (float)(end_time - engine.start_time)/1000);
	printf("Engine shutting down after %ld ticks.\n", engine.tick);
	
	close_window(&win);
	
	return 0;
}
