#ifndef PRIMS_H
#define PRIMS_H

#include <stdint.h>

typedef struct Vertex {
  int32_t x, z;
  int32_t yb, yt; //bottom, top
  uint32_t id;
} Vertex;

typedef struct Line {
  uint32_t id;
  Vertex *head;   //start vertex
  Vertex *tail;   //end vertex
  uint8_t normal; //facing direction
  uint8_t is_portal;
  uint32_t adjacent_sector;

} Line;

typedef struct Sector {
  uint32_t id;
  uint32_t linec;
  Line *first_line;

} Sector;

typedef struct Chunk {
  uint32_t sectorc;
  Sector *sectors;

} Chunk;

// Vertex functions
Vertex *create_verticies(int count);
void populate_verticies(Vertex *verts, int count, int *positions);

#endif