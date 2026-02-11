#ifndef STATE_TYPE_H
#define STATE_TYPE_H

typedef enum StateType StateType;
typedef enum Flag Flag;

enum StateType {
	ENGINE, ENTITY_MOVEMENT, EVENT
};

enum Flag {
	NOOP, CHANGE_ME
};

#endif
