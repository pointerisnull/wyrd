#ifndef MESH_H
#define MESH_H

#include <stdint.h>

#include "../core/world.h"

typedef struct WyrdMesh WyrdMesh;

struct WyrdMesh {
	int16_t *vertex_array;
	int16_t *texture_coord_array;
	uint16_t triangle_count;
};

int shred_sector(World *world, int sector_id, WyrdMesh *mesh);

#endif
