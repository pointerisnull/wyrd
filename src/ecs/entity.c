#include "entity.h"

Entity new_entity(eid_t id, int atrv[], int atrc);

Event entity_event(eid_t id, bitset_t type, Vec3 vec, int arg) {
    Event e = new_event(E_ENTITY, type);
    e.reciever = id;
    e.vec = vec;
    e.arg = arg;
    return e;
}