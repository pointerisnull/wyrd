#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdbool.h>

#include "../misc/bitset.h"
#include "../misc/input_map.h"
#include "../ecs/ecs.h"
#include "events.h"
#include "world.h"

typedef struct Engine {
	int64_t tick;
	int tickrate; // ticks per second
	int tick_delta; // ms
	uint64_t last_tick_time;
	uint64_t init_time;
	uint64_t start_time;
	
	uint8_t is_running;
	uint8_t paused;
	uint8_t headless;

	bitset_t input;
	bitset_t flags;
	
	EventManager *events;
	ECS ecs;
	World *world;

	int I_MASKS[I_ENUM_COUNT];

} Engine;

Engine new_engine(int rate);
void start_engine(Engine *e);
void tick_engine(Engine *e);
bool can_engine_tick(Engine *e);
bool engine_running(Engine *e);
void stop_engine(Engine *e);
void kill_engine(Engine *e);

#endif
