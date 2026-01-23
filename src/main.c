#include "primitives.h"
#include <stdio.h>

int main(int argc, char **argv) {
  
  int count = 4;
  Vertex *verts = create_verticies(count);
  int positions[] = {3,4,5,1,2,3,9,8,7,11};
  populate_verticies(verts, count, positions);
  printf("Vertex Count: %d\n", count);
  printf("Vertex 3 position - x: %d y: %d \n", verts[2].x, verts[2].y);

  return 0;
}
