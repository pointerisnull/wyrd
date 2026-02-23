#include "world.h"
#include "primitives.h"

#include <stdio.h>

World new_world() {
	World w;

    w.chunk_size = CHUNK_SIZE;
    w.vc = 0;
    w.lc = 0;
    w.sc = 0;
    w.cc = 0;

	return w;
}

void new_vertex(World *w, int x, int z, int yb, int yt) {
	//                     x, z, yb, yt, id
	w->v[w->vc] = (Vertex){x, z, yb, yt, w->vc};
	w->vc++;

}

void new_line(World *w, int head_id, int tail_id) {
	w->l[w->lc] = (Line){w->lc, (uint32_t)head_id, (uint32_t)tail_id, 0, 0, -1};
	w->l[w->lc].id = w->lc;
	w->l[w->lc].head = (uint32_t)head_id;
	w->l[w->lc].tail = (uint32_t)tail_id;
	w->l[w->lc].is_portal = 0;
	w->l[w->lc].normal = 0;
	w->l[w->lc].adjacent_sector = -1;
	w->lc++;
}

void new_sector(World *w, int start_line_id, int line_count) {
	w->s[w->sc] = (Sector){w->sc, line_count, start_line_id};
	w->sc++;

}

