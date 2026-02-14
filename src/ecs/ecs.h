#ifndef ECS_H
#define ECS_H

#include "entity.h"

#include <stdint.h>

#define MAX_ENTITIES 1024
#define ENTITY_SLOTS MAX_ENTITIES/sizeof(bitset_t)

typedef struct ECS ECS;

struct ECS {
	float dt;				// delta time, seconds per tick
	uint64_t *engine_tick;	// Keep track of the engine's current tick

    int entityc;
	uint64_t slots[ENTITY_SLOTS];

	/* All entities will have positional components at least */
	Vec3 position[MAX_ENTITIES];
    Vec3 velocity[MAX_ENTITIES];
    Vec3 acceleration[MAX_ENTITIES];
	Vec3 direction[MAX_ENTITIES];
	float drag[MAX_ENTITIES];
	
	/* Boolean Attributes */
	uint8_t is_static[MAX_ENTITIES];
	uint8_t has_gravity[MAX_ENTITIES];
	uint8_t has_inventory[MAX_ENTITIES];
	uint8_t has_agency[MAX_ENTITIES];
};

void initialize_ecs(ECS *ecs, uint64_t *engine_ticker, int tickrate);
void add_entity(ECS *ecs, bitset_t attributes);
void kill_entity(ECS *ecs, eid_t e);

void move_entity(ECS *ecs, eid_t id, Vec3 pos);

void update_physics(ECS *ecs);
void update_positions(ECS *ecs);
void handle_collisions(ECS *ecs);

#endif
