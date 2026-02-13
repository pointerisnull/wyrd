#ifndef INPUT_MAP_H
#define INPUT_MAP_H

typedef enum input_t input_t;

enum input_t {
	FORWARD,
	BACKWARD,
	STRAFE_LEFT,
	STRAFE_RIGHT,
	YAW,
	PITCH,
	SPRINT,
	JUMP,
	INTERACT,
	DESTROY,
	INVENTORY,
	PAUSE,
	RELEASE
};

#endif
