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

#include "misc/file.h"

int main(int argc, char **argv) {
	World world = new_world();
	read_legacy_file(&world, "./wyd/indev.wyd");
	//write_file("./wyd/indev.wyd");
	
	EventManager event_manager;
	clear_manager(&event_manager);

	Engine engine = new_engine(40);
	engine.events = &event_manager;
	engine.world = &world;
	
	Window win;
	init_window(&win, "Wyrd", DEFAULT_WIDTH, DEFAULT_HEIGHT);
	win.engine = &engine;
	win.ecs = &engine.ecs;
	win.em = &event_manager;

	Event ev = new_event(E_ENTITY, E_SPAWN);
	ev.vec = (Vec3){25.0f, 0.0f, 25.0f};
	queue_event(&event_manager, ev);
	
	start_engine(&engine);
	while(engine_running(&engine)) {
		if(can_engine_tick(&engine)) {
			tick_engine(&engine);
		}
		draw_frame(&win);
	}
	
	uint64_t end_time = current_time_ms();
	printf("Time ellipsed: %.02f seconds.\n", (float)(end_time - engine.start_time)/1000);
	printf("Engine shutting down after %ld ticks.\n", engine.tick);
	
	close_window(&win);
	return 0;
}
