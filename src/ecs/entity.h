#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "../misc/bitset.h"
#include "../misc/math.h"

typedef struct Entity Entity;
typedef uint16_t eid_t;

struct Entity {
    eid_t eid;
    Vec3 p;		// Position
    Vec3 v;		// Velocity
    Vec3 a;		// Acceleration
    
	Vec3 d;		// Direction

    bitset_t attributes;

};

enum EntityAttributes {
    EA_STATIC,
    EA_HAS_INVENTORY,
    EA_HAS_AGENT
};

Entity new_entity(int atrv[], int atrc);
void spawn_entity(float x, float y, float z);

#endif
