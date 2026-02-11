#include "state.h"
#include "state_type.h"

State *new_state_list(int *map) {
	State *s;

	return s;
}

void update_state(State *current, Flag new_flag) {
	current->state_flag = new_flag;
}

State *change_state(State *current) {
	if ((current->state_flag != NOOP) && (current->flagc ==current->pathc)) {
		//state flag has changed
		for (int i=0; i < current->flagc; i++) {
			if (current->change_flags[i] ==  current->state_flag) {
				current->state_flag = NOOP;
				return &current->next_state[i];
			} else {
				// there must have been an error, change state back to NOOP
				current->state_flag = NOOP;
			}
		}
	}
	// return iteself, so no change
	return current;
}
