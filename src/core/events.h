#ifndef EVENTS_H
#define EVENTS_H

#include <stdint.h>

#define MAX_EVENTS 256

typedef struct Event Event;
typedef struct EventManager EventManager;

struct Event {
    uint16_t id;
    uint8_t type;
    uint8_t value;
};

struct EventHandler {
    uint8_t processing;
    int bufferc;
    // Events are added, first come first serve
    // All events must be handled before the next tick
    Event stack[MAX_EVENTS];
};

#endif