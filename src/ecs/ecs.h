#ifndef ECS_H
#define ECS_H

#include <stdint.h>

typedef struct ECS ECS;

struct ECS {
	float dt;				// delta time, seconds per tick
	uint64_t *engine_tick;	// Keep track of the engine's current tick
    int entityc;
};

void update_physics(ECS *ecs);
void update_positions(ECS *ecs);
void handle_collisions(ECS *ecs);

#endif
