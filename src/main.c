#include "primitives.h"
#include <stdio.h>

int main(int argc, char **argv) {
  
  int count = 3;
  Vertex *verts = create_verticies(count)
  int positions[] = [3,4,5,1,2,3,9,8,7];
  populate_verticies(verts, count, &positions)
  printf("Vertex Count: %d\n", count);
  printf("Vertex 2 position - x: %d y: %d z: %d\n", verts[1]->x, verts[1]->y, verts[1]->z);

  return 0;
}
