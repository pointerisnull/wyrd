#include "mesh.h"
#include "../misc/math.h"
#include "../core/primitives.h"
#include "../core/world.h"

#include <stdlib.h>
#include <stdio.h>

void shred_wall(World *w, WyrdMesh *mesh, int offset, int i) {

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

void shred_portal(World *w, WyrdMesh *mesh, int offset, int i) {
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
	  		mesh->vertex_array[offset+9]	= w->v[w->l[i].tail].x;
	  		mesh->vertex_array[offset+10] 	= ceiling;
	  		mesh->vertex_array[offset+11] 	= w->v[w->l[i].tail].z;

  			mesh->vertex_array[offset+12] 	= w->v[w->l[i].head].x;
  			mesh->vertex_array[offset+13] 	= ceiling;
  			mesh->vertex_array[offset+14] 	= w->v[w->l[i].head].z;
	
	  		mesh->vertex_array[offset+15] 	= w->v[w->l[i].tail].x;
			mesh->vertex_array[offset+16] 	= floor;
		  	mesh->vertex_array[offset+17] 	= w->v[w->l[i].tail].z;

      } else {
	  		mesh->vertex_array[offset]		= w->v[w->l[i].tail].x;
		  	mesh->vertex_array[offset+1] 	= floor;
	  		mesh->vertex_array[offset+2] 	= w->v[w->l[i].tail].z;
	
	  		mesh->vertex_array[offset+3] 	= w->v[w->l[i].head].x;
	  		mesh->vertex_array[offset+4] 	= floor;
			mesh->vertex_array[offset+5] 	= w->v[w->l[i].head].z;
	
		  	mesh->vertex_array[offset+6] 	= w->v[w->l[i].head].x;
	  		mesh->vertex_array[offset+7] 	= ceiling;
  			mesh->vertex_array[offset+8] 	= w->v[w->l[i].head].z;

  			mesh->vertex_array[offset+9]	= w->v[w->l[i].head].x;
  			mesh->vertex_array[offset+10] 	= ceiling;
  			mesh->vertex_array[offset+11] 	= w->v[w->l[i].head].z;

  			mesh->vertex_array[offset+12] 	= w->v[w->l[i].tail].x;
  			mesh->vertex_array[offset+13] 	= ceiling;
  			mesh->vertex_array[offset+14] 	= w->v[w->l[i].tail].z;
	
			mesh->vertex_array[offset+15] 	= w->v[w->l[i].tail].x;
			mesh->vertex_array[offset+16] 	= floor;
			mesh->vertex_array[offset+17] 	= w->v[w->l[i].tail].z;
      }

   } else {
    /* junk triangle for now, fix later */
		mesh->vertex_array[offset]		= 0;
		mesh->vertex_array[offset+1] 	= 0;
	  	mesh->vertex_array[offset+2] 	= 0;
	
	  	mesh->vertex_array[offset+3] 	= 0;
	  	mesh->vertex_array[offset+4] 	= 0;
		mesh->vertex_array[offset+5] 	= 0;
	
		mesh->vertex_array[offset+6] 	= 0;
	  	mesh->vertex_array[offset+7] 	= 0;
  		mesh->vertex_array[offset+8] 	= 0;

  		mesh->vertex_array[offset+9]	= 0;
  		mesh->vertex_array[offset+10] 	= 0;
  		mesh->vertex_array[offset+11] 	= 0;

  		mesh->vertex_array[offset+12] 	= 0;
  		mesh->vertex_array[offset+13] 	= 0;
  		mesh->vertex_array[offset+14] 	= 0;
	
		mesh->vertex_array[offset+15] 	= 0;
		mesh->vertex_array[offset+16] 	= 0;
		mesh->vertex_array[offset+17] 	= 0;
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
void apply_texture(WyrdMesh *mesh, int j) {
	mesh->texture_coord_array[j]	= 0;
  	mesh->texture_coord_array[j+1]	= 1;
  	mesh->texture_coord_array[j+2] 	= 1;
  	mesh->texture_coord_array[j+3] 	= 1;
  	mesh->texture_coord_array[j+4] 	= 0;
  	mesh->texture_coord_array[j+5] 	= 0;

  	mesh->texture_coord_array[j+6]	= 1;
  	mesh->texture_coord_array[j+7] 	= 0;
  	mesh->texture_coord_array[j+8] 	= 0;
  	mesh->texture_coord_array[j+9] 	= 0;
  	mesh->texture_coord_array[j+10] = 1;
  	mesh->texture_coord_array[j+11] = 1;

}

/* returns number of triangles created from sectors */
int calculate_triangle_count(World *w, int sector) {
	int total_triangles = 0;

	// Each line makes 2 triangles
	total_triangles += (w->s[sector].linec * 2);

    // Get portal count, each portal adds 2 triangles
    int start = w->s[sector].first_line;
    for (int i = 0; i < w->s[sector].linec; i++) {
        if (w->l[start+i].is_portal) {
	        total_triangles += 2;
        }
    }

	// Calculate floor and ceiling triangles
    int n_lines = w->s[sector].linec;
    // A valid polygon must have at least 3 sides
    if (n_lines >= 3) {
	// (N - 2) triangles per flat. 
    // Multiply by 2 because of floor and ceiling.
        total_triangles += (n_lines - 2) * 2;
    }

	return total_triangles;
}

float sign(float ax, float az, float bx, float bz, float cx, float cz) {
    return (bx - ax) * (cz - az) - (bz - az) * (cx - ax);
}

int is_point_in_triangle(float px, float pz, float ax, float az, float bx, float bz, float cx, float cz) {
    float d1 = sign(px, pz, ax, az, bx, bz);
    float d2 = sign(px, pz, bx, bz, cx, cz);
    float d3 = sign(px, pz, cx, cz, ax, az);

    int has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    int has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

// TEMPORARY STRUCT
typedef struct {
    int start_vert;
    int end_vert;
    int used;
} SectorLine;

void shred_single_loop(World *w, WyrdMesh *mesh, int sector_idx, int *ordered_verts, int num_verts, int *offset) {
    int floor_y = w->s[sector_idx].yb;
    int ceiling_y = w->s[sector_idx].yt;
    
    int active_verts[512]; 
    for(int i = 0; i < num_verts; i++) {
        active_verts[i] = ordered_verts[i];
    }
    
    int verts_left = num_verts;

    while (verts_left > 2) {
        int ear_found = 0;

        for (int i = 0; i < verts_left; i++) {
            int prev_idx = (i == 0) ? (verts_left - 1) : (i - 1);
            int next_idx = (i + 1) % verts_left;

            int v0 = active_verts[prev_idx];
            int v1 = active_verts[i];
            int v2 = active_verts[next_idx];

            float ax = w->v[v0].x; float az = w->v[v0].z;
            float bx = w->v[v1].x; float bz = w->v[v1].z;
            float cx = w->v[v2].x; float cz = w->v[v2].z;

            // Is the angle convex?
            if (sign(ax, az, bx, bz, cx, cz) > 0) {
                
                // Are any other vertices inside this triangle?
                int is_ear = 1;
                for (int j = 0; j < verts_left; j++) {
                    if (j == prev_idx || j == i || j == next_idx) continue;
                    
                    int p_idx = active_verts[j];
                    if (is_point_in_triangle(w->v[p_idx].x, w->v[p_idx].z, ax, az, bx, bz, cx, cz)) {
                        is_ear = 0;
                        break;
                    }
                }

                if (is_ear) {
                    // Floor Triangle (v0, v2, v1 - Reversed to flip normal)
                    mesh->vertex_array[*offset + 0] = ax; mesh->vertex_array[*offset + 1] = floor_y; mesh->vertex_array[*offset + 2] = az;
                    mesh->vertex_array[*offset + 3] = cx; mesh->vertex_array[*offset + 4] = floor_y; mesh->vertex_array[*offset + 5] = cz;
                    mesh->vertex_array[*offset + 6] = bx; mesh->vertex_array[*offset + 7] = floor_y; mesh->vertex_array[*offset + 8] = bz;

                    // Ceiling Triangle (v0, v1, v2 - Reversed to flip normal)
                    mesh->vertex_array[*offset + 9]  = ax; mesh->vertex_array[*offset + 10] = ceiling_y; mesh->vertex_array[*offset + 11] = az;
                    mesh->vertex_array[*offset + 12] = bx; mesh->vertex_array[*offset + 13] = ceiling_y; mesh->vertex_array[*offset + 14] = bz;
                    mesh->vertex_array[*offset + 15] = cx; mesh->vertex_array[*offset + 16] = ceiling_y; mesh->vertex_array[*offset + 17] = cz;

                    *offset += 18; 

                    // Since offset is for the vertex array (9 floats per triangle), 
                    // we calculate the corresponding texture array offset (6 floats per triangle).
                    int uv_offset = (*offset / 3) * 2; 
                    float scale = 64.0;

                    // Floor
                    mesh->texture_coord_array[uv_offset + 0] = ax / scale; mesh->texture_coord_array[uv_offset + 1] = az / scale;
                    mesh->texture_coord_array[uv_offset + 2] = cx / scale; mesh->texture_coord_array[uv_offset + 3] = cz / scale;
                    mesh->texture_coord_array[uv_offset + 4] = bx / scale; mesh->texture_coord_array[uv_offset + 5] = bz / scale;

                    // Ceiling 
                    mesh->texture_coord_array[uv_offset + 6]  = ax / scale; mesh->texture_coord_array[uv_offset + 7]  = az / scale;
                    mesh->texture_coord_array[uv_offset + 8]  = bx / scale; mesh->texture_coord_array[uv_offset + 9]  = bz / scale;
                    mesh->texture_coord_array[uv_offset + 10] = cx / scale; mesh->texture_coord_array[uv_offset + 11] = cz / scale;

                    // Remove the ear tip
                    for (int k = i; k < verts_left - 1; k++) {
                        active_verts[k] = active_verts[k + 1];
                    }
                    verts_left--;
                    ear_found = 1;
                    break;
                }
            }
        }
        
        if (!ear_found) break;
    }
}

void shred_flats(World *w, WyrdMesh *mesh, int *offset, int sector_idx) {
    SectorLine slines[512]; 
    int sline_count = 0;

    // All lines belonging to this sector
    for (int i = 0; i < w->lc; i++) {
        if (w->l[i].sector == sector_idx) {
            slines[sline_count].start_vert = w->l[i].head;
            slines[sline_count].end_vert   = w->l[i].tail;
            slines[sline_count].used       = 0;
            sline_count++;
        } else if (w->l[i].is_portal == 1 && w->l[i].adjacent_sector == sector_idx) {
            // Reverse direction for back-facing lines
            slines[sline_count].start_vert = w->l[i].tail;
            slines[sline_count].end_vert   = w->l[i].head;
            slines[sline_count].used       = 0;
            sline_count++;
        }
    }

    // Keep finding loops until all lines are used
    int un_used_lines = sline_count;
    while (un_used_lines > 0) {
        int ordered_verts[512];
        int num_verts = 0;
        int first_vert = -1;
        int current_vert = -1;

        // Find the first unused line to start a new loop
        for (int i = 0; i < sline_count; i++) {
            if (!slines[i].used) {
                slines[i].used = 1;
                un_used_lines--;
                
                first_vert = slines[i].start_vert;
                current_vert = slines[i].end_vert;
                
                ordered_verts[num_verts++] = first_vert;
                break;
            }
        }

        // Trace the loop
        while (current_vert != first_vert && current_vert != -1) {
            ordered_verts[num_verts++] = current_vert;
            int found_next = 0;

            for (int i = 0; i < sline_count; i++) {
                if (!slines[i].used && slines[i].start_vert == current_vert) {
                    slines[i].used = 1;
                    un_used_lines--;
                    current_vert = slines[i].end_vert;
                    found_next = 1;
                    break;
                }
            }

            if (!found_next || num_verts >= 512) {
                break;
            }
        }

        // Triangulate this specific loop
        if (num_verts >= 3) {
            shred_single_loop(w, mesh, sector_idx, ordered_verts, num_verts, offset);
        }
    }
}

int shred_sector(World *world, int sector_id, WyrdMesh *mesh) {
    int triangle_count = calculate_triangle_count(world, sector_id);
    mesh->triangle_count = triangle_count;
    mesh->vertex_array = malloc(sizeof(float) * mesh->triangle_count * 9);
    mesh->texture_coord_array = malloc(sizeof(float) * mesh->triangle_count * 6);

    int offset = 0;
    int uv_offset = 0; 
    
	printf("SHREDDING SECTOR %d\n--------------------\n", sector_id);
    for(int i = world->s[sector_id].first_line; i < world->s[sector_id].first_line+world->s[sector_id].linec; i++) {
		printf("Attempting wall shred%d\n", sector_id);
        if(world->l[i].is_portal) {
            shred_portal(world, mesh, offset, i);
            offset += 36; 
        
            apply_texture(mesh, uv_offset);
            apply_texture(mesh, uv_offset + 12);
            uv_offset += 24; 
        } else {
            shred_wall(world, mesh, offset, i);
            offset += 18; 
        
            apply_texture(mesh, uv_offset);
            uv_offset += 12; 
        }
    }
    
	printf("Mesh triangle count: %d\n", mesh->triangle_count);
	printf("Offset: %d\n", offset);
	printf("First Line: %d\n", world->s[sector_id].first_line);
	printf("Line Count: %d\n\n", world->s[sector_id].linec);
    shred_flats(world, mesh, &offset, sector_id);

    mesh->triangle_count = offset / 9;
  
	return 0;
}
