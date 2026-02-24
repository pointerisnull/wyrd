#include "entity.h"
#include "ecs.h"
#include "../misc/math.h"
#include "../misc/bitset.h"

#include <stdio.h>
#include <math.h>

void initialize_ecs(ECS *ecs, uint64_t *engine_ticker, int tickrate) {
	ecs->dt = 1.0/(float)tickrate;
	ecs->engine_tick = engine_ticker;

	ecs->entityc = 0;

	for (int i = 0; i < SLOT_BITSET_ARR; i++) {
		ecs->slots[i] = 0;
	}
	// Initialize entity components 
	for (int i = 0; i < MAX_ENTITIES; i++) {
		ecs->position[i] = (Vec3){0, 0, 0};
		ecs->velocity[i] = (Vec3){0, 0, 0};
		ecs->direction[i] = (Vec3){0, PI, 0};
		ecs->drag[i] = DEFAULT_ENTITY_DRAG;
		ecs->speed[i] = DEFAULT_SPEED;
		ecs->rotspeed[i] = DEFAULT_ROTSPEED;

		// By default, all attributes are false
		ecs->is_static[i] = 0;
		ecs->is_flying[i] = 0;
		ecs->has_inventory[i] = 0;
		ecs->has_agency[i] = 0;
	}
}

eid_t add_entity(ECS *ecs, bitset_t attributes, Vec3 spawnpoint) {
	// First, find the first available slot for the new entity
	int bitset_arr_found = 0;
	int bitset_arr_index = 0;
	int id = 0;
	// Find the first bitset array with an open slot
	while (!bitset_arr_found) {
		if (bitset_arr_index >= SLOT_BITSET_ARR) {
			// No more room for entities, send to back buffer (eventually)
			printf("No more room for entities! Entity creation failed.\n");
			return -1;
		}
		bitset_t slots = ecs->slots[bitset_arr_index];
		int size = sizeof(ecs->slots[0])*8;

		for (int i = 0; i < size; i++) {
			if ((slots & ((bitset_t)1 << i)) == 0) {
				// Found an open slot, flip bit then break
				ecs->slots[bitset_arr_index] |= ((bitset_t)1 << i);
				bitset_arr_found = 1;
				id = i+size*bitset_arr_index;
				break;
			}
		}
		bitset_arr_index++;
	}
	printf("Added entity with ID: %d\n", id);
	print_bitset(ecs->slots[bitset_arr_index-1]);
	//print_bitset((bitset_t)(ecs->slots[bitset_arr_index-1]>>32));
	printf("Slot bitset index: %d of %ld\n\n", bitset_arr_index, SLOT_BITSET_ARR);
	// Initialize entity positional components
	ecs->position[id] = spawnpoint;
	ecs->velocity[id] = (Vec3){0, 0, 0};
	ecs->direction[id] = (Vec3){0, PI, 0};
	ecs->drag[id] = DEFAULT_ENTITY_DRAG;
	ecs->speed[id] = DEFAULT_SPEED;
	ecs->rotspeed[id] = DEFAULT_ROTSPEED;
	// Finally, increment total entity count
	ecs->entityc++;
	return id;
}

void kill_entity(ECS *ecs, eid_t e) {
	if (e < 0 || e >= MAX_ENTITIES) {
		printf("Invalid entity ID: %d. Out of range.\n", e);
		return;
	}
	int bitset_arr_index = e/(sizeof(bitset_t)*8);
	int bit_index = e%(sizeof(bitset_t)*8);
	if (get_bit(ecs->slots[bitset_arr_index], bit_index) == 0) {
		printf("Entity with ID: %d does not exist in the ecs slots.\n", e);
		return;
	}
	toggle_bit(&ecs->slots[bitset_arr_index], bit_index);
	ecs->entityc--;
	printf("Killed entity %d.\n", e);
	//print_bitset(ecs->slots[bitset_arr_index]);
}

void move_entity(ECS *ecs, eid_t id, Vec3 pos) {
	ecs->position[id] = pos;
}

void update_physics(ECS *ecs) {
	// PLEASE PLEASE PLEASE OPTIMIZE THIS
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (get_bit(ecs->slots[i/(sizeof(bitset_t)*8)], i%(sizeof(bitset_t)*8)) == 1) {
			// Apply velocity to position
			ecs->position[i].x += ecs->velocity[i].x;
			ecs->position[i].y += ecs->velocity[i].y;
			ecs->position[i].z += ecs->velocity[i].z;
			
			// Apply drag
			ecs->velocity[i].x *= ecs->drag[i];
			ecs->velocity[i].y *= ecs->drag[i];
			ecs->velocity[i].z *= ecs->drag[i];
	
		}
	}
}
// TODO
void update_positions(ECS *ecs);
// TODO
void handle_collisions(ECS *ecs);

void apply_movement(ECS *ecs, eid_t id, int direction) {
	float magnitude = ecs->speed[id] * ecs->dt;

	switch(direction) {
		case M_FORWARD:
			ecs->velocity[id].x += sin(ecs->direction[id].y)*magnitude;
			ecs->velocity[id].z += cos(ecs->direction[id].y)*magnitude;
			if (ecs->is_flying[id])
				ecs->velocity[id].y += sin(ecs->direction[id].x)*magnitude;
			return;

		case M_BACKWARD:
			ecs->velocity[id].x -= sin(ecs->direction[id].y)*magnitude;
			ecs->velocity[id].z -= cos(ecs->direction[id].y)*magnitude;
			if (ecs->is_flying[id])
				ecs->velocity[id].y -= sin(ecs->direction[id].x)*magnitude;
			return;
		case M_STRAFE_LEFT:
			// 1.5708f = PI/2
			ecs->velocity[id].x -= sin(ecs->direction[id].y - 1.5708f)*magnitude;
			ecs->velocity[id].z -= cos(ecs->direction[id].y - 1.5708f)*magnitude;
			return;
		case M_STRAFE_RIGHT:
			ecs->velocity[id].x += sin(ecs->direction[id].y - 1.5708f)*magnitude;
			ecs->velocity[id].z += cos(ecs->direction[id].y - 1.5708f)*magnitude;
			return;
		case M_UP:
			return;
		case M_DOWN:
			return;
		case M_YAW_LEFT: // looking left
			ecs->direction[id].y += ecs->rotspeed[id]*ecs->dt;
			if (ecs->direction[id].y < 0) {
				ecs->direction[id].y += 6.28319f; // 2*PI
			}
			return;
		case M_YAW_RIGHT: // looking right
			ecs->direction[id].y -= ecs->rotspeed[id]*ecs->dt;
			if (ecs->direction[id].y > 6.28319f) {
				ecs->direction[id].y -= 6.28319f; // 2*PI
			}
			return;
		case M_PITCH_UP: // looking up
			return;
		case M_PITCH_DOWN: // looking down
			return;
		case M_ROLL: // rotating view 
			return;
		case M_JUMP:
			if (ecs->velocity[id].y == 0) {
				ecs->velocity[id].y = 5;
			}
			return;
		case M_SPRINT:
			ecs->speed[id] = DEFAULT_SPEED + SPRINT_MODIFIER;
			return;
		case M_WALK:
			ecs->speed[id] = DEFAULT_SPEED;
		default:
			return;
	}
}

void handle_entity_event(ECS *ecs, Event e) {
	switch (e.value) {
		case E_MOVE:
			apply_movement(ecs, e.reciever, e.arg);
			break;
		case E_SPAWN:
			add_entity(ecs, 0, e.vec);
			break;
		case E_KILL:
			kill_entity(ecs, e.reciever);
			break;
		default:
			break;
	}
}
