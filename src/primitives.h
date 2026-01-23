#ifndef PRIMS_H
#define PRIMS_H

#include <stdint.h>

typedef struct Vertex {
  uint32_t x, y, z;

} Vertex;

typedef struct Line {
  Vertex *head;   //start vertex
  Vertex *tail;   //end vertex
  uint8_t normal; //facing direction
  uint8_t is_portal;
  uint16_t ceiling, floor;
  uint32_t adjacent_sector;

} Line;

typedef struct Sector {
  uint32_t vertexc, linec;
  uint32_t first_vert, first_line;

} Sector;

typedef struct Chunk {
  uint32_t sectorc;
  Sector *sectors;

} Chunk;

// Vertex functions
Vertex *create_verticies(int count);
void populate_verticies(Vertex *verts, int count, int *positions);

#endif