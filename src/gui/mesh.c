#include "mesh.h"
#include "../core/primitives.h"
#include "../core/world.h"

#include <stdlib.h>
#include <stdio.h>

void shredWall(World *w, WyrdMesh *mesh, int offset, int i) {

	//if(sector->normal == 0) { 
	if(w->s[w->l[i].sector].normal == 0) { 
		/* left triangle  */
		mesh->vertex_array[offset]   = w->v[w->l[i].head].x;
		mesh->vertex_array[offset+1] = w->s[w->l[i].sector].yb;
		mesh->vertex_array[offset+2] = w->v[w->l[i].head].z;
		
		mesh->vertex_array[offset+3] = w->v[w->l[i].tail].x;
		mesh->vertex_array[offset+4] = w->s[w->l[i].sector].yb;
		mesh->vertex_array[offset+5] = w->v[w->l[i].tail].z;
		
		mesh->vertex_array[offset+6] = w->v[w->l[i].head].x;
		mesh->vertex_array[offset+7] = w->s[w->l[i].sector].yt;
		mesh->vertex_array[offset+8] = w->v[w->l[i].head].z;
		/* right triangle */
		mesh->vertex_array[offset+9]  = w->v[w->l[i].tail].x;
		mesh->vertex_array[offset+10] = w->s[w->l[i].sector].yt;
		mesh->vertex_array[offset+11] = w->v[w->l[i].tail].z;

		mesh->vertex_array[offset+12] = w->v[w->l[i].head].x;
		mesh->vertex_array[offset+13] = w->s[w->l[i].sector].yt;
		mesh->vertex_array[offset+14] = w->v[w->l[i].head].z;
		
		mesh->vertex_array[offset+15] = w->v[w->l[i].tail].x;
		mesh->vertex_array[offset+16] = w->s[w->l[i].sector].yb;
		mesh->vertex_array[offset+17] = w->v[w->l[i].tail].z;
	} else {
		mesh->vertex_array[offset]   = w->v[w->l[i].tail].x;
		mesh->vertex_array[offset+1] = w->s[w->l[i].sector].yb;
		mesh->vertex_array[offset+2] = w->v[w->l[i].tail].z;
		
		mesh->vertex_array[offset+3] = w->v[w->l[i].head].x;
		mesh->vertex_array[offset+4] = w->s[w->l[i].sector].yb;
		mesh->vertex_array[offset+5] = w->v[w->l[i].head].z;
		
		mesh->vertex_array[offset+6] = w->v[w->l[i].head].x;
		mesh->vertex_array[offset+7] = w->s[w->l[i].sector].yt;
		mesh->vertex_array[offset+8] = w->v[w->l[i].head].z;

		mesh->vertex_array[offset+9]  = w->v[w->l[i].head].x;
		mesh->vertex_array[offset+10] = w->s[w->l[i].sector].yt;
		mesh->vertex_array[offset+11] = w->v[w->l[i].head].z;

		mesh->vertex_array[offset+12] = w->v[w->l[i].tail].x;
		mesh->vertex_array[offset+13] = w->s[w->l[i].sector].yt;
		mesh->vertex_array[offset+14] = w->v[w->l[i].tail].z;
		
		mesh->vertex_array[offset+15] = w->v[w->l[i].tail].x;
		mesh->vertex_array[offset+16] = w->s[w->l[i].sector].yb;
		mesh->vertex_array[offset+17] = w->v[w->l[i].tail].z;

	}

}

