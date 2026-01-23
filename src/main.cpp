#include "primitives.h"
#include <cstdio>

int main(int argc, char **argv) {
  int *test;
  Sector sector = Sector(1, test);
  int count = sector.get_vertex_count();
  printf("Vertex Count: %d\n", count);

  return 0;
}
