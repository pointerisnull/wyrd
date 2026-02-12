#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum FlagType FlagType;
typedef uint32_t flag_t;

enum FlagType {
	F_SYSTEM, F_POSITION, F_ENTITY, F_ENVIRONMENT
};

uint8_t get_flag(flag_t bitfield, int index);
void set_flag(flag_t *bitfield, int index);
void clear_flag(flag_t *bitfield, int index);
void toggle_flag(flag_t *bitfield, int index);

#endif
