#ifndef PRIMS_H
#define PRIMS_H


typedef struct Vertex {
  int x, y, z;
} Vertex;

typedef struct Line {
  int start_vertex, end_vertex;
  bool normal; //facing direction
  bool is_portal;
  int adjacent_sector;

} Line;

class Sector {
  private:
    int vertexc, linec;
    int first_vert;
    Vertex *verticies;
    Line *lines;

  public:
    Sector(int vertexc, int *pos);

    int get_vertex_count();
    Vertex *vertex_at(int x, int y);

};

#endif
