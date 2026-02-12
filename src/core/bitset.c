#include "bitset.h"

#include <stdio.h>

void print_bitset(uint32_t bin) {
	for (int i = 0; i < sizeof(bin)*8; i++) {
		printf("%d", get_bit(bin, sizeof(bin)*8-1-i));
	}
	printf("\n");
}

uint8_t get_bit(bitset_t bitset, int index) {
	return (uint8_t)(bitset >> index) & 0x1;
}

void set_bit(bitset_t *bitset, int index) {
	*bitset |= ((bitset_t) 0x1 << index);
}

void clear_bit(bitset_t *bitset, int index) {
	*bitset &= ~((bitset_t) 0x1 << index);
}

void toggle_bit(bitset_t *bitset, int index) {
	*bitset ^= ((bitset_t) 0x1 << index);
}
