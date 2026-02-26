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
	
	e.init_time = current_time_ms();
	e.last_tick_time = e.start_time;
	
	e.headless = true;
	e.is_running = false;
	e.paused = false;

	e.input = 0;
	e.flags = 0;

	// Setup input masks
	for (int i=0; i < I_ENUM_COUNT; i++) {
		e.I_MASKS[i] = 0x1 << i;
	}
	
	initialize_ecs(&e.ecs, &e.tick, e.tickrate);
	
	return e;
}

void start_engine(Engine *e) {
	e->start_time = current_time_ms();
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
			printf("Shutting down engine -> Tick: %ld\n", e->tick);
			return;
		case E_SYSTEM:
			// Handle system events here
			return;
		case E_INPUT:
			e->input |= ev.value;
			return;
		case E_ENTITY:
			handle_entity_event(&e->ecs, ev);
			return;
		default:
			return;
	}
}

void handle_events(Engine *e) {
	if (e->events->eventc <= 0)
		return;
	//printf("Handling events for tick %ld\n",e->tick);
	e->events->processing = 1;
	for (int i = 0; i < e->events->eventc; i++) {
		Event ev = next_event(e->events);
		handle_event(e, ev);
	}
	clear_manager(e->events);
	
}

void execute_input(Engine *e, int val) {
	Event ev;
	switch (val) {
		case I_FORWARD:
			//printf("Forward input detected!\n");
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_FORWARD);
			queue_event(e->events, ev);
			return;
		case I_BACKWARD:
			//printf("Reverse input detected!\n");
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_BACKWARD);
			queue_event(e->events, ev);
			return;
		case I_STRAFE_LEFT:
			//printf("Strafe left input detected!\n");
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_STRAFE_LEFT);
			queue_event(e->events, ev);
			return;
		case I_STRAFE_RIGHT:
			//printf("Strafe right input detected!\n");	
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_STRAFE_RIGHT);
			queue_event(e->events, ev);
			return;
		case I_YAW_LEFT:
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_YAW_LEFT);
			queue_event(e->events, ev);
			return;
		case I_YAW_RIGHT:
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_YAW_RIGHT);
			queue_event(e->events, ev);
			return;
		case I_PITCH_UP:
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_PITCH_UP);
			queue_event(e->events, ev);
			return;
		case I_PITCH_DOWN:
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_PITCH_DOWN);
			queue_event(e->events, ev);
			return;
		case I_JUMP:
			// Do nothing for now
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_JUMP);
			queue_event(e->events, ev);
			return;
		case I_SPRINT:
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_SPRINT);
			queue_event(e->events, ev);
			return;
		case I_WALK:
			ev = entity_event(0, E_MOVE, (Vec3){0,0,0}, M_WALK);
			queue_event(e->events, ev);
			return;		
		default:
			printf("Input %d could not be determined.\n", val);
			return;
	}
}

void handle_input(Engine *e) {
	if (!e->input)
		return;
	
	int inputs = e->input;
	int inputc = count_bits(e->input);
	print_bitset(e->input);
	int i = 0;
	while (inputs) {
		if (inputs & 0x1) {
			execute_input(e, i);
		}
		inputs = inputs >> 1;
		i++;
	}

	e->input = 0;
}

void tick_engine(Engine *e) {
	// Handle pending events
	handle_events(e);

	// Engine input
	handle_input(e);
	
	// Deal with entities
	update_physics(&e->ecs);


	// Finally increment the tick counter
	e->tick += 1;
	e->last_tick_time = current_time_ms();
	
}


