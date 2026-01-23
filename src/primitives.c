#include "primitives.h"

#include <stdlib.h>

Vertex *create_verticies(int count) {
    Vertex *verticies = malloc(sizeof(Vertex)*count);
    return verticies;
}

void populate_verticies(Vertex *verts, int count, int *positions) {
    int offset = 0;
    for(int i = 0; i < count; i++) {
        verts[i].x = positions[offset];
        verts[i].y = positions[offset+1];
        verts[i].z = positions[offset+2];
        offset += 3;
    }
}