#ifndef RENDER_H
#define RENDER_H

#include "window.h"

void init_gl();
void draw_pixel(int x, int y, int width, int height);
void render_3D(Window *win);

#endif
