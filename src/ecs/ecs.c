#include "entity.h"
#include "ecs.h"
#include "../misc/math.h"

void initialize_ecs(ECS *ecs, uint64_t *engine_ticker, int tickrate) {
	ecs->dt = 1.0/(float)tickrate;
	ecs->engine_tick = engine_ticker;

	ecs->entityc = 0;
}

void add_entity(ECS *ecs, bitset_t attributes);
void kill_entity(ECS *ecs, eid_t e);

void move_entity(ECS *ecs, eid_t id, Vec3 pos);

void update_physics(ECS *ecs);
void update_positions(ECS *ecs);
void handle_collisions(ECS *ecs);

