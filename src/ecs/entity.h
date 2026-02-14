#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "../misc/bitset.h"
#include "../misc/math.h"

typedef struct Entity Entity;
typedef uint16_t eid_t;

struct Entity {
    eid_t eid;
    bitset_t attributes;

};

enum EntityAttributes {
    EA_STATIC,
    EA_HAS_GRAVITY,
    EA_HAS_INVENTORY,
    EA_HAS_AGENT
};

Entity new_entity(eid_t id, int atrv[], int atrc);

#endif
