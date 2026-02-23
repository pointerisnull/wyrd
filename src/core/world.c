#include "world.h"
#include "primitives.h"

World new_world() {
	World w;

    int chunk_size = CHUNK_SIZE;
    int vc = 0;
    int lc = 0;
    int sc = 0;
    int cc = 0;

}

void new_vertex(World *w, int x, int z, int yb, int yt) {
	//                     x, z, yb, yt, id
	w->v[w->vc] = (Vertex){x, z, yb, yt, w->vc};
	w->vc++;

}

void new_line(World *w, int head_id, int tail_id) {
	w->l[w->lc] = (Line){w->lc, head_id, tail_id, 0, 0, 0xFFFFFFFF};
	w->lc++;
}

void new_sector(World *w, int start_line_id, int line_count) {
	w->s[w->sc] = (Sector){w->sc, line_count, start_line_id};
	w->sc++;

}

