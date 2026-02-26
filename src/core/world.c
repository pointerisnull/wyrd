#include "world.h"
#include "primitives.h"

#include <stdio.h>

World new_world() {
	World w;

    w.chunk_size = CHUNK_SIZE;
    w.vc = 0;
    w.lc = 0;
    w.pc = 0;
    w.sc = 0;
    w.cc = 0;

	return w;
}

void new_vertex(World *w, int x, int z) {
	//                     x, z, id
	w->v[w->vc] = (Vertex){x, z, w->vc};
	w->vc++;

}

void new_line(World *w, int head_id, int tail_id, int sector_id, int adjacent_sector, bitset_t flags) {
	w->l[w->lc] = (Line){w->lc, (uint32_t)head_id, (uint32_t)tail_id, 0, 0, -1};
	w->l[w->lc].id = w->lc;
	w->l[w->lc].sector = sector_id;
	w->l[w->lc].head = (uint32_t)head_id;
	w->l[w->lc].tail = (uint32_t)tail_id;
	w->l[w->lc].is_portal = flags&0x1; // CHANGE LATER
	if (flags&0x1)
		w->pc++;
	w->l[w->lc].adjacent_sector = adjacent_sector;
	w->lc++;
}

void new_sector(World *w, int start_line_id, int line_count, int yb, int yt, int normal) {
	w->s[w->sc] = (Sector){w->sc, line_count, start_line_id, yb, yt, normal};
	w->sc++;

}

