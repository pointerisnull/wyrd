#include "events.h"
#include "../misc/bitset.h"

#include <stdio.h>

Event new_event(uint8_t type, uint16_t value) {
	Event e;
	e.pid = 0;
	e.type = type;
	e.value = value;
	return e;
}

int event_index(EventManager *em, int type) {
	for (int i = 0; i < em->eventc; i++)
		if (em->buffer[i].type == type)
			return i;
	return -1;
}

void queue_event(EventManager *em, Event e) {
	// Special processing 
	switch(e.type) {
		//Inputs are treated as flags in a bitset
		case E_INPUT:
			// if input, and an input event already exists, mask the old one and return
			bitset_t mask = 0x1 << e.value;
			int index = event_index(em, E_INPUT);
			// if an input event exists
			if (index >= 0) {
				em->buffer[index].value |= mask;
				return;
			}
			e.value = mask;
		default:
			break;
	}

	if (em->eventc < MAX_EVENTS) {
		em->buffer[em->eventc] = e;
		em->eventc++;
	}
}

Event next_event(EventManager *em) {
	Event ev;
	if (em->eventp < em->eventc) {
		ev = em->buffer[em->eventp];
		em->eventp++;
	} else {
		ev = new_event(E_TERM, 0);
	}
	return ev;
}

void clear_manager(EventManager *em) {
	em->eventp = 0; 
	em->eventc = 0; 
	em->processing = 0;
}

void print_queue(EventManager *em) {
	for (int i=0; i < em->eventc; i++)
		printf("%d:\tType: %d Value: %d\n", i, em->buffer[i].type, em->buffer[i].value);
}
