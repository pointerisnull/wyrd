#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t bitset_t;

void print_bitset(bitset_t bitset);
uint8_t get_bit(bitset_t bitset, int index);
void set_bit(bitset_t *bitset, int index);
void clear_bit(bitset_t *bitset, int index);
void toggle_bit(bitset_t *bitset, int index);
uint8_t count_bits(bitset_t b);

#endif
