#ifndef INPUT_MAP_H
#define INPUT_MAP_H

typedef enum input_t input_t;
typedef enum movement_t movement_t;

enum input_t {
	I_FORWARD,
	I_BACKWARD,
	I_STRAFE_LEFT,
	I_STRAFE_RIGHT,
	I_YAW,
	I_PITCH,
	I_SPRINT,
	I_JUMP,
	I_INTERACT,
	I_DESTROY,
	I_INVENTORY,
	I_PAUSE,
	I_RELEASE,

	I_ENUM_COUNT // Keep last, used to create bitmasks for these enums
};

enum movement_t {
	M_FORWARD,
	M_BACKWARD,
	M_STRAFE_LEFT,
	M_STRAFE_RIGHT,
	M_UP,
	M_DOWN,
	M_YAW,
	M_PITCH,
	M_ROLL,
	M_JUMP,

	M_ENUM_COUNT // Keep last, used to create bitmasks for these enums
};

#endif
