#ifndef WORLD_H
#define WORLD_H

#include "primitives.h"
#include "../misc/bitset.h"

#define CHUNKS		16
#define CHUNK_SIZE	32  // How many units^2 is a chunk?
#define MAX_VERTS	2048
#define MAX_LINES	2048
#define MAX_SECTORS 2048

typedef struct World World;

struct World {
    Vertex v[MAX_VERTS];
    Line l[MAX_LINES];
    Sector s[MAX_SECTORS];
    Chunk c[CHUNKS];

    // This value will affect chunk coordinates
    int chunk_size;

    int vc;
    int lc;
    int pc;
    int sc;
    int cc;

};

World new_world();
void new_vertex(World *w, int x, int z);
void new_line(World *w, int head_id, int tail_id, int sector_id, int adj_sector, bitset_t flags);
void new_sector(World *w, int start_line_id, int line_count, int yb, int yt, int normal);

#endif
