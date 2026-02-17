#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "../core/events.h"
#include "../misc/bitset.h"
#include "../misc/math.h"

typedef struct Entity Entity;
typedef uint16_t eid_t;

struct Entity {
    eid_t eid;
    bitset_t attributes;

};

enum EntityAttributes {
    EA_HAS_DRAG,
    EA_STATIC,
    EA_HAS_GRAVITY,
    EA_HAS_INVENTORY,
    EA_HAS_AGENT
};

enum Movement {
	M_FORWARD,
	M_BACKWARD,
	M_STRAFE_LEFT,
	M_STRAFE_RIGHT,
	M_UP,
	M_DOWN,
	M_YAW,
	M_PITCH,
	M_ROLL,
	M_JUMP,

	M_ENUM_COUNT // Keep last, used to create bitmasks for these enums
};

Entity new_entity(eid_t id, int atrv[], int atrc);
Event entity_event(eid_t id, bitset_t type, Vec3 vec, int arg);

#endif
