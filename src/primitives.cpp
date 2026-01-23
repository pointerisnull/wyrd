#include "primitives.h"

Sector::Sector(int vertexc, int *pos) {
  this->vertexc = vertexc;
}

int Sector::get_vertex_count() {
  return this->vertexc;
}
