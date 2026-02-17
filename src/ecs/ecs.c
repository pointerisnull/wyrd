#include "entity.h"
#include "ecs.h"
#include "../misc/math.h"
#include "../misc/bitset.h"

#include <stdio.h>

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
		ecs->acceleration[i] = (Vec3){0, 0, 0};
		ecs->direction[i] = (Vec3){0, 0, 0};
		ecs->drag[i] = 0;

		// By default, all attributes are false
		ecs->is_static[i] = 0;
		ecs->has_gravity[i] = 0;
		ecs->has_inventory[i] = 0;
		ecs->has_agency[i] = 0;
	}
}

void add_entity(ECS *ecs, bitset_t attributes) {
	// First, find the first available slot for the new entity
	int bitset_arr_found = 0;
	int bitset_arr_index = 0;
	int id = 0;
	// Find the first bitset array with an open slot
	while (!bitset_arr_found) {
		if (bitset_arr_index >= SLOT_BITSET_ARR) {
			// No more room for entities, send to back buffer (eventually)
			printf("No more room for entities! Entity creation failed.\n");
			return;
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
	printf("Slot bitset index: %d of %d\n\n", bitset_arr_index, SLOT_BITSET_ARR);
	// Initialize entity positional components
	ecs->position[id] = (Vec3){0, 0, 0};
	ecs->velocity[id] = (Vec3){0, 0, 0};
	ecs->acceleration[id] = (Vec3){0, 0, 0};
	ecs->direction[id] = (Vec3){0, 0, 0};
	ecs->drag[id] = 0;
	// Finally, increment total entity count
	ecs->entityc++;
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

void move_entity(ECS *ecs, eid_t id, Vec3 pos);

void update_physics(ECS *ecs);
void update_positions(ECS *ecs);
void handle_collisions(ECS *ecs);

void handle_entity_event(ECS *ecs, Event e) {
	switch (e.value) {
		case E_MOVE:
			//move_entity(ecs, e.sender, (Vec3){0, 0, 0});
			break;
		case E_SPAWN:
			add_entity(ecs, 0);
			break;
		case E_KILL:
			kill_entity(ecs, e.reciever);
			break;
		default:
			break;
	}
}