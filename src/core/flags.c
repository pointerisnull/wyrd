#include "flags.h"

#include <stdio.h>

void print_flag(uint32_t bin) {
	for (int i = 0; i < sizeof(bin)*8; i++) {
		printf("%d", get_flag(bin, sizeof(bin)*8-1-i));
	}
	printf("\n");
}

uint8_t get_flag(flag_t bitfield, int index) {
	return (uint8_t)(bitfield >> index) & 0x1;
}

void set_flag(flag_t *bitfield, int index) {
	*bitfield |= ((flag_t) 0x1 << index);
}

void clear_flag(flag_t *bitfield, int index) {
	*bitfield &= ~((flag_t) 0x1 << index);
}

void toggle_flag(flag_t *bitfield, int index) {
	*bitfield ^= ((flag_t) 0x1 << index);
}
