#ifndef EVENTS_H
#define EVENTS_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_EVENTS 256

typedef enum EventType EventType;

typedef struct Event Event;
typedef struct EventManager EventManager;

enum EventType {
	E_TERM, E_NOOP, E_INPUT, E_SYSTEM, E_ENTITY_MOVE
};

struct Event {
    uint16_t pid;
    uint8_t type;
    uint16_t value;
};

struct EventManager {
    uint8_t processing;
    int eventc; // event count
	int eventp; // event pointer (current index in buffer)
    // Events are added, first come first serve
    // All events must be handled before the next tick
    Event buffer[MAX_EVENTS];
};

Event new_event(uint8_t type, uint16_t value);

void queue_event(EventManager *em, Event e);
Event next_event(EventManager *em);
void clear_manager(EventManager *em);
void print_queue(EventManager *em);

#endif
