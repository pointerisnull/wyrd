#ifndef PRIMS_H
#define PRIMS_H

#include <stdint.h>

typedef struct Vertex {
  int32_t x, z;
  uint32_t id;
} Vertex;

typedef struct Line {
  uint32_t id;
  uint32_t sector; // sector this line belongs to
  uint32_t head;   //start vertex
  uint32_t tail;   //end vertex
  uint8_t is_portal;
  uint32_t adjacent_sector;

} Line;

typedef struct Sector {
  uint32_t id;
  uint32_t linec;
  uint32_t first_line;
  int32_t yb, yt; //bottom, top
  uint8_t normal; //facing direction

} Sector;

typedef struct Chunk {
  uint32_t sectorc;
  Sector *sectors;

} Chunk;

#endif
