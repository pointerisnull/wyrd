#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "../misc/bitset.h"

typedef struct Entity Entity;
typedef uint16_t eid_t;
typedef enum EntityAttributes;

struct Entity {
    eid_t eid;
    float x, y, z;

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