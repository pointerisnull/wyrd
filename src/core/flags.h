#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum FlagType FlagType;

enum FlagType {
	F_SYSTEM, F_POSITION, F_ENTITY, F_ENVIRONMENT
};

void print_bitfield(uint64_t bitfield);
uint8_t get_flag(uint64_t bitfield, int index);
void set_flag(uint64_t *bitfield, int index);
void clear_flag(uint64_t *bitfield, int index);
void toggle_flag(uint64_t *bitfield, int index);

#endif
