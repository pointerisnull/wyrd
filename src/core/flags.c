#include "flags.h"

#include <stdio.h>

void print_bitfield(uint64_t bin) {
	for (int i = 0; i < sizeof(bin)*8; i++) {
		printf("%d", get_flag(bin, sizeof(bin)*8-1-i));
	}
	printf("\n");
}

uint8_t get_flag(uint64_t bitfield, int index) {
	return (uint8_t)(bitfield >> index) & 0x1;
}

void set_flag(uint64_t *bitfield, int index) {
	*bitfield |= ((uint64_t) 0x1 << index);
}

void clear_flag(uint64_t *bitfield, int index) {
	*bitfield &= ~((uint64_t) 0x1 << index);
}

void toggle_flag(uint64_t *bitfield, int index) {
	*bitfield ^= ((uint64_t) 0x1 << index);
}
