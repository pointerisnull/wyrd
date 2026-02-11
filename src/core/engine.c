#include "engine.h"
#include "../utils/utils.h"

#include <stdbool.h>
#include <sys/time.h>
#include <stdio.h>

Engine new_engine(int rate) {
	Engine e;
	e.tick = 0;
	e.tickrate = rate;
	e.tick_delta = 1000/rate;
	
	e.start_time = current_time_ms();
	e.last_tick_time = e.start_time;
	
	e.headless = true;
	e.is_running = false;
	e.paused = false;
	
	return e;
}

void start_engine(Engine *e) {
	e->is_running = true;
}

bool can_engine_tick(Engine *e) {
	uint64_t current_time = current_time_ms();
	//printf("\nCurrent:\t%d\nlast:\t\t%d\npassed:\t\t%d\n", current_time, e->last_tick_time, (uint64_t)(e->last_tick_time + e->tick_delta));
	if(current_time >= (uint64_t)(e->last_tick_time + e->tick_delta))
		return true;
	return false;
}

bool engine_running(Engine *e) {
	if(e->is_running && !e->paused)
		return true;
	return false;
}

bool engine_alive(Engine *e) {
	if(e->is_running)
		return true;
	return false;
}

void tick_engine(Engine *e) {
	e->tick += 1;
	e->last_tick_time = current_time_ms();
}

void stop_engine(Engine *e) {
	e->paused = true;
}

void kill_engine(Engine *e) {
	e->is_running = false;
}
