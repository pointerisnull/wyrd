#include "engine.h"
#include "events.h"
#include "../misc/utils.h"

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

	e.input = 0;
	e.flags = 0;
	
	return e;
}

void start_engine(Engine *e) {
	e->is_running = true;
}

bool can_engine_tick(Engine *e) {
	// If, for some reason, events queue is still processing, stall engine
	if (e->events->processing)
		return false;

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

void stop_engine(Engine *e) {
	e->paused = true;
}

void kill_engine(Engine *e) {
	e->is_running = false;
}

void handle_event(Engine *e, Event ev) {
	switch(ev.type) {
		case E_NOOP:
			return;
		case E_TERM:
			kill_engine(e);
		case E_INPUT:
			e->input |= ev.value;
		default:
			return;
	}
}

void handle_events(Engine *e) {
	if (e->events->eventc <= 0)
		return;
	
	e->events->processing = 1;
	for (int i = 0; i < e->events->eventc; i++) {
		Event ev = next_event(e->events);
		handle_event(e, ev);
	}
	clear_manager(e->events);
	
}

void handle_input(Engine *e) {
	int inputs = count_bits(e->input);
	print_bitset(e->input);
	if (inputs)
		printf("%d Bits set as input!\n", inputs);

	e->input = 0;
}

void tick_engine(Engine *e) {
	// Handle pending events
	handle_events(e);

	// Engine input
	handle_input(e);
	
	// Finally increment the tick counter
	e->tick += 1;
	e->last_tick_time = current_time_ms();
	
}


