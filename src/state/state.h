#ifndef STATE_H
#define STATE_H

#include "state_type.h"
// States that all relate to eachother based on type.
// The amount of flags = the amount of states.
// When a flag is set, move to the state which address is the same index as the flag type
// First flag is always to do nothing, with the first state being itself

typedef struct State State;

struct State {
	StateType type;		// type of state 
	Flag state_flag;	// current 'state' of state, determines where to go from here
	int flagc;
	Flag *change_flags;	// by number of flagc, conditions on which to change state
	int pathc;
	State *next_state;	// by number of statec, next states corresponding with flags above
};

State *new_state_list(int *map);
void update_state(State *current, Flag new_flag);
State *change_state(State *current);

#endif
