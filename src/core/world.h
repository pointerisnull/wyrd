#ifndef WORLD_H
#define WORLD_H

#include "primitives.h"

#define CHUNKS  16
#define MAX_VERTS 2048
#define MAX_LINES 2048
#define MAX_SECTORS 2048

typedef struct World World;

struct World {
    Vertex v[MAX_VERTS];
    Line l[MAX_LINES];
    Sector s[MAX_SECTORS];
    Chunk c[CHUNKS];

    // How many units wide is a chunk?
    // This value will affect chunk coordinates
    int chunk_size = 32;

    int vc;
    int lc;
    int sc;
    int cc;

};

void new_vertex(World *w, int x, int z, int yb, int yt);
void new_line(World *w, int head_id, int tail_id);
void new_sector(World *w, int start_line_id, int line_count);

#endif