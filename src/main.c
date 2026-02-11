#include "core/engine.h"
#include "core/primitives.h"
#include "core/flags.h"
#include "utils/utils.h"
#include "gui/window.h"
#include <stdio.h>

#if defined(_WIN32)
  #include <SDL2/SDL.h>
#endif

int main(int argc, char **argv) {
	uint64_t flags = 0;
	print_bitfield(flags);

	set_flag(&flags, 10);
	set_flag(&flags, 20);
	set_flag(&flags, 30);
	set_flag(&flags, 40);
	set_flag(&flags, 50);
	toggle_flag(&flags, 60);
	print_bitfield(flags);
	clear_flag(&flags, 50);
	toggle_flag(&flags, 60);
	print_bitfield(flags);
	toggle_flag(&flags, 60);
	print_bitfield(flags);

	/*
	Engine engine = new_engine(20);
	
	start_engine(&engine);
	
	while(engine_running(&engine)) {
		if(can_engine_tick(&engine)) {
			tick_engine(&engine);
		}
		if(engine.tick >= 80)
			kill_engine(&engine);
	}
	
	uint64_t end_time = current_time_ms();
	printf("Time ellipsed: %.02f ms.\n", (float)(end_time - engine.start_time)/1000);
	
	printf("Engine shutting down after %ld ticks.\n", engine.tick);
	*/
	return 0;
}
