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
		offset += 2;
	}
}