void shredPortal(World *w, WyrdMesh *mesh, int offset, int i) {
	/* start with floor part of portal */
	int nextFloor = w->s[w->l[i].adjacent_sector].yb;
	int nextCeiling = w->s[w->l[i].adjacent_sector].yt;
	int floor = w->s[w->l[i].sector].yb;
	int ceiling = nextFloor;

	for(int j = 0; j < 2; j++) {
    if(ceiling > floor) {
		if(w->s[w->l[i].sector].normal == 0) { 
			mesh->vertex_array[offset]		= w->v[w->l[i].head].x;
		  	mesh->vertex_array[offset+1]	= floor;
		  	mesh->vertex_array[offset+2]	= w->v[w->l[i].head].z;
	
	  		mesh->vertex_array[offset+3]	= w->v[w->l[i].tail].x;
	  		mesh->vertex_array[offset+4]	= floor;
	  		mesh->vertex_array[offset+5]	= w->v[w->l[i].tail].z;
	
		  	mesh->vertex_array[offset+6]	= w->v[w->l[i].head].x;
		  	mesh->vertex_array[offset+7]	= ceiling;
	  		mesh->vertex_array[offset+8]	= w->v[w->l[i].head].z;
	  		/* right triangle */
	  		mesh->vertex_array[offset+9]  = w->v[w->l[i].tail].x;
	  		mesh->vertex_array[offset+10] = ceiling;
	  		mesh->vertex_array[offset+11] = w->v[w->l[i].tail].z;

  			mesh->vertex_array[offset+12] = w->v[w->l[i].head].x;
  			mesh->vertex_array[offset+13] = ceiling;
  			mesh->vertex_array[offset+14] = w->v[w->l[i].head].z;
	
	  		mesh->vertex_array[offset+15] = w->v[w->l[i].tail].x;
			mesh->vertex_array[offset+16] = floor;
		  	mesh->vertex_array[offset+17] = w->v[w->l[i].tail].z;

      } else {
	  		mesh->vertex_array[offset]   = w->v[w->l[i].tail].x;
		  	mesh->vertex_array[offset+1] = floor;
	  		mesh->vertex_array[offset+2] = w->v[w->l[i].tail].z;
	
	  		mesh->vertex_array[offset+3] = w->v[w->l[i].head].x;
	  		mesh->vertex_array[offset+4] = floor;
			mesh->vertex_array[offset+5] = w->v[w->l[i].head].z;
	
		  	mesh->vertex_array[offset+6] = w->v[w->l[i].head].x;
	  		mesh->vertex_array[offset+7] = ceiling;
  			mesh->vertex_array[offset+8] = w->v[w->l[i].head].z;

  			mesh->vertex_array[offset+9]  = w->v[w->l[i].head].x;
  			mesh->vertex_array[offset+10] = ceiling;
  			mesh->vertex_array[offset+11] = w->v[w->l[i].head].z;

  			mesh->vertex_array[offset+12] = w->v[w->l[i].tail].x;
  			mesh->vertex_array[offset+13] = ceiling;
  			mesh->vertex_array[offset+14] = w->v[w->l[i].tail].z;
	
			mesh->vertex_array[offset+15] = w->v[w->l[i].tail].x;
			mesh->vertex_array[offset+16] = floor;
			mesh->vertex_array[offset+17] = w->v[w->l[i].tail].z;
      }

   } else {
    /* junk triangle for now, fix later */
		mesh->vertex_array[offset]   = 0;
		mesh->vertex_array[offset+1] = 0;
	  	mesh->vertex_array[offset+2] = 0;
	
	  	mesh->vertex_array[offset+3] = 0;
	  	mesh->vertex_array[offset+4] = 0;
		mesh->vertex_array[offset+5] = 0;
	
		mesh->vertex_array[offset+6] = 0;
	  	mesh->vertex_array[offset+7] = 0;
  		mesh->vertex_array[offset+8] = 0;

  		mesh->vertex_array[offset+9]  = 0;
  		mesh->vertex_array[offset+10] = 0;
  		mesh->vertex_array[offset+11] = 0;

  		mesh->vertex_array[offset+12] = 0;
  		mesh->vertex_array[offset+13] = 0;
  		mesh->vertex_array[offset+14] = 0;
	
		mesh->vertex_array[offset+15] = 0;
		mesh->vertex_array[offset+16] = 0;
		mesh->vertex_array[offset+17] = 0;
   }
    /* move to ceiling part */ 
    floor = nextCeiling;
    ceiling = w->s[w->l[i].sector].yt;
    offset += 18;
  }
}
/* applies a texture to each wall
 * alternates between each wall's two triangles
 * and flips the coords, hence the offset of 12 (3 verts)*(2 uv coords)*(2 triangles)*/
void applyTexture(WyrdMesh *mesh, int j) {
	mesh->texture_coord_array[j] = 0;
  	mesh->texture_coord_array[j+1] = 1;
  	mesh->texture_coord_array[j+2] = 1;
  	mesh->texture_coord_array[j+3] = 1;
  	mesh->texture_coord_array[j+4] = 0;
  	mesh->texture_coord_array[j+5] = 0;

  	mesh->texture_coord_array[j+6] = 1;
  	mesh->texture_coord_array[j+7] = 0;
  	mesh->texture_coord_array[j+8] = 0;
  	mesh->texture_coord_array[j+9] = 0;
  	mesh->texture_coord_array[j+10] = 1;
  	mesh->texture_coord_array[j+11] = 1;

}

/* returns number of triangles created from sectors */
int calculate_triangle_count(World *w) {
	int tcount = (w->lc - (w->sc * 2)) * 2;
  	return tcount;
}

int shred_map(World *world, WyrdMesh *mesh) {
	int flatTriangles = calculate_triangle_count(world);
	printf("Flat Triangle Count: %d\n", flatTriangles);
	printf("Line Count: %d\n", world->lc);
  
	// each wall has 2 triangles, each triangle 3 verticies, each vertex 3 coords + 2 extra for portals + sector flat triangles
	mesh->triangle_count = world->lc*2 + (world->pc*2) + 0; //flatTriangles;
	mesh->vertex_array = malloc(sizeof(int)*mesh->triangle_count*9);
	mesh->texture_coord_array = malloc(sizeof(int)*mesh->triangle_count*6);
	// loop and shred each wall
	int offset = 0;
	for(int i = 0; i < world->lc; i++) {
		if(world->l[i].is_portal == 1) {
			shredPortal(world, mesh, offset, i);
			offset += 6*3*2;
		} else {
			shredWall(world, mesh, offset, i);
			offset += 6*3;
		}
	}
  /*
  //loop and shred flats 
  for(int i = 0; i < map->sectorCount; i++) {
    //offset = shredFlats(map, smap, offset, i);
    
  }
  */
	// textures 
	offset = 0;
  	for(int j = 0; j < mesh->triangle_count; j++) {
		applyTexture(mesh, offset);
		offset += 12;
  	}
	return 0;
}
