#ifndef ECS_H
#define ECS_H

#include "entity.h"
#include "../core/events.h"

#include <stdint.h>

#define MAX_ENTITIES 1024
#define SLOT_BITSET_ARR MAX_ENTITIES/(sizeof(bitset_t)*8)

#define DEFAULT_SPEED 2.5f
#define SPRINT_MODIFIER 2.0f
#define DEFAULT_ROTSPEED 2.0f
#define DEFAULT_ENTITY_DRAG 0.75f

typedef struct ECS ECS;

struct ECS {
	float dt;				// delta time, seconds per tick
	uint64_t *engine_tick;	// Keep track of the engine's current tick

	int entityc;
	bitset_t slots[SLOT_BITSET_ARR];

	/* All entities will have positional components at least */
	Vec3 position[MAX_ENTITIES];
	Vec3 velocity[MAX_ENTITIES];
	Vec3 direction[MAX_ENTITIES];		// Normalized direction vector
	float speed[MAX_ENTITIES];		// How fast the entity can move, m/s
	float rotspeed[MAX_ENTITIES];		// rotational speed, m/s
	float drag[MAX_ENTITIES];
	
	/* Boolean Attributes */
	uint8_t is_static[MAX_ENTITIES];
	uint8_t is_flying[MAX_ENTITIES];
	uint8_t has_inventory[MAX_ENTITIES];
	uint8_t has_agency[MAX_ENTITIES];
};

void initialize_ecs(ECS *ecs, uint64_t *engine_ticker, int tickrate);
eid_t add_entity(ECS *ecs, bitset_t attributes, Vec3 spawnpoint);
void kill_entity(ECS *ecs, eid_t e);

void move_entity(ECS *ecs, eid_t id, Vec3 pos);

void update_physics(ECS *ecs);
void update_positions(ECS *ecs);
void handle_collisions(ECS *ecs);

void handle_entity_event(ECS *ecs, Event e);

#endif
